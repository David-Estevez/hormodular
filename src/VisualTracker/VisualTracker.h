//#include "cv.h"
//#include "highgui.h"

#include <vector>

#include "/usr/local/include/opencv/cv.h"
#include "/usr/local/include/opencv/highgui.h"

#include "layer_utils.h"
#include "disjoint_sets2.h"


class VisualTracker
{
private:
    cv::VideoCapture camera; // From camera or video

public:
  VisualTracker(void);
  ~VisualTracker() {
    camera.release();
  }

  //std::vector<int> get_robot_3D_position(void);
  //void get_robot_3D_position(void);
  //! return position of the robot in meters
  bool process_image(const cv::Mat&, int &robot_x_pixels, int &robot_y_pixels);
  void get_robot_3D_position(double &x, double &y, double& z);
  bool get_robot_3D_position_rectfied(double &x, double &y, double& z);
  double euclidean_distance(cv::Point, cv::Point);
};
