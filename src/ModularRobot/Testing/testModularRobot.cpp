#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <inttypes.h>
#include <semaphore.h>
#include <pthread.h>

#include "../ModularRobot.h"
#include "../Module/Module.h"
#include "../Module/SimulatedModule.h"
#include "../SimulatedModularRobot.h"
#include "../SimulationOpenRAVE.h"

//-- Testing timing
#include <sys/time.h>

//#define DEBUG_MESSAGES

int main(int argc, char * argv[] )
{
    //-- Config data:
    std::string scene_file;
    if ( argc == 2 )
        scene_file = argv[1];
    else
        //scene_file = "../../../../data/models/Unimod1.env.xml";
        scene_file = "../../../../data/models/Minicube-II.env.xml";
        //scene_file = "../../../../data/models/Cube5-I.env.xml";


    //---------------------------------------------------------------------------------------------------
    //-- Create robot:
    //---------------------------------------------------------------------------------------------------
    //-- Gait table:
    std::string gait_table_file = "../../../../data/gait tables/gait_table_straight_3_modules_pyp.txt";
    //std::string gait_table_file = "../../../../data/gait tables/test_gait_5.txt";

    //-- Create robot:
    SimulatedModularRobot myRobot( scene_file, gait_table_file);
    myRobot.setTimeStep( 1);
    myRobot.setMaxRuntime( 10000);
    myRobot.selectDistanceCalculationMethod( ModularRobot::START_END_POINTS );
    myRobot.showSimulationViewer();

    //-- Create variables to store simulation results:
    std::vector< double > run_times;
    std::vector< double > distances;


    //-- Start simulation:
    std::cout << "Press key to start..." << std::endl;
    std::cin.get();
    std::cout << "Start!" << std::endl;

    for (int i=0; i < 20; i++)
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

        //-- Report distance travelled:
        std::cout << "Distance travelled: " << myRobot.getDistanceTravelled() << std::endl;
        std::cout << "Robot time elapsed: " << (int) myRobot.getTimeElapsed() << std::endl;
        std::cout << "Real time elapsed: " << sec_diff << "s " << usec_diff << "us " << std::endl;
        std::cout << std::endl;

        //-- Record data:
        run_times.push_back( sec_diff + usec_diff / 1000000.0);
        distances.push_back( myRobot.getDistanceTravelled() );
    }

    //-- Calculate statistics: ( http://stackoverflow.com/questions/7616511/calculate-mean-and-standard-deviation-from-a-vector-of-samples-in-c-using-boos )
    //-- Actual run times:
    double sum_run_times = std::accumulate( run_times.begin(), run_times.end(), 0.0);
    double mean_run_times = sum_run_times / run_times.size();

    double sq_sum_run_times = std::inner_product( run_times.begin(), run_times.end(), run_times.begin(), 0.0);
    double stdev_run_times = std::sqrt(sq_sum_run_times / run_times.size() - mean_run_times * mean_run_times);

    //-- Distances:
    double sum_distances = std::accumulate( distances.begin(), distances.end(), 0.0);
    double mean_distances = sum_distances / distances.size();

    double sq_sum_distances = std::inner_product( distances.begin(), distances.end(), distances.begin(), 0.0);
    double stdev_distances = std::sqrt(sq_sum_distances / distances.size() - mean_distances * mean_distances);

    std::cout << "Statistics report" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "Runned " << run_times.size() << " simulations for " << 10000 << " ms each." << std::endl << std::endl;
    std::cout << "Average actual run time: " << mean_run_times << "s. " << std::endl;
    std::cout << "Std. Dev. actual run time: " << stdev_run_times << "s. " << std::endl;
    std::cout << std::endl;
    std::cout << "Average distance travelled: " << mean_distances << " units." << std::endl;
    std::cout << "Std. Dev. distace travelled: " << stdev_distances << " units. " << std::endl << std::endl;

    std::cout << "Exiting..." << std::endl;

    return 0;
}

