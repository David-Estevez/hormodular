//------------------------------------------------------------------------------
//-- ModularRobotInterfaceFactory
//------------------------------------------------------------------------------
//--
//-- Creates different modular robot interfaces that follow the
//-- ModularRobotInterface interface
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

#ifndef MODULAR_ROBOT_INTERFACE_FACTORY_H
#define MODULAR_ROBOT_INTERFACE_FACTORY_H

#include <string>

#include "ModularRobotInterface.hpp"
#include "SimulatedModularRobotInterface.hpp"
#include "ConfigParser.h"

namespace hormodular {

ModularRobotInterface * createModularRobotInterface( std::string type, ConfigParser configParser);

}

#endif //-- MODULAR_ROBOT_INTERFACE_FACTORY_H
