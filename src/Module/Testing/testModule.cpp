#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <string>
#include <inttypes.h>

#include "../Module.h"


void startViewer( OpenRAVE::EnvironmentBasePtr penv,  bool showgui );
void * updateTime( void * args);

struct UpdateTimeArgs {
    Module * pmodule;
    OpenRAVE::EnvironmentBasePtr penv;
};

int main(int argc, char * argv[] )
{
    //-- Config data:
    std::string scene_file;
    if ( argc == 2 )
        scene_file = argv[1];
    else
        scene_file = "../../../../data/models/Unimod1.env.xml";

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
    penv->StartSimulation(0.0025, true);

    std::cin.get();
    std::cout << "Start!" << std::endl;

    std::stringstream is,os;
    is << "Setpos1 0 90";
    pcontroller->SendCommand(os, is);

    sleep(3);

    //-- Get actual dof values:
    std::stringstream is2, os2;
    is2 << "getpos1 0";
    pcontroller->SendCommand(os2, is2);
    float value = 1.23456; os2 >> value;
    std::cout << "Values: " << value << std::endl;

    penv->StopSimulation();

    //---------------------------------------------------------------------------------------------------
    //-- Alt actions with Module:
    //---------------------------------------------------------------------------------------------------
    //-- Create a module:
    std::string gait_table_file = "../../../../data/gait tables/gait_table_straight_3_modules_pyp.txt";
    Module module( SimulatedModule,  probot->GetDOF(), gait_table_file, pcontroller );

    module.reset();
    module.run( 20000); //-- 2000 ms

    pthread_t updateTime_thread;
    struct UpdateTimeArgs updateTimeArgs;
    updateTimeArgs.penv = penv;
    updateTimeArgs.pmodule = &module;
    pthread_create( &updateTime_thread, NULL, &updateTime, (void *) &updateTimeArgs );

    pthread_join( updateTime_thread, NULL );

    //--------------------------------------------------------------------------------------------------


    //-- Wait for the viewer to be closed:
    pthviewer->join();

    //-- Clean up things:
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
    //-- Get the args:
    struct UpdateTimeArgs * updateTimeArgs = (struct UpdateTimeArgs *) args;

    uint32_t time = 0;
    Module * pmodule = updateTimeArgs->pmodule;
    OpenRAVE::EnvironmentBasePtr penv = updateTimeArgs->penv;

    while (time < 20000)
    {
        //-- Increment time
        pmodule->incrementTime( 2); //-- 2ms

        //-- Update simulation
        penv->StepSimulation( 0.002);

        //-- Increment time counter
        time += 2;

        //-- Wait for time period
        usleep( 1000*2);

        //-- Print time:
        std::cout << "Current time: " << time << std::endl;
    }
    std::cout << "I'm supposed to increment time here." << std::endl;

    return NULL;
}
