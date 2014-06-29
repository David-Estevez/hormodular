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

#include "ModularRobotInterfaceFactory.hpp"

hormodular::ModularRobotInterface *hormodular::createModularRobotInterface(std::string type, ConfigParser configParser)
{
    if ( type == "simulated")
        return (ModularRobotInterface*) new SimulatedModularRobotInterface(configParser);
    else if (type == "serial")
        return (ModularRobotInterface*) new SerialModularRobotInterface(configParser);
    else
    {
        std::cerr << "[Error][ModularRobotInterface] Could not create robot with type: \"" << type << "\"" << std::endl;
        return (ModularRobotInterface * ) NULL;
    }
}
