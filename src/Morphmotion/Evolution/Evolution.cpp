/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   E V O L U T I O N   C L A S S                                                                              */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/

#include <iostream>  // TODO: May be not needed. Confirm and remove
#include <math.h>  // TODO: May be not needed. Confirm and remove

#include "Evolution.h"

namespace Flood
{

Evolution::Evolution()
{
  robot = NULL;
  controller = NULL;
}

Evolution::Evolution(MultilayerPerceptron* mlp)
:ObjectiveFunctional(mlp)
{
}

//-- GENERAL CONSTRUCTOR WITH SIMULATION ENVIRONMENT OBJECT
Evolution::Evolution(MultilayerPerceptron* mlp, Robot* robot_pointer, Controller* controller_pointer)
:ObjectiveFunctional(mlp)
{
  robot = robot_pointer;
  controller = controller_pointer;
}


//-- DESTRUCTOR
Evolution::~Evolution(void)
{
}


//-- METHODS

//-- Default objective function for debugging purpose.
double Evolution::calculate_objective(void)
{
  double evaluation;
  evaluation =  controller->calculate_random_uniform(0.1,5.0);
  return evaluation;
}

double Evolution::calculate_objective(int generation, int individual)  //-- TODO: To be removed from here and from ObjectiveFunction.h
{
    return 0;
}

double Evolution::calculate_objective(int generation, int individual, int evaluation_sample_size)
{
  Vector<double> evaluation(evaluation_sample_size);
  double total_distance = 0;
  double mean_distance = 0;
  double mean_speed = 0;

  //double gen = generation;
  //double ind = individual;

  std::cout << std::endl << generation << " -- " << individual << ":";
  for(int i=0; i<evaluation_sample_size; i++)
  {
    //-- Initialise the robot with 0 degrees to the motor and move it to the initial position.
    robot->reset_robot();

    //-- Run controller.
    controller->run_Controller("evolution",individual,generation,i);

    //-- Calculate distance travelled by the robot.
    //evaluation[i] = robot->calculate_distance_travelled_euclidean();
    evaluation[i] = robot->get_distance_travelled();

    std::cout << "    (" << i+1 << ") " << evaluation[i];
  }

  for(int i=0; i<evaluation_sample_size; i++)
  {
    total_distance = total_distance + evaluation[i];
  }

  mean_distance = total_distance/evaluation_sample_size;
  mean_speed = (mean_distance/controller->get_evaluation_period())*100;  //-- Mean speed calculated as cms/second.
  
  //--------------------TODO: Debugger to be removed--------------------//
  /*std::cout << std::endl;
  double user_fitness;
  std::cin >> user_fitness;
  
  if(user_fitness)
  {
		mean_speed = user_fitness;
	}
	else
	{
		mean_speed = mean_speed/10;
	}*/
  //--------------------TODO: Debugger to be removed--------------------//

  return(mean_speed);
}

}

