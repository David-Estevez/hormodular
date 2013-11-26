#include "VisualTracker.h"
#include "camera_utils/camera_utils.h"


#define BOX_SIZE 30
#define MARKER_ECU_DIST_RATIO 2

using namespace cv;

VisualTracker::VisualTracker(void)
{
   /***********************OpenCV Debugger****************************
   cv::Mat image;
   cv::namedWindow( "Display Image", CV_WINDOW_AUTOSIZE );
   cv::waitKey(0);
   /***********************OpenCV Debugger****************************/

    // Initialize to camera #0
    //camera.open(0);
  camera.open(0);
  assert(camera.isOpened());
}

////////////////////////////////////////////////////////////////////////////////

//std::vector<int> VisualTracker::get_robot_3D_position(void)
void VisualTracker::get_robot_3D_position(double & x, double & y, double &z)
{
   namedWindow("video", 1);
   //cv::Mat input_image_rgb; // Image matrix

   // Capture a single image from camera
   cv::Mat3b input_image_rgb; // Image matrix
   camera >> input_image_rgb;

   if(!input_image_rgb.data) {
     std::cout << "No input file from camera to process." << std::endl;  // TODO: Debugger to be removed.
     //return -1;
   }
   //imshow("input_image_rgb", input_image_rgb);

   // Process the captured camera image
   int robot_x_pixels, robot_y_pixels;
   process_image(input_image_rgb, robot_x_pixels, robot_y_pixels);

   waitKey(0);
   //std::cout << "Ready to return from VisualTracker::get_robot_3D_position(std::vector<int>&)" << std::endl;  // TODO: Debugger to be removed.
}

////////////////////////////////////////////////////////////////////////////////

bool VisualTracker::get_robot_3D_position_rectfied(double &x, double &y, double &z) {
  // load calibration files
  std::string calibration_filename = "/home/nash/Dropbox/PhD/modularRobotics/morphomotion/VisualTracker/camera_utils/camera.yml";
  cv::Mat mapx, mapy;
  cv::Mat intrinsics, distortion, intrinsics_inv;
  CameraUtils::read_calibration_file
      (calibration_filename, mapx, mapy, intrinsics, distortion, intrinsics_inv);

  // Capture a single image from camera
  cv::Mat3b input_image_rgb; // Image matrix
  for (int var = 0; var < 5; ++var) // read 5 iamges
  {
      camera >> input_image_rgb;
  }

  if(!input_image_rgb.data || input_image_rgb.empty()) {
    std::cout << "No input file from camera to process." << std::endl;
    return false;
  }

  // Undistort image
  cv::Mat3b input_image_rgb_remapped = input_image_rgb.clone();
  cv::remap(input_image_rgb, input_image_rgb_remapped, mapx, mapy, cv::INTER_LINEAR);

  // Process the captured camera image
  int robot_x_pixels, robot_y_pixels;
  bool process_image_success = true;

  process_image_success = process_image(input_image_rgb_remapped, robot_x_pixels, robot_y_pixels);

  if (!process_image_success)
  {
    //std::cout << "process_image() returned false! Aborting." << std::endl; // TODO: Debugger to be removed.
    return false;
  }

  // reproject robot in 3D
  double fixed_height = 1.29; // meters
  cv::Point robot_center_pixels(robot_x_pixels, robot_y_pixels);
  cv::Point3f p3D = CameraUtils::pixel2world_known_distance
      (intrinsics_inv, robot_center_pixels, fixed_height);
  x = p3D.x;
  y = p3D.y;
  z = p3D.z;

  //std::cout << std::endl << "Finished -- reproject robot in 3D" << std::endl; // TODO: Debugger to be removed.

  // show axes
  double arrow_length = .5; // meters
  cv::line(input_image_rgb_remapped,
           CameraUtils::world2pixel(intrinsics, 0, 0, fixed_height),
           CameraUtils::world2pixel(intrinsics, arrow_length, 0, fixed_height),
           CV_RGB(255, 0, 0), 2);
  cv::line(input_image_rgb_remapped,
           CameraUtils::world2pixel(intrinsics, 0, 0, fixed_height),
           CameraUtils::world2pixel(intrinsics, 0, arrow_length, fixed_height),
           CV_RGB(0, 255, 0), 2);
  cv::line(input_image_rgb_remapped,
           CameraUtils::world2pixel(intrinsics, 0, 0, fixed_height),
           CameraUtils::world2pixel(intrinsics, arrow_length, arrow_length, fixed_height + arrow_length),
           CV_RGB(0, 0, 255), 2);

  //std::cout << std::endl << "Finished -- show axes" << std::endl; // TODO: Debugger to be removed.

  // show robot position
  cv::circle(input_image_rgb_remapped, robot_center_pixels, 2, CV_RGB(255, 0, 0), -1);

  // show images
  //namedWindow("input_image_rgb");
  //imshow("input_image_rgb", input_image_rgb);

  namedWindow("input_image_rgb_remapped");
  imshow("input_image_rgb_remapped", input_image_rgb_remapped);
  //waitKey(0);

  //std::cout << std::endl << "Leaving bool VisualTracker::get_robot_3D_position_rectfied(double&, double&, double&)" << std::endl; // TODO: Debugger to be removed.
  return true;
}

////////////////////////////////////////////////////////////////////////////////

bool VisualTracker::process_image(const cv::Mat & input_image_rgb,
                                  int & robot_x_pixels, int & robot_y_pixels)
{
   //printf("process_image:%ix%i\n", input_image_rgb.cols, input_image_rgb.rows);
   Mat3b imageHSV;
   Mat1b result;
   Mat1b Hbuffer;
   Mat1b Sbuffer;
   Mat1b Vbuffer;

   //imshow( "imageRGB", input_image_rgb );

   // OpenCV HSV encoding
   // H: 0 - 180, S: 0 - 255, V: 0 - 255.
   cv::cvtColor(input_image_rgb, imageHSV, CV_BGR2HSV, 0);
   //cv::imshow( "imageHSV", imageHSV );

   // blue color: H=240 (120 with OpenCV), S=100 (255 with OpenCV) , V=100 (255 with OpenCV)
   //int Hmin = 100, Hmax = 150, Smin  = 200, Smax = 255, Vmin = 200, Vmax = 255;
   //int Hmin = 100, Hmax = 150, Smin  = 105, Smax = 180, Vmin = 40, Vmax = 130;

   // Color --> Parrot Green: H=63-128 (31.5-64 with OpenCV), S=20-72 (51-183.6 with OpenCV) , V=26-54 (66.3-137.7 with OpenCV)
   //int Hmin = 25, Hmax = 70, Smin  = 45, Smax = 190, Vmin = 60, Vmax = 145;
   //int Hmin = 30, Hmax = 65, Smin  = 50, Smax = 180, Vmin = 65, Vmax = 140;
   int Hmin = 40, Hmax = 55, Smin  = 60, Smax = 170, Vmin = 75, Vmax = 125;

   image_utils::HSVfilter(imageHSV,
                          250, result,
                          Hmin, Hmax, Smin, Smax, Vmin, Vmax,
                          Hbuffer, Sbuffer, Vbuffer);

   /*cv::imshow( "Hbuffer", Hbuffer );
   cv::imshow( "Sbuffer", Sbuffer );
   cv::imshow( "Vbuffer", Vbuffer );
   cv::imshow( "result", result );*/

   // process disjoint sets
   DisjointSets2 set(result);

   // instantiate output for get_connected_components()
   int cols = imageHSV.cols;
   int rows = imageHSV.rows;
   std::vector< DisjointSets2::Comp > components_pts;
   std::vector<cv::Rect> boundingBoxes;

   // get results
   set.get_connected_components(cols, components_pts, boundingBoxes);

   if(boundingBoxes.size() < 3)
   {
       //std::cout << std::endl << "Too few connected components found. Aborting" << std::endl; // TODO: Debugger to be removed.
       return false;
   }


/***************************** Sort by boundingBox size approach **************************************/
   cv::Rect tempBoundingBox;

   // Sort the components based on the bounding box size.
   for(int i = 0; i < boundingBoxes.size()-1; i++)
   {
      for(int j = i+1; j < boundingBoxes.size(); j++)
      {
         if((boundingBoxes[j].width * boundingBoxes[j].height) > (boundingBoxes[i].width * boundingBoxes[i].height))
         {
            tempBoundingBox = boundingBoxes[i];
            boundingBoxes[i] = boundingBoxes[j];
            boundingBoxes[j] = tempBoundingBox;
         }
      }
   }

   /*printf("Total number of components: %i\n", (int) boundingBoxes.size());
   std::cout << "Top three components:" << std::endl;
   for(int box_idx = 0; box_idx < 3; box_idx++)
   {
      printf("Box %i (%i, %i)+(%i, %i)\n",
             box_idx,
             boundingBoxes[box_idx].x,
             boundingBoxes[box_idx].y,
             boundingBoxes[box_idx].width,
             boundingBoxes[box_idx].height);
   }*/

   // make an illustration of the result
   cv::Mat3b illus = input_image_rgb.clone();
   for(int box_idx = 0; box_idx < 3; box_idx++)
   {
      cv::rectangle(illus, boundingBoxes[box_idx], CV_RGB(255, 0, 0), 1);
   }
   //cv::imshow( "illus", illus );
/***************************** Sort by boundingBox size approach **************************************/

/***************************** Extract center point of the markers ************************************/
   std::vector<cv::Point> center(3);
   cv::Point temp_point;

   for(int box_idx = 0; box_idx < 3; box_idx++)
   {
      temp_point.x = boundingBoxes[box_idx].x + (boundingBoxes[box_idx].width/2);
      temp_point.y = boundingBoxes[box_idx].y + (boundingBoxes[box_idx].height/2);
      center[box_idx] = temp_point;
   }

   cv::Mat3b illus_triangle = illus.clone();

   cv::line(illus_triangle, center[0], center[1], CV_RGB(0, 0, 255), 1, 8, 0);
   cv::line(illus_triangle, center[1], center[2], CV_RGB(0, 0, 255), 1, 8, 0);
   cv::line(illus_triangle, center[2], center[0], CV_RGB(0, 0, 255), 1, 8, 0);

   //cv::imshow( "illus_triangle", illus_triangle );
/***************************** Extract center point of the markers ************************************/


/******************************** Validate the extracted markers **************************************/
   std::vector<double> eucDistance_marker(3);

   //--Calculate the euclidean distance between the markers.
   eucDistance_marker[0] = euclidean_distance(center[0], center[1]);
   eucDistance_marker[1] = euclidean_distance(center[1], center[2]);
   eucDistance_marker[2] = euclidean_distance(center[2], center[0]);

   //--Sort the euclidean distance between markets.
   double temp_ecuDist;
   for(unsigned int i=0; i<2; i++)
   {
       for(unsigned int j=i+1; j<3; j++)
       {
           if(eucDistance_marker[i] < eucDistance_marker[j])
           {
               temp_ecuDist = eucDistance_marker[i];
               eucDistance_marker[i] = eucDistance_marker[j];
               eucDistance_marker[j] = temp_ecuDist;
           }
       }
   }

   for(unsigned int i=0; i<2; i++)
   {
       for(unsigned int j=i+1; j<3; j++)
       {
           if(eucDistance_marker[i]/eucDistance_marker[j] >= MARKER_ECU_DIST_RATIO)
           {
               //std::cout << std::endl << "Incorrect Markers" << std::endl; // TODO: Debugger to be removed.
               //break;
               return false;
           }
       }
   }

   //std::cout << std::endl << "Finished /**Validate the extracted markers**/" << std::endl; // TODO: Debugger to be removed.
/******************************** Validate the extracted markers **************************************/


/************************************ Detect orientation marker ***************************************/

   std::vector<double> diff_eucDistance(3);

   diff_eucDistance[0] = fabs(euclidean_distance(center[0], center[1]) - euclidean_distance(center[0], center[2]));
   diff_eucDistance[1] = fabs(euclidean_distance(center[1], center[0]) - euclidean_distance(center[1], center[2]));
   diff_eucDistance[2] = fabs(euclidean_distance(center[2], center[0]) - euclidean_distance(center[2], center[1]));

   for(int i=0; i<3; i++)
   {
      //std::cout << "euclidean_distance " << i+1 << ": " << diff_eucDistance[i] << std::endl;  // TODO: Debugger to be removed.
   }

   int orientationMarker_index = 0;
   cv::Point point2;

   if(diff_eucDistance[0] < diff_eucDistance[1] && diff_eucDistance[0] < diff_eucDistance[2])
   {
      orientationMarker_index = 0;
      //cv::rectangle(illus_triangle, boundingBoxes[0], CV_RGB(0, 255, 0), 1);

      point2.x = center[2].x + ((center[1].x - center[2].x)/2);
      point2.y = center[2].y + ((center[1].y - center[2].y)/2);

      cv::line(illus_triangle, center[0], point2, CV_RGB(0, 0, 255), 1, 8, 0);

      robot_x_pixels = boundingBoxes[0].x + (boundingBoxes[0].width/2);
      robot_y_pixels = boundingBoxes[0].y + (boundingBoxes[0].height/2);

   }
   else if(diff_eucDistance[1] < diff_eucDistance[0] && diff_eucDistance[1] < diff_eucDistance[2])
   {
      orientationMarker_index = 1;
      //cv::rectangle(illus_triangle, boundingBoxes[1], CV_RGB(0, 255, 0), 1);

      point2.x = center[2].x + ((center[0].x - center[2].x)/2);
      point2.y = center[2].y + ((center[0].y - center[2].y)/2);

      cv::line(illus_triangle, center[1], point2, CV_RGB(0, 0, 255), 1, 8, 0);

      robot_x_pixels = boundingBoxes[1].x + (boundingBoxes[1].width/2);
      robot_y_pixels = boundingBoxes[1].y + (boundingBoxes[1].height/2);
   }
   else if(diff_eucDistance[2] < diff_eucDistance[0] && diff_eucDistance[2] < diff_eucDistance[1])
   {
      orientationMarker_index = 2;
      //cv::rectangle(illus_triangle, boundingBoxes[2], CV_RGB(0, 255, 0), 1);

      point2.x = center[1].x + ((center[0].x - center[1].x)/2);
      point2.y = center[1].y + ((center[0].y - center[1].y)/2);

      cv::line(illus_triangle, center[2], point2, CV_RGB(0, 0, 255), 1, 8, 0);

      robot_x_pixels = boundingBoxes[2].x + (boundingBoxes[2].width/2);
      robot_y_pixels = boundingBoxes[2].y + (boundingBoxes[2].height/2);
   }

   //cv::imshow( "illus_triangle", illus_triangle );
/************************************ Detect orientation marker ***************************************/


/**************************************** Calculate centroid ******************************************/
   //std::cout << std::endl << "Started /**Calculate centroid**/" << std::endl; // TODO: Debugger to be removed.
   cv::Point centroid;
   centroid.x = (center[0].x + center[1].x + center[2].x)/3;
   centroid.y = (center[0].y + center[1].y + center[2].y)/3;

   //cv::circle(illus_triangle, centroid, 2, CV_RGB(0, 255, 0), 3, 8, 0);
   //cv::imshow( "illus_triangle", illus_triangle );

   robot_x_pixels = centroid.x;
   robot_y_pixels = centroid.y;

   //robot_x_pixels = 20;
   //robot_y_pixels = 20;

   //std::cout << std::endl << "Finished /**Calculate centroid**/" << std::endl; // TODO: Debugger to be removed.
/**************************************** Calculate centroid ******************************************/


/************************************** Determine orientation *****************************************
   int quad = 0;

   if(center[orientationMarker_index].x <= cols/2)
   {
      if(center[orientationMarker_index].y <= rows/2)
      {
         quad = 2;
      }
      else
      {
         quad = 3;
      }
   }
   else
   {
      if(center[orientationMarker_index].y <= rows/2)
      {
         quad = 1;
      }
      else
      {
         quad = 4;
      }
   }

   std::cout << std::endl << "Quadrant: " << quad << std::endl;




/************************************** Determine orientation *****************************************/

    //std::cout << std::endl << "Leaving process_image(const cv::Mat&, int&, int&)" << std::endl; // TODO: Debugger to be removed.
    return true;
}

double VisualTracker::euclidean_distance(cv::Point point1, cv::Point point2)
{
   return( sqrt(((point1.x - point2.x)*(point1.x - point2.x)) + ((point1.y - point2.y)*(point1.y - point2.y))));
}
