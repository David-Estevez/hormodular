
#include <iostream>
#include <string>

#include "ModularRobot.h"
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"

using namespace hormodular;

int main(int argc, char * argv[] )
{
    //-- Extract data from arguments
    std::string config_file, gait_table_file;
    float frequency;
    int run_time;
    float timestep;

    if ( argc == 5 )
    {
        config_file = argv[1];
        gait_table_file = argv[2];
        frequency = atof(argv[3]);
        run_time = atoi(argv[4]);
        timestep = 0.25;
    }
    else if ( argc == 6)
    {
        config_file = argv[1];
        gait_table_file = argv[2];
        frequency = atof(argv[3]);
        run_time = atoi(argv[4]);
        timestep = atof(argv[5]);
    }
    else
    {
        std::cout << "Usage: evaluate-gaits-sim (config file) (gait-table) (frequency) (run time(ms)) [simulation step(ms)=2ms]" << std::endl;
        exit(-1);
    }

    //-- Load configuration on a ConfigParser
    hormodular::ConfigParser configParser;
    if ( configParser.parse(config_file) != 0)
    {
        std::cerr << "[Evaluate] Error: error parsing xml config file!" << std::endl;
        return false;
    }

    //-- Load gait table:
    GaitTable * gaitTable = new GaitTable(gait_table_file);

    //-- Create empty sinusoidal oscillators with the test parameters
    std::vector<Oscillator *> oscillators;
    std::vector<unsigned long> ids = configParser.getShapeIDs();
    for ( int i = 0; i < configParser.getNumModules(); i++)
    {
            std::vector<float> parameters = gaitTable->getParameters(ids[i]);
            oscillators.push_back(new SinusoidalOscillator(parameters[0], parameters[1], parameters[2],1000/frequency));
    }

    //-- Create joints
    std::vector<float> joint_values;

    //-- Create robot
    ModularRobotInterface * robotInterface = createModularRobotInterface( "simulated", configParser);
    robotInterface->reset();
    robotInterface->setProperty("viewer", "enabled");

    //-- Joint values set to 0:
    for ( int i = 0; i < configParser.getNumModules(); i++)
        joint_values.push_back(0);

    std::cout << "Evaluate-Gaits (simulated version)" << std::endl
              << "------------------------------------" << std::endl;

    //-- Time track:
    struct timeval starttime, endtime;
    gettimeofday( &starttime, NULL);

    //-- Run the robot:
    std::cout << "[Evaluate] Run!" << std::endl;

    //-- Here you put the main loop
    unsigned long elapsed_time = 0; //-- Should be in uS
    unsigned long max_time_us = run_time*1000;

    while( elapsed_time < max_time_us )
    {
        //-- Update joint values
        for ( int i = 0; i < (int) oscillators.size(); i++)
            joint_values[i] = oscillators[i]->calculatePos(elapsed_time);

        //-- Send joint values
        robotInterface->sendJointValues(joint_values, timestep);

        elapsed_time+=(unsigned long) (timestep*1000);
    }


    //-- Get actual elapsed time:
    gettimeofday(&endtime, NULL);

    int sec_diff = endtime.tv_sec-starttime.tv_sec;
    int usec_diff = endtime.tv_usec-starttime.tv_usec;
    if (usec_diff < 0)
    {
        usec_diff += 1000000;
        sec_diff -= 1;
    }

    //-- Report distance travelled:
    std::cout << "Distance travelled: " << robotInterface->getTravelledDistance() << std::endl;
    std::cout << "Robot time elapsed: " << (int) run_time << std::endl;
    std::cout << "Real time elapsed: " << sec_diff << "s " << usec_diff << "us " << std::endl;
    std::cout << std::endl;

    std::cout << "Finished!" << std::endl;

    //-- Cleanup
    robotInterface->destroy();
    delete robotInterface;
    robotInterface = NULL;

    for (int i = 0; i < configParser.getNumModules(); i++)
    {
        delete oscillators[i];
        oscillators[i] = NULL;
    }

    return 0;
}

