#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <inttypes.h>
#include <semaphore.h>
#include <pthread.h>

#include "SimulatedModularRobot.h"
#include "SerialModularRobot.h"


//-- Testing timing
#include <sys/time.h>

//#define DEBUG_MESSAGES

int main(int argc, char * argv[] )
{
    //-- Config data:
    std::string serial_port_name;
    if ( argc == 2 || argc == 3 )
        serial_port_name = argv[1];
    else
        serial_port_name = "/dev/ttyUSB0";


    //---------------------------------------------------------------------------------------------------
    //-- Create robot:
    //---------------------------------------------------------------------------------------------------
    //-- Gait table:
    std::string gait_table_file;
    if ( argc == 3 )
        gait_table_file = argv[2];
    else
        gait_table_file = "../../../../data/gait tables/gait_table_straight_3_modules_pyp.txt";
    //std::string gait_table_file = "../../../../data/gait tables/test_gait_5.txt";



    //-- Create robot:
    SerialModularRobot myRobot( serial_port_name,3, gait_table_file);
    myRobot.setTimeStep( 20);
    myRobot.setMaxRuntime( 10000);
    myRobot.selectDistanceCalculationMethod( ModularRobot::START_END_POINTS );

    //-- Create variables to store results:
    std::vector< double > run_times;

    //-- Start simulation:
    std::cout << "Press key to start..." << std::endl;
    std::cin.get();
    std::cout << "Start!" << std::endl;

    for (int i=0; i < 10; i++)
    {
        std::cout << "Run #" << i << std::endl;

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

        std::cout << "Robot time elapsed: " << (int) myRobot.getTimeElapsed() << std::endl;
        std::cout << "Real time elapsed: " << sec_diff << "s " << usec_diff << "us " << std::endl;
        std::cout << std::endl;

        //-- Record data:
        run_times.push_back( sec_diff + usec_diff / 1000000.0);
    }

    //-- Calculate statistics: ( http://stackoverflow.com/questions/7616511/calculate-mean-and-standard-deviation-from-a-vector-of-samples-in-c-using-boos )
    //-- Actual run times:
    double sum_run_times = std::accumulate( run_times.begin(), run_times.end(), 0.0);
    double mean_run_times = sum_run_times / run_times.size();

    double sq_sum_run_times = std::inner_product( run_times.begin(), run_times.end(), run_times.begin(), 0.0);
    double stdev_run_times = std::sqrt(sq_sum_run_times / run_times.size() - mean_run_times * mean_run_times);

    std::cout << "Statistics report" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Runned " << run_times.size() << " simulations for " << 10000 << " ms each." << std::endl << std::endl;
    std::cout << "Average actual run time: " << mean_run_times << "s. " << std::endl;
    std::cout << "Std. Dev. actual run time: " << stdev_run_times << "s. " << std::endl;
    std::cout << std::endl;
    std::cout << "Exiting..." << std::endl;

    return 0;
}

