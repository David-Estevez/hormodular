//------------------------------------------------------------------------------
//-- ModularRobotInterface
//------------------------------------------------------------------------------
//--
//-- Abstract class for different types of interfaces with modular robots
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

#include "ModularRobotInterface.hpp"


bool hormodular::ModularRobotInterface::setProperty(std::string property, std::string value)
{
    //-- By default, it does nothing
    return false;
}
