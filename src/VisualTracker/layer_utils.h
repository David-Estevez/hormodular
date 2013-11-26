#ifndef LAYER_UTILS_H
#define LAYER_UTILS_H

#include "color_utils.h"
#include <opencv2/imgproc/imgproc.hpp>

namespace image_utils {

////////////////////////////////////////////////////////////////////////////

/*!
 *\brief   extract one of the layer from an image
     *
 *\param   src the source
 *\param   dest the destination
 *\param   layer the number of the layer (between 0 and 2)
 */
inline void extractLayer(const cv::Mat & src, cv::Mat & dest,
                         const int layer) {
  // TODO check there is a copy done
  //    cv::vector<cv::Mat> planes;
  //    split(src, planes);
  //    dest = planes.at(layer);

  IplImage src_ipl = src, dest_ipl = dest;
  if (layer == 0)
    cvSplit(&src_ipl, &dest_ipl, 0, 0, 0); // hue
  if (layer == 1)
    cvSplit(&src_ipl, 0, &dest_ipl, 0, 0); // saturation
  if (layer == 2)
    cvSplit(&src_ipl, 0, 0, &dest_ipl, 0); // value
}

////////////////////////////////////////////////////////////////////////////

/*!
 *\brief   save in "dest" one HSV component of "src"
 */
inline void extractHSVLayer(const cv::Mat & src, cv::Mat & temp,
                            cv::Mat & dest, const int layer) {
  cv::cvtColor(src, temp, CV_BGR2HSV); // conversion in HSV
  extractLayer(temp, dest, layer);
}

////////////////////////////////////////////////////////////////////////////

/*!
 *\brief   save in "dest" the hue component of "src"
 */
inline void extractHue(const cv::Mat & src, cv::Mat & temp, cv::Mat & dest) {
  extractHSVLayer(src, temp, dest, 0);
}

////////////////////////////////////////////////////////////////////////////

/*!
 *\brief   save in "dest" the saturation component of "src"
 */
inline void extractSaturation(const cv::Mat & src, cv::Mat & temp, cv::Mat & dest) {
  extractHSVLayer(src, temp, dest, 1);
}

////////////////////////////////////////////////////////////////////////////

/*!
 *\brief   save in "dest" the value component of "src"
 */
inline void
extractValue(const cv::Mat & src, cv::Mat & temp, cv::Mat & dest) {
  extractHSVLayer(src, temp, dest, 2);
}

////////////////////////////////////////////////////////////////////////////

/*!
 *\brief   create the rgb image which illustrate the hue
 *\param   src a rgb image
 *\param   dest a rgb image
 */
inline void extractHue_and_convertRGB(const cv::Mat3b & src, cv::Mat3b & dest)  {
  // (int _rows, int _cols)
  cv::Mat1b hue (src.rows, src.cols);
  dest.create(src.rows, src.cols);
  cv::Vec3b rgb;

  /* get the layer__Hue component */
  extractHue(src, dest, hue);
  //cv::cvtColor( src, dest, CV_BGR2HSV );  // conversion in HSV
  //cvSplit(dest, layer__Hue, 0, 0, 0);               // split the image

  cv::Mat1b::iterator hue_it = hue.begin();
  cv::Mat3b::iterator dest_it = dest.begin();
  while (hue_it != hue.end()) {
    rgb = color_utils::hue2rgb<cv::Vec3b>(*hue_it);
    (dest_it[0]) = rgb[0];
    (dest_it[1]) = rgb[1];
    (dest_it[2]) = rgb[2];
    ++hue_it;
    ++dest_it;
  }

  /*std::ostringstream m;
     m << "extractHue_and_convertRGB():dest:" << dest.cols << "x" << dest.rows << "|" << dest.nChannels << " channels";
     maggieDebug2(m.str());*/
}

////////////////////////////////////////////////////////////////////////////

/*!
 *\brief   create the rgb image which illustrate the hue component
 *of the image "filename"
 */
inline void extractHue_and_showRGB(const std::string & filename) {
  cv::Mat1b original_h = cv::imread(filename, 1);
  cv::Mat3b res ( original_h.rows, original_h.cols);

  /* transforn */
  extractHue_and_convertRGB(original_h, res);

  /* show results */
  const char* window_hueImage = "Hue Previewer";
  cv::namedWindow(window_hueImage, CV_WINDOW_AUTOSIZE);
  cv::imshow(window_hueImage, res);

  /* loop to see the results */
  while (1) {
    if ((cv::waitKey(33) & 255) == 27)
      break;
  }

}

////////////////////////////////////////////////////////////////////////////

inline void HSVfilter(const cv::Mat3b & srcHSV,
                      const int outValue, cv::Mat1b & result,
                      const int Hmin, const int Hmax,
                      const int Smin, const int Smax,
                      const int Vmin, const int Vmax,
                      cv::Mat1b & Hbuffer, cv::Mat1b & Sbuffer, cv::Mat1b & Vbuffer) {
//void HSVfilter() {
  
     // init the images if needed

  Hbuffer.create(srcHSV.size());
  Sbuffer.create(srcHSV.size());
  Vbuffer.create(srcHSV.size());
  result.create(srcHSV.size());

     // split

  std::vector< cv::Mat1b > layers;
  layers.push_back(Hbuffer);
  layers.push_back(Sbuffer);
  layers.push_back(Vbuffer);
  cv::split(srcHSV, layers);

     // filter each channel

  cv::threshold(Hbuffer, Hbuffer, Hmax, 255, cv::THRESH_TOZERO_INV);
  cv::threshold(Hbuffer, Hbuffer, Hmin, outValue, cv::THRESH_BINARY);
  cv::threshold(Sbuffer, Sbuffer, Smax, 255, cv::THRESH_TOZERO_INV);
  cv::threshold(Sbuffer, Sbuffer, Smin, outValue, cv::THRESH_BINARY);
  cv::threshold(Vbuffer, Vbuffer, Vmax, 255, cv::THRESH_TOZERO_INV);
  cv::threshold(Vbuffer, Vbuffer, Vmin, outValue, cv::THRESH_BINARY);

     // combine

  cv::min( (cv::Mat) Hbuffer, Sbuffer, result);
  cv::min( (cv::Mat) result, Vbuffer, result);
}

} // end namesapce image_utils

#endif // LAYER_UTILS_H
