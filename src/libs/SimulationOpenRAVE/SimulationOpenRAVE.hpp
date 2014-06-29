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


/*! \file SimulationOpenRAVE.hpp
 *  \brief Class wrapping all the components of a OpenRAVE simulation
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */


#ifndef SIMULATION_OPENRAVE_H
#define SIMULATION_OPENRAVE_H

#include <openrave-core.h>
#include <boost/thread/thread.hpp>
#include <boost/bind.hpp>

#include <iostream>
#include <vector>
#include <string>

namespace hormodular {

/*!
 *  \class SimulationOpenRAVE
 *  \brief Class wrapping all the components of a OpenRAVE simulation
 */
class SimulationOpenRAVE
{
    public:
        /*!
         * \brief Creates a SimulationOpenRAVE using the environment defined in the environment_file
         * \param environment_file Path to the XML file defining the OpenRAVE simulation environment
         * \param show_simulation If true (default value), enables the simulation viewer
         */
        SimulationOpenRAVE( std::string environment_file , bool show_simulation = true);
        ~SimulationOpenRAVE();


         //! \brief Loads the environment and sets everything needed
        void init();


        OpenRAVE::EnvironmentBasePtr getPenv() const;
        std::vector<OpenRAVE::RobotBasePtr> getRobots() const;
        OpenRAVE::RobotBasePtr getRobot( int index = 0) const;


        //! \brief Starts the dedicated thread for the viewer and calls the startViewer function to create a viewer
        void showViewer();

        //! \brief Starts the simulation with a given period (in s) that can be run in real time
        void start(OpenRAVE::dReal step_period, bool real_time = true);

        //! \brief Stops the simulation
        void stop();

        //! \brief Advances the simulation only a step of the specified duration
        void step( OpenRAVE::dReal step_period);

        //! \brief Resets the simulation, reloading the environment, robots and controllers
        void reset();

private:
        //! \brief Creates a viewer and attaches it to the environment
        void startViewer();
        std::string environment_file;
        OpenRAVE::EnvironmentBasePtr penv;
        OpenRAVE::ViewerBasePtr pviewer;
        boost::thread * pthviewer;
        std::vector< OpenRAVE::RobotBasePtr > robots;
        bool show_simulation;
};
}

#endif //-- SIMULATION_OPENRAVE_H
