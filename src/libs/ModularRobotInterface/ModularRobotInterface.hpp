//------------------------------------------------------------------------------
//-- ModularRobotInterface
//------------------------------------------------------------------------------
//--
//-- Base class for different types of modular robots for modular robotics
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

#ifndef MODULAR_ROBOT_INTERFACE_H
#define MODULAR_ROBOT_INTERFACE_H

#include <iostream>

#include "ConfigParser.h"

namespace hormodular {

class ModularRobotInterface
{
    public:
        virtual bool start() = 0;
        virtual bool stop() = 0;
        virtual bool destroy() = 0;
        virtual bool reset() = 0;

        virtual float getTravelledDistance() = 0;
        virtual bool sendJointValues(std::vector<float> joint_values, int step_ms=0) = 0;
        virtual std::vector<float> getJointValues() = 0;

};


}

#endif //-- MODULAR_ROBOT_INTERFACE_H
