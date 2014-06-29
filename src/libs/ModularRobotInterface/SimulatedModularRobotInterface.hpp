//------------------------------------------------------------------------------
//-- SimulatedModularRobotInterface
//------------------------------------------------------------------------------
//--
//-- Interface to the simulated robot
//--
//------------------------------------------------------------------------------
//--
//-- This file belongs to the Hormodular project
//-- (https://github.com/David-Estevez/hormodular.git)
//--
//------------------------------------------------------------------------------
//-- Author: David Estevez-Fernandez
//--
//-- Released under the GPL license (more info on LICENSE.txt file)
//------------------------------------------------------------------------------


/*! \file SimulatedModularRobotInterface.hpp
 *  \brief  Interface to the simulated robot
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */


#ifndef SIMULATED_MODULAR_ROBOT_INTERFACE_H
#define SIMULATED_MODULAR_ROBOT_INTERFACE_H

#include "ModularRobotInterface.hpp"
#include "SimulationOpenRAVE.hpp"
#include "ConfigParser.h"

namespace hormodular {

/*!
 *  \class SimulatedModularRobotInterface
 *  \brief  Interface to the simulated robot
 */

class SimulatedModularRobotInterface : public ModularRobotInterface
{
    public:
        SimulatedModularRobotInterface( ConfigParser configParser);


        /*!
         * \brief Starts the simulation
         * \return True if completed successfully, false otherwise
         */
        virtual bool start();

        /*!
         * \brief Stops the simulation
         * \return True if completed successfully, false otherwise
         */
        virtual bool stop();

        /*!
         * \brief Frees all the dynamically allocated memory
         * \return True if completed successfully, false otherwise
         */
        virtual bool destroy();

        /*!
         * \brief Resets the simulation, returning the robot to the initial position
         * \return True if completed successfully, false otherwise
         */
        virtual bool reset();



        /*!
         * \brief Configure a property or parameter of the interface
         * \param property Property to be changed. Currently, only the "viewer" property
         * is available, which controls the visibility of the OpenRAVE viewer.
         * \param value Value to be set on the property. For "viewer", the only
         * available value is "enable".
         * \return True if completed successfully, false otherwise
         */
        virtual bool setProperty(std::string property, std::string value);



        /*!
         * \brief Returns the distance travelled by the simulated modular robot
         *
         * This distance is not the actual distance travelled, but the point-to-point
         * distance between the initial point and the final point.
         *
         */
        virtual float getTravelledDistance();

        //! \brief Sends the specified joint position values to the simulated modular robot servocontroller
        virtual bool sendJointValues(std::vector<float> joint_values, float step_ms=0);

        //! \brief Returns the actual joint position values of the simulated modular robot
        virtual std::vector<float> getJointValues();

    private:
        SimulationOpenRAVE * simulation;
        std::string environment_file;
        OpenRAVE::ControllerBasePtr controller;

        int step_ms;
        double step_s;

        //-- Position-related things:

        //! \brief Gets robot position and stores it on the current_pos variable
        void calculatePos();

        std::pair<float, float> start_pos;
        std::pair<float, float> current_pos;
};

}

#endif
