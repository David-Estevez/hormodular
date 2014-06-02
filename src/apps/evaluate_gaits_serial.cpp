#include <iostream>
#include <string>

#include "ModularRobot.h"


int main(int argc, char * argv[] )
{
    //-- Extract data from arguments
    std::string config_file;
    int run_time, step_time;

    if ( argc == 3 )
    {
        config_file = argv[1];
        run_time = atoi (argv[2] );
        step_time = 2;
    }
    else if ( argc == 4)
    {
        config_file = argv[1];
        run_time = atoi (argv[2] );
        step_time = atoi(argv[3]);
    }
    else
    {
        std::cout << "Usage: evaluate-gaits-serial (config file) (run time(ms)) [simulation step(ms)=2ms]" << std::endl;
        exit(-1);
    }

    //-- Load configuration on a ConfigParser
    hormodular::ConfigParser configParser;
    configParser.parse(config_file);

    //-- Create robot:
    hormodular::ModularRobot myRobot(configParser, "serial");
    myRobot.setTimeStep(step_time);

    std::cout << "Evaluate-Gaits (serial version)" << std::endl
              << "------------------------------------" << std::endl;

    //-- Reset robot:
    myRobot.reset();


    //-- Testing timing:
    struct timeval starttime, endtime;
    gettimeofday( &starttime, NULL);

    //-- Run controller
    myRobot.run(run_time);

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
    std::cout << "Robot time elapsed: " << (int) run_time << std::endl;
    std::cout << "Real time elapsed: " << sec_diff << "s " << usec_diff << "us " << std::endl;
    std::cout << std::endl;

    std::cout << "Finished!" << std::endl;

    return 0;
}

