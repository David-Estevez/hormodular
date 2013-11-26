/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   Y 1   M O D U L A R   R O B O T    C L A S S   H E A D E R                                                 */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef Y1MODULARROBOT_H
#define Y1MODULARROBOT_H

//#include <Robot.h>
#include "Robot.h"
#include "VisualTracker.h"
#include "SerialCommunication.h"

#define BAUD_RATE 115200

//#define MAX_POLL_TRIALS 10  //-- For Wired-Communication between PC and Skymega
#define MAX_POLL_TRIALS 14  //-- For XBEE-Communication between PC and Skymega

using namespace std;

class Y1ModularRobot: public Robot
{

public:

  enum MessageType{Request_ServoTime, Request_Time, None};

  //-- DEFAULT CONSTRUCTOR
  Y1ModularRobot();
  
  //-- COPY CONSTRUCTOR
  Y1ModularRobot(const Robot*);

  //-- CONSTRUCTOR WITH SERIAL PORT
  Y1ModularRobot(const std::string&);

  //-- DESTRUCTOR
  virtual ~Y1ModularRobot(void);

  //-- METHODS
  void set_default_parameters(void);
  bool set_serial_port(const std::string&, int);
  void set_elapsed_evaluation_time(unsigned long);
  void init_elapsed_evaluation_time(unsigned long);
  //void get_all_moduleServo_position_with_time(vector<ServoFeedback*>&); //-- Compatible with Arduino code --> servo_controller_charArray_V6.pde
  //void get_all_moduleServo_position_with_individual_time(vector<ServoFeedback*>&); //-- Compatible with Arduino code --> servo_controller_charArray_V7.pde
  bool get_message(char*);
  bool get_message_with_time(char*); //-- Compatible with Arduino code --> servo_controller_charArray_V6.pde
  bool decode_message(const char[], vector<double>&);
  bool decode_message_with_time(const char[], vector<double>&); //-- Compatible with Arduino code --> servo_controller_charArray_V6.pde
  bool decode_message_with_individual_time(const char[], vector<double>&, vector<long>&); //-- Compatible with Arduino code --> servo_controller_charArray_V7.pde
  void get_current_time(void);
  std::vector<double> get_robot_XY();
  double euclidean_distance(const std::vector<double> pos_1, const std::vector<double> pos_2);

  //-- INHERITED METHODS
  void copy(const Robot*);
  void reset_robot(void);
  void set_sinusoidal_controller_parameters(const vector<double>&, const vector<double>&, const vector<double>&, const double);
  void stop_sinusoidal_controller(void);
  void set_moduleServo_position(unsigned int, double);
  void set_all_moduleServo_position(const vector<double>&);
  double get_moduleServo_position(unsigned int);
  //void get_all_moduleServo_position(vector<ServoFeedback*>&);
  unsigned long get_elapsed_evaluation_time(void);
  unsigned long get_previous_read_evaluation_time(void);
  double calculate_distance_travelled_euclidean(void);
  void measure_cumulative_distance(void);
  double get_robot_X(void);
  double get_robot_Y(void);
  void step(const std::string&);

private:
  std::vector<double> robot_pos_initial;
  VisualTracker *vis_track;
  unsigned int serial_port;
};

#endif
