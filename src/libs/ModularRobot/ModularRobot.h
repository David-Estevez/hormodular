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

#ifndef MODULAR_ROBOT_H
#define MODULAR_ROBOT_H

#include "ConfigParser.h"
#include "Module.hpp"
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"

namespace hormodular {

class ModularRobot
{
    public:
        ModularRobot(ConfigParser configParser, std::string robotInterfaceType="simulated");
        ~ModularRobot();

        bool run(unsigned long runTime);
        bool reset();

        bool setTimeStep(float step_ms);
        bool setProperty(std::string property, std::string value);

        float getTravelledDistance();

        static const int COMMUNICATION_PERIOD_MS = 100;

   private:
        bool attachModules();

        ConfigParser configParser;
        std::vector<Module *> modules;
        ModularRobotInterface * robotInterface;

        unsigned long elapsed_time; //-- This is expressed in us
        float step_ms;
        std::vector<float> joint_values;
};
}
#endif //-- MODULAR_ROBOT_H
