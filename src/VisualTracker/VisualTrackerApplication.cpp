#include "VisualTracker.h"

int main(void) {
  VisualTracker vt;

  double x = 1.1;
  double y = 2.2;
  double z = 3.3;

  bool got_robot_position_success = false;

  for(unsigned int i=0; i<30; i++)
  {
      unsigned int vtCounter = 0;
      do
      {
        vtCounter++;
        got_robot_position_success = vt.get_robot_3D_position_rectfied(x, y, z);
      }while(!got_robot_position_success);

      std::cout << std::endl << i+1 << " (" << vtCounter << ") -->  X = " << x << ", Y = " << y << ", Z = " << z << std::endl;
      cv::waitKey(0);
  }

  return 0;
}
