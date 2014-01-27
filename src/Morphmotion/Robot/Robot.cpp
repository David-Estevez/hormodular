/****************************************************************************************************************/
/*                                                                                                              */
/*   Morphomotion: A project researching on how morphology influences locomotion in robots.                     */
/*                                                                                                              */
/*   R O B O T [B A S E]   C L A S S                                                                            */
/*                                                                                                              */
/*   Avinash Ranganath                                                                                          */
/*   Robotics Lab, Department of Systems Engineering and Automation                                             */
/*   University Carlos III de Mardid(UC3M)                                                                      */
/*   Madrid, Spain                                                                                              */
/*   E-mail: avinash.ranganath@uc3m.es                                                                          */
/*   http://roboticslab.uc3m.es/roboticslab/persona.php?id_pers=104                                             */
/*                                                                                                              */
/****************************************************************************************************************/

#include <Robot.h>


Robot::Robot()
{
  set_robot_priority("Robot_Primary");
  elapsed_evaluation_time = 0;
  distance_travelled = 0;
  evaluation_method = Euclidean_Distance_Final;
  number_of_modules = 2;
}


void Robot::set_robot_environment(const std::string& new_robot_environment)
{
  if(new_robot_environment == "SimulationOpenRave")
  {
    robot_environment = SimulationOpenRave;
  }
  else if(new_robot_environment == "Y1")
  {
    robot_environment = Y1;
  }
  else
  {
    std::cerr << "Morphomotion Error: Robot class." << std::endl
              << "void set_robot_environment(const std::string&) method." << std::endl
              << "Unknown RobotEnvironment: " << new_robot_environment << "." <<std::endl;

    exit(1);
  }
}


std::string Robot::get_robot_environment(void) const
{
  switch(robot_environment)
  {
    case SimulationOpenRave:
    {
      return("SimulationOpenRave");
    }
    break;
    case Y1:
    {
      return("Y1");
    }
    break;
    default:
    {
      std::cerr << "Morphomotion Error: Robot class." << std::endl
                << "std::string get_robot_environment(void) method." << std::endl
                << "Robot_Environment: " << std::endl;
      exit(1);
    }
  }
}


void Robot::set_robot_priority(const std::string& new_robot_priority)
{
  if(new_robot_priority == "Robot_Primary")
  {
    robot_priority = Robot_Primary;
  }
  else if(new_robot_priority == "Robot_Secondary")
  {
    robot_priority = Robot_Secondary;
  }
  else
  {
    std::cerr << "Morphomotion Error: Robot class." << std::endl
              << "void set_robot_priority(const std::string&) method." << std::endl
              << "Unknown Robot_Priority: " << new_robot_priority << "." <<std::endl;

    exit(1);
  }
}


std::string Robot::get_robot_priority(void) const
{
  switch(robot_priority)
  {
    case Robot_Primary:
    {
      return("Robot_Primary");
    }
    break;
    case Robot_Secondary:
    {
      return("Robot_Secondary");
    }
    break;
    default:
    {
      std::cerr << "Morphomotion Error: Robot class." << std::endl
                << "std::string get_robot_priority(void) method." << std::endl
                << "robot_priority: " << std::endl;
      exit(1);
    }
  }
}


void Robot::set_robot_type(const std::string& new_robot_type)
{
  if(new_robot_type == "CubeN_ServoFeedBack")
  {
    robot_type = CubeN_ServoFeedBack;
  }
  else if(new_robot_type == "Tripod")
  {
    robot_type = Tripod;
  }
  else if(new_robot_type == "Quadpod")
  {
    robot_type = Quadpod;
  }
  else if(new_robot_type == "Ybot4_ServoFeedBack")
  {
    robot_type = Ybot4_ServoFeedBack;
  }
  else if(new_robot_type == "Lizard")
  {
    robot_type = Lizard;
  }
  else if(new_robot_type == "Bunny")
  {
    robot_type = Bunny;
  }
  else if(new_robot_type == "Bunny_StiffSpine")
  {
    robot_type = Bunny_StiffSpine;
  }
  else if(new_robot_type == "Lizard_3D")
  {
    robot_type = Lizard_3D;
  }
  else
  {
    std::cerr << "Morphomotion Error: Robot class." << std::endl
              << "void set_robot_type(const std::string&) method." << std::endl
              << "Unknown RobotType: " << new_robot_type << "." <<std::endl;

    exit(1);
  }
}


std::string Robot::get_robot_type(void) const
{
  switch(robot_type)
  {
    case CubeN_ServoFeedBack:
    {
      return("CubeN_ServoFeedBack");
    }
    break;
    case Tripod:
    {
      return("Tripod");
    }
    break;
    case Quadpod:
    {
      return("Quadpod");
    }
    break;
    case Ybot4_ServoFeedBack:
    {
      return("Ybot4_ServoFeedBack");
    }
    break;
    case Lizard:
    {
      return("Lizard");
    }
    break;
    case Bunny:
    {
      return("Bunny");
    }
    break;
    case Bunny_StiffSpine:
    {
      return("Bunny_StiffSpine");
    }
    break;
    case Lizard_3D:
    {
      return("Lizard_3D");
    }
    break;
    default:
    {
      std::cerr << "Morphomotion Error: Robot class." << std::endl
                << "std::string get_robot_type(void) method." << std::endl
                << "Unknown RobotType: " << std::endl;
      exit(1);
    }
  }
}


void Robot::set_evaluation_method(const std::string& new_evaluation_method)
{
  if(new_evaluation_method == "Euclidean_Distance_Final")
  {
    evaluation_method = Euclidean_Distance_Final;
  }
  else if(new_evaluation_method == "Euclidean_Distance_Cumulative")
  {
    evaluation_method = Euclidean_Distance_Cumulative;
  }
  else
  {
    std::cerr << "Morphomotion Error: Robot class." << std::endl
              << "void set_evaluation_method(const std::string&) method." << std::endl
              << "Unknown RobotEnvironment: " << new_evaluation_method << "." <<std::endl;

    exit(1);
  }
}


std::string Robot::get_evaluation_method(void) const
{
  switch(evaluation_method)
  {
    case Euclidean_Distance_Final:
    {
      return("Euclidean_Distance_Final");
    }
    break;
    case Euclidean_Distance_Cumulative:
    {
      return("Euclidean_Distance_Cumulative");
    }
    break;
    default:
    {
      std::cerr << "Morphomotion Error: Robot class." << std::endl
                << "std::string get_evaluation_method(void) method." << std::endl
                << "Evaluation Method: " << std::endl;
      exit(1);
    }
  }
}


void Robot::set_number_of_modules(unsigned int new_number_of_modules)
{
  if(new_number_of_modules > 0)
  {
    number_of_modules = new_number_of_modules;
  }
  else
  {
    std::cerr << "Morphomotion Error: Robot class." << std::endl
              << "void set_number_of_modules(int) method." << std::endl
              << "Number of modules must be greater than zero." << std::endl;
    exit(1);
  }
}


unsigned int Robot::get_number_of_modules(void) const
{
  return(number_of_modules);
}


double Robot::get_distance_travelled(void)
{
  if(evaluation_method == Euclidean_Distance_Final)
  {
    return(this->calculate_distance_travelled_euclidean());
  }
  else if(evaluation_method == Euclidean_Distance_Cumulative)
  {
    return(distance_travelled);
  }
  else
  {
    std::cerr << "Morphomotion Error: Robot class." << std::endl
              << "void get_distance_travelled(void) method." << std::endl
              << "Unknown Evaluation Method: " << evaluation_method << std::endl;
    exit(1);
  }
}
