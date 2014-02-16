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

#ifndef SIMULATION_OPENRAVE_H
#define SIMULATION_OPENRAVE_H

#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <vector>
#include <string>

class Simulation_OpenRAVE
{
    public:
        Simulation_OpenRAVE( std::string environment_file , bool show_simulation = true);
        ~Simulation_OpenRAVE();

        void init(); //-- Loads the environment and sets everything needed

        OpenRAVE::EnvironmentBasePtr getPenv() const;
        std::vector<OpenRAVE::RobotBasePtr> getRobots() const;
        OpenRAVE::RobotBasePtr getRobot( int index = 0) const;

        void showViewer( );

        void start(OpenRAVE::dReal step_period, bool real_time = true);
        void stop();
        void step( OpenRAVE::dReal step_period);
        void reset();

private:
        void startViewer();
        std::string environment_file;
        OpenRAVE::EnvironmentBasePtr penv;
        OpenRAVE::ViewerBasePtr pviewer;
        boost::thread * pthviewer;
        std::vector< OpenRAVE::RobotBasePtr > robots;
        bool show_simulation;
};

#endif //-- SIMULATION_OPENRAVE_H
