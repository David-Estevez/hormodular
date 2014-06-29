//------------------------------------------------------------------------------
//-- ModularRobot
//------------------------------------------------------------------------------
//--
//-- Modular robot for modular robotics
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

/*! \file ModularRobot.h
 *  \brief Modular robot for modular robotics
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

#ifndef MODULAR_ROBOT_H
#define MODULAR_ROBOT_H

#include "ConfigParser.h"
#include "Module.hpp"
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"

namespace hormodular {

/*!
 *  \class ModularRobot
 *  \brief Modular robot for modular robotics
 *
 *  ModularRobot class contains all the modules that form the modular robot, and
 *  it is in charge of executing the modules controllers, emulating a concurrent
 *  distributed system.
 */

class ModularRobot
{
    public:
        /*!
         * \brief Creates a ModularRobot, specifying the type of robot to be created
         * \param configParser ConfigParser object containing the robot configuration
         * \param robotInterfaceType Optional parameter specifying the type of robot to
         * which the ModularRobot will be connected, either a simulated robot (default)
         * or a real robot connected via serial port.
         */
        ModularRobot(ConfigParser configParser, std::string robotInterfaceType="simulated");
        ~ModularRobot();



        /*!
         * \brief Runs the modular robot distributed controller for a given amount of time.
         * \param runTime Amount of time (in ms) the controller will be run.
         * \return True if completed successfully, false otherwise
         */
        bool run(unsigned long runTime);

        /*!
         * \brief Resets the initial state of the robot.
         *
         * It should be used after run() if the robot is to be run again.
         *
         * \return True if completed successfully, false otherwise
         */
        bool reset();


        bool setTimeStep(float step_ms);
        bool setProperty(std::string property, std::string value);

        float getTravelledDistance();

        static const int COMMUNICATION_PERIOD_MS = 100;

   private:
        /*!
         * \brief Function that performs the connections between the different connectors of the
         * different modules.
         *
         * These connections are based on the configuration from the ConfigParser.
         *
         * \return True if completed successfully, false otherwise
         */
        bool attachModules();

        ConfigParser configParser;
        std::vector<Module *> modules;
        ModularRobotInterface * robotInterface;

        //! \brief Time elapsed, expressed in us
        unsigned long elapsed_time;

        //! \brief Simulation / robot communication step time, expressed in ms
        float step_ms;

        std::vector<float> joint_values;
};
}
#endif //-- MODULAR_ROBOT_H
