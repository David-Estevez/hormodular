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


    //---------------------------------------------------------------------------------------------------
    //-- Create robot:
    //---------------------------------------------------------------------------------------------------
    //-- Gait table:
    std::string gait_table_file = "../../../../data/gait tables/gait_table_straight_3_modules_pyp.txt";

    //-- Create robot:
    SimulatedModularRobot myRobot( scene_file, gait_table_file);
    myRobot.setTimeStep( 1);
    myRobot.setMaxRuntime( 20000);
    myRobot.selectDistanceCalculationMethod( ModularRobot::START_END_POINTS );
    myRobot.showSimulationViewer();

    std::cout << "Press key to start..." << std::endl;
    std::cin.get();
    std::cout << "Start!" << std::endl;

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
    std::cout << "Robot time elapsed:" << myRobot.getTimeElapsed() << std::cout;
    std::cout << "Real time elapsed:" << sec_diff << "s " << usec_diff << "us " << std::endl;

    std::cout << "Exiting..." << std::endl;

    return 0;
}
