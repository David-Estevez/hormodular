#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <inttypes.h>
#include <semaphore.h>
#include <pthread.h>

#include "SimulatedModularRobot.h"

//#define DEBUG_MESSAGES

int main(int argc, char * argv[] )
{
    //-- Extract data from arguments
    std::string scene_file, gait_table_file;
    int run_time, step_time;

    if ( argc == 4 )
    {
        scene_file = argv[1];
        gait_table_file = argv[2];
        run_time = atoi (argv[3] );
        step_time = 2;
    }
    else if ( argc == 5)
    {
        scene_file = argv[1];
        gait_table_file = argv[2];
        run_time = atoi (argv[3] );
        step_time = atoi(argv[4]);
    }
    else
    {
        std::cout << "Usage: evaluate-gaits-sim [scene file] [gait table file] [run time(ms)] [simulation step(ms)]" << std::endl;
        exit(-1);
    }

    //-- Create robot:
    SimulatedModularRobot myRobot( scene_file, gait_table_file);
    myRobot.setTimeStep( step_time);
    myRobot.setMaxRuntime( run_time );
    myRobot.selectDistanceCalculationMethod( ModularRobot::START_END_POINTS );
    myRobot.showSimulationViewer();


    std::cout << "Evaluate-Gaits (simulated version)" << std::endl
              << "------------------------------------" << std::endl;

    //-- Reset robot:
    myRobot.reset();

    //-- Testing timing:
    struct timeval starttime, endtime;
    gettimeofday( &starttime, NULL);

    //-- Run controller
    myRobot.run();

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
    std::cout << "Distance travelled: " << myRobot.getDistanceTravelled() << std::endl;
    std::cout << "Robot time elapsed: " << (int) myRobot.getTimeElapsed() << std::endl;
    std::cout << "Real time elapsed: " << sec_diff << "s " << usec_diff << "us " << std::endl;
    std::cout << std::endl;

    std::cout << "Finished!" << std::endl;

    return 0;
}

