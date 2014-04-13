//-----------------------------------------------------------------------------------
//-- SimulationOpenRAVE
//-----------------------------------------------------------------------------------
//--
//-- Class wrapping all the components of a OpenRAVE simulation
//--
//-----------------------------------------------------------------------------------
//--
//-- This file belongs to the Hormodular project
//-- (https://github.com/David-Estevez/hormodular.git)
//--
//-----------------------------------------------------------------------------------
//-- Author: David Estevez-Fernandez
//--
//-- Based on the 'TestBase' example from OpenMR ( https://github.com/Obijuan/openmr )
//-- made by Juan Gonzalez-Gomez
//--
//-- Released under the GPL license (more info on LICENSE.txt file)
//------------------------------------------------------------------------------------

#include "SimulationOpenRAVE.hpp"

hormodular::SimulationOpenRAVE::SimulationOpenRAVE(std::string environment_file, bool show_simulation)
{
    this->environment_file = environment_file;

    //-- Initialize OpenRAVE:
    OpenRAVE::RaveInitialize(true);

    //-- Create main environment:
    penv = OpenRAVE::RaveCreateEnvironment();
    //OpenRAVE::RaveSetDebugLevel(OpenRAVE::Level_Debug);
    penv->StopSimulation();

    //-- Run the viewer on a different thread, and wait for it to be ready:
    this->show_simulation = show_simulation;
    pthviewer = NULL;

    if ( show_simulation )
        showViewer();

    //-- Init (load and setup everything)
    init();
}

hormodular::SimulationOpenRAVE::~SimulationOpenRAVE()
{
    if (show_simulation && pthviewer != NULL)
    {
        //-- Wait for the viewer to finish
        pthviewer->join();
        delete pthviewer;
        pthviewer = NULL;
    }

    //-- Destroy the environment
    penv->Destroy();
    //std::cout << "[Debug] This is executed! -> ~SimulationOpenRAVE" << std::endl;
}


void hormodular::SimulationOpenRAVE::init()
{
    //-- Load the scene and wait for it to be ready:
    if ( !penv->Load( environment_file) )
    {
        penv->Destroy();
        exit(-1);
    }
    usleep(100000);

    //-- Get the robot from the environment
    penv->GetRobots( robots );
    std::cout << "[Debug] Loaded " << robots.size() << " robots." << std::endl;

    //-- Lock the environment mutex:
    OpenRAVE::EnvironmentMutex::scoped_lock lock(penv->GetMutex());

    //-- Create a servocontroller and attach it to the robots:
    for( int i = 0; i < (int) robots.size(); i++)
    {
        //-- Create a new servocontroller
        OpenRAVE::ControllerBasePtr pcontroller = OpenRAVE::RaveCreateController(penv, "servocontroller");

        std::vector<int> dofindices( robots[i]->GetDOF());
        for (int j = 0; j < (int) dofindices.size(); j++)
            dofindices[j] = j;

        //-- Attach it
        robots[i]->SetController(pcontroller, dofindices, 1);

        std::cout << "[Debug] Robot " << i << ", number of joints: " << dofindices.size() << std::endl;
    }

    //-- Unlock the environment mutex:
    lock.unlock();

    //-- Reset controller and wait:
    for( int i = 0; i < (int) robots.size(); i++)
        robots[i]->GetController()->Reset();
}



OpenRAVE::EnvironmentBasePtr hormodular::SimulationOpenRAVE::getPenv() const
{
    return penv;
}


std::vector<OpenRAVE::RobotBasePtr> hormodular::SimulationOpenRAVE::getRobots() const
{
    return robots;
}

OpenRAVE::RobotBasePtr hormodular::SimulationOpenRAVE::getRobot(int index) const
{
    return robots[index];
}


void hormodular::SimulationOpenRAVE::showViewer()
{
    this->show_simulation = true;
    pthviewer = new boost::thread(boost::bind(&hormodular::SimulationOpenRAVE::startViewer, this));
    usleep(200000);
}

void hormodular::SimulationOpenRAVE::start( OpenRAVE::dReal step_period, bool real_time)
{
    penv->StartSimulation(step_period, real_time );
}

void hormodular::SimulationOpenRAVE::stop()
{
    penv->StopSimulation();
}

void hormodular::SimulationOpenRAVE::step(OpenRAVE::dReal step_period)
{
    penv->StepSimulation( step_period);
}

void hormodular::SimulationOpenRAVE::reset()
{
    penv->Reset();

    init();
}

void hormodular::SimulationOpenRAVE::startViewer()
{
        //-- Create the viewer and attach it to the environment
        pviewer = OpenRAVE::RaveCreateViewer(penv, "qtcoin");
        BOOST_ASSERT(!!pviewer);
        penv->Add( pviewer);

        //-- Show viewer
        pviewer->main(show_simulation);
}


