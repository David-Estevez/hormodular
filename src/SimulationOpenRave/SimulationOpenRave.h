/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   S I M U L A T I O N   O P E N R A V E   C L A S S   H E A D E R                                            */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/


#ifndef SIMULARIONOPENRAVE_H
#define SIMULARIONOPENRAVE_H

// OpenRAVE includes
#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

// Base class include
#include <Robot.h>

using namespace OpenRAVE;

class SimulationOpenRave: public Robot
{

public:

  // DEFAULT CONSTRUCTOR
  SimulationOpenRave(void);
  
  // COPY CONSTRUCTOR
  SimulationOpenRave(const Robot*);

  // CONSTRUCTOR WITH SCENE FILE NAME
  SimulationOpenRave(std::string&);

  // DESTRUCTOR
  virtual ~SimulationOpenRave(void);

  // METHODS
  void init_simu_env(std::string);
  void set_default_parameters(void);
  void SetCamera(dReal, dReal, dReal, dReal, dReal, dReal, dReal);
  void load_controller(std::string);
  void set_scene_file_name(const std::string);
  std::string get_scene_file_name(void);
  //void get_all_moduleServo_position_with_time(vector<ServoFeedback*>&);
  void init_elapsed_evaluation_time(void);
  void update_elapsed_evaluation_time(void);
  void set_simu_resolution_microseconds(double);
  double get_simu_resolution_microseconds(void);
  Vector get_robot_XY();

  // INHERITED METHODS
  void copy(const Robot*);
  void reset_robot(void);
  void set_sinusoidal_controller_parameters(const vector<double>&, const vector<double>&, const vector<double>&, const double);
  void stop_sinusoidal_controller(void);
  void set_moduleServo_position(unsigned int, double);
  double get_moduleServo_position(unsigned int);
  //void get_all_moduleServo_position(vector<ServoFeedback*>&);
  unsigned long get_elapsed_evaluation_time(void); //-- uS
  unsigned long get_previous_read_evaluation_time(void);
  double calculate_distance_travelled_euclidean(void);
  void measure_cumulative_distance(void);
  double get_robot_X(void);
  double get_robot_Y(void);
  void step(const std::string&);

private:
  EnvironmentBasePtr penv;
  RobotBasePtr probot;
  ControllerBasePtr pcontroller;
  Transform t0;
  std::string scene_file_name;
  //Vector robot_pos_initial;
  Vector robot_pos_previous;
  double simu_resolution_seconds;
};

#endif
