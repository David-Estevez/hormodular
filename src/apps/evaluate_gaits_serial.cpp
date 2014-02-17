#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <inttypes.h>
#include <semaphore.h>
#include <pthread.h>

#include "SerialModularRobot.h"

//#define DEBUG_MESSAGES

int main(int argc, char * argv[] )
{
    //-- Extract data from arguments
    std::string serial_port, gait_table_file;
    int n_modules, run_time;

    if ( argc == 5 )
    {
        n_modules = atoi( argv[1]);
        serial_port = argv[2];
        gait_table_file = argv[3];
        run_time = atoi (argv[4] );
    }
    else
    {
        std::cout << "Usage: evaluate-gaits-serial [number of modules] [serial port] [gait table file] [run time(ms)]" << std::cout;
        exit(-1);
    }

    //-- Create robot:
    SerialModularRobot myRobot(  serial_port, n_modules, gait_table_file);
    myRobot.setTimeStep( 25);
    myRobot.setMaxRuntime( run_time );


    std::cout << "Evaluate-Gaits (serial version)" << std::endl
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
    std::cout << "Robot time elapsed: " << (int) myRobot.getTimeElapsed() << std::endl;
    std::cout << "Real time elapsed: " << sec_diff << "s " << usec_diff << "us " << std::endl;
    std::cout << std::endl;

    std::cout << "Finished!" << std::endl;

    return 0;
}

