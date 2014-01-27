/*!
 * \file test_CameraUtils.cpp
 *
 * tests for the camera
 *
 * \date 10/11/2010
 * \author Arnaud Ramey
 */

////// my imports
#include "camera_utils.h"
//#include "utils/image/CameraUtils/camera_calibrator.h"

//#include "long_term_memory/ltm_path.h"
#define LONG_TERM_MEMORY_DIR ""

inline int get_camera_nb_prompt() {
  std::cout << "Camera index ? (0=default)" << std::endl;
  int camera_nb = 0;
  std::cin >> camera_nb;
  return camera_nb;
}

int main(int argc, char **argv) {
  printf("grabbing the camera...\n");
  std::cout << "1 : camera test mode (OpenCV 2.1 style)" << std::endl;
  std::cout << "2 : photo camera mode" << std::endl;
  std::cout << "3 : video recorder mode" << std::endl;
  std::cout << "4 : video player mode" << std::endl;
  std::cout << "5 : three-layers camera test mode" << std::endl;
  // std::cout << "6 : camera calibrator mode" << std::endl;
  std::cout << "7 : rectify image" << std::endl;
  std::cout << "8 : rectify image ROS" << std::endl;

  int choice = 8;
  std::cin >> choice;

  /* camera tests */

  if (choice == 1) {
    CameraUtils::cameraTester_OpenCV2(get_camera_nb_prompt());
  }

  if (choice == 2) {
    cv::VideoCapture capture;
    CameraUtils::getCamera(get_camera_nb_prompt(), capture);
    CameraUtils::photo_camera(capture, "pic", 1);
  }

  if (choice == 3) {
    const char* filename =
        (argc < 2 || strlen(argv[1]) == 0 ? "video_capture.avi"
                                          : argv[1]);
    std::cout << "input:" << filename << std::endl;
    cv::VideoCapture capture;
    CameraUtils::getCamera(get_camera_nb_prompt(), capture);
    CameraUtils::cameraRecorder(capture, filename);
  }

  if (choice == 4) {
    const char* filename =
        (argc < 2 || strlen(argv[1]) == 0 ? "video_capture.avi"
                                          : argv[1]);
    std::cout << "input:" << filename << std::endl;
    CameraUtils::videoPlayer(filename);
  }

  if (choice == 5) {
    cv::VideoCapture capture;
    CameraUtils::getCamera(get_camera_nb_prompt(), capture);
    CameraUtils::showThreeLayers(capture);
  }

  /* calibrator */
  if (choice == 6) {
    //        CameraCalibrator cc("chess_captures/pic", ".png", 1, 38, 3);
    //        cc.autoCalibrate();
    //        cc.test();
  }

  if (choice == 7) {
    cv::VideoCapture capture;
    CameraUtils::getCamera(get_camera_nb_prompt(), capture);
    CameraUtils::rectify_image_skeleton
        (capture, "/home/nash/Dropbox/PhD/modularRobotics/morphomotion/VisualTracker/camera_utils/camera.yml");
  }

  if (choice == 8) {
    cv::VideoCapture capture;
    CameraUtils::getCamera(get_camera_nb_prompt(), capture);
    CameraUtils::rectify_image_ros
        (capture, LONG_TERM_MEMORY_DIR "kinect/Logitech_QuickCam_Arnaud.yml");
  }

  return 0;
}

