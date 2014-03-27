#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <inttypes.h>
#include <semaphore.h>
#include <pthread.h>

#include "Module.h"
#include "SimulatedModule.h"

//-- Testing timing
#include <sys/time.h>

//#define DEBUG_MESSAGES

void startViewer( OpenRAVE::EnvironmentBasePtr penv,  bool showgui );
void * updateTime( void * args);

struct UpdateTimeArgs {
    std::vector<Module*> pmodules;
    OpenRAVE::EnvironmentBasePtr penv;
    sem_t* updateTime_sem;
    sem_t *modules_sem;
};

int main(int argc, char * argv[] )
{
    //-- Config data:
    std::string scene_file;
    if ( argc == 2 )
        scene_file = argv[1];
    else
        //scene_file = "../../../../data/models/Unimod1.env.xml";
        scene_file = "../../../../data/models/Minicube-II.env.xml";

    //-- Initialize OpenRAVE:
    OpenRAVE::RaveInitialize(true);

    //-- Create main environment:
    OpenRAVE::EnvironmentBasePtr penv = OpenRAVE::RaveCreateEnvironment();
    OpenRAVE::RaveSetDebugLevel(OpenRAVE::Level_Debug);
    penv->StopSimulation();

    //-- Run the viewer on a different thread, and wait for it to be ready:
    boost::thread * pthviewer = new boost::thread(&startViewer, penv, true);
    usleep(200000);

    //-- Load the scene and wait for it to be ready:
    if ( !penv->Load( scene_file))
    {
        penv->Destroy();
        exit(-1);
    }
    usleep(100000);

    //-- Get the robot from the environment
    std::vector< OpenRAVE::RobotBasePtr > all_robots;
    penv->GetRobots( all_robots);
    OpenRAVE::RobotBasePtr probot = all_robots[0];
    std::cout << "Loaded " << all_robots.size() << " robots" << std::endl
              <<"Selected: " << probot->GetName() << std::endl;

    //-- Lock the environment mutex:
    OpenRAVE::EnvironmentMutex::scoped_lock lock(penv->GetMutex());

    //-- Create a servocontroller and attach it to the robot:
    OpenRAVE::ControllerBasePtr pcontroller = OpenRAVE::RaveCreateController(penv, "servocontroller");
    std::vector<int> dofindices( probot->GetDOF());
    for (int i = 0; i < (int) dofindices.size(); i++)
        dofindices[i] = i;
    probot->SetController(pcontroller, dofindices, 1);
    std::cout << "Number of joints: " << dofindices.size() << std::endl;

    //-- Unlock the environment mutex:
    lock.unlock();

    //-- Send a simple command to the robot:
    //-------------------------------------------------------------------------------------------------
    pcontroller->Reset();
//    penv->StartSimulation(0.0025, true);

      std::cin.get();
      std::cout << "Start!" << std::endl;

//    std::stringstream is,os;
//    is << "Setpos1 0 90";
//    pcontroller->SendCommand(os, is);

//    sleep(3);

//    //-- Get actual dof values:
//    std::stringstream is2, os2;
//    is2 << "getpos1 0";
//    pcontroller->SendCommand(os2, is2);
//    float value = 1.23456; os2 >> value;
//    std::cout << "Values: " << value << std::endl;

//    penv->StopSimulation();

    //---------------------------------------------------------------------------------------------------
    //-- Run individual modules:
    //---------------------------------------------------------------------------------------------------
    //-- Module required arguments:

    //-- Gait table:
    std::string gait_table_file = "../../../../data/gait tables/gait_table_straight_3_modules_pyp.txt";

    //-- Create sync semaphores
    sem_t updateTime_sem;
    sem_init( &updateTime_sem, 0, 0);

    sem_t module_sem_vector[ probot->GetDOF()];
    for( int i = 0; i < probot->GetDOF(); i++)
        sem_init( module_sem_vector+i, 0, 1);

    //-- Create modules:

    std::vector<Module*> robot_modules;
    for( int i = 0; i< probot->GetDOF(); i++)
    {
        std::vector<sem_t* > temp_sem_vector;
        std::vector<int> temp_indices;
        temp_sem_vector.push_back( module_sem_vector+i);
        temp_indices.push_back(dofindices[i]);
        Module * temp_module;
        //! \todo Update this to use 2 gait tables:
        temp_module = new SimulatedModule(1, gait_table_file, gait_table_file, pcontroller, temp_indices, &updateTime_sem, temp_sem_vector);
        assert(false);
        robot_modules.push_back((Module *) temp_module);
    }

    //-- Reset modules
    for(int i = 0; i < probot->GetDOF(); i++)
    {
        robot_modules[i]->reset();
        //! \todo Update this to use 2 gait tables:
        //robot_modules[i]->setID( (uint8_t) i);
        assert(false);
    }

    //-- Record initial position:
    OpenRAVE::Vector start_pos = probot->GetCenterOfMass();

    //-- Run modules
    for(int i = 0; i < probot->GetDOF(); i++)
        robot_modules[i]->run( 15000); //-- 20000 ms

    pthread_t updateTime_thread;
    struct UpdateTimeArgs updateTimeArgs;
    updateTimeArgs.penv = penv;
    updateTimeArgs.pmodules = robot_modules;
    updateTimeArgs.updateTime_sem = &updateTime_sem;
    updateTimeArgs.modules_sem = module_sem_vector;
    pthread_create( &updateTime_thread, NULL, &updateTime, (void *) &updateTimeArgs );

    pthread_join( updateTime_thread, NULL );

    //-- Record final position:
    OpenRAVE::Vector end_pos = probot->GetCenterOfMass();
    OpenRAVE::Vector distance_travelled = end_pos - start_pos;
    std::cout << "Distance travelled: " << sqrt( pow(distance_travelled.x, 2) + pow( distance_travelled.y, 2)) << std::endl;


    //-- Run it again: --------------------
    for(int j = 0; j < 9; j++) {
    //-- Reset modules
    for(int i = 0; i < probot->GetDOF(); i++)
    {
        robot_modules[i]->reset();
        //!\Change this to work with 2 gait tables
        //robot_modules[i]->setID( (uint8_t) i);
        assert(false);
    }

    //-- Record initial position:
    start_pos = probot->GetCenterOfMass();

    //-- Run modules
    for(int i = 0; i < probot->GetDOF(); i++)
        robot_modules[i]->run( 15000); //-- 20000 ms

    pthread_create( &updateTime_thread, NULL, &updateTime, (void *) &updateTimeArgs );
    pthread_join( updateTime_thread, NULL );

    //-- Record final position:
    end_pos = probot->GetCenterOfMass();
    distance_travelled = end_pos - start_pos;
    std::cout << "Distance travelled: " << sqrt( pow(distance_travelled.x, 2) + pow( distance_travelled.y, 2)) << std::endl;

    }
    //-- Wait for the viewer to be closed:
    pthviewer->join();

    //-- Clean up things:
    for( int i = 0; i< probot->GetDOF(); i++)
        delete robot_modules[probot->GetDOF()-1-i];

    delete pthviewer;
    penv->Destroy();
    std::cout << "Exiting..." << std::endl;

    return 0;
}


void startViewer( OpenRAVE::EnvironmentBasePtr penv,  bool showgui )
{
    //-- Create the viewer and attach it to the environment
    OpenRAVE::ViewerBasePtr viewer= OpenRAVE::RaveCreateViewer(penv, "qtcoin");
    BOOST_ASSERT(!!viewer);
    penv->Add( viewer);

    //-- Show viewer
    viewer->main(showgui);
}


void * updateTime( void * args)
{
    static const int RUNTIME_S = 15;
    static const float STEP_MS = 2;

    //-- Get the args:
    struct UpdateTimeArgs * updateTimeArgs = (struct UpdateTimeArgs *) args;

    uint32_t time = 0;
    std::vector<Module*> pmodules = updateTimeArgs->pmodules;
    OpenRAVE::EnvironmentBasePtr penv = updateTimeArgs->penv;
    sem_t * updateTime_sem = updateTimeArgs->updateTime_sem;
    sem_t* pmodule_sem_vector = updateTimeArgs->modules_sem;

    //-- Testing timing:
    struct timeval starttime, endtime;
    gettimeofday( &starttime, NULL);

    while (time < RUNTIME_S*1000)
    {
        //-- Lock this thread semaphores:
        for (int i = 0; i < (int) pmodules.size(); i++)
            sem_wait( updateTime_sem);

        //-- Increment time
        for(int i = 0; i < (int) pmodules.size(); i++)
            pmodules.at(i)->incrementTime( STEP_MS); //-- 2ms

        //-- Update simulation
        penv->StepSimulation( STEP_MS / 1000.0);

        //-- Unlock modules threads:
        for (int i = 0; i < (int) pmodules.size(); i++)
            sem_post( pmodule_sem_vector+i);

        //-- Increment time counter
        time += STEP_MS;

        //-- Wait for time period
        //usleep( 1000*STEP_MS);

#ifdef DEBUG_MESSAGES
        //-- Print time:
        std::cout << "[Debug] Current time: " << time << std::endl;
        std::cout.flush();
#endif
    }

    gettimeofday(&endtime, NULL);

    std::cout << "Time up!" << std::endl;
    //std::cout << "Start time: " << starttime.tv_sec << "s " << starttime.tv_usec << "us" << std::endl;
    //std::cout << "End time: " << endtime.tv_sec << "s " << endtime.tv_usec << "us" << std::endl;
    int sec_diff = endtime.tv_sec-starttime.tv_sec;
    int usec_diff = endtime.tv_usec-starttime.tv_usec;
    if (usec_diff < 0)
    {
        usec_diff += 1000000;
        sec_diff -= 1;
    }
    std::cout << "Runtime selected: " << RUNTIME_S << "s" << std::endl;
    std::cout << "Actual runtime: " << sec_diff << "." << usec_diff << "s" << std::endl;

    return NULL;
}
