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

/*! \file ModularRobotInterfaceFactory.hpp
 *  \brief Creates different modular robot interfaces that follow the
 *   ModularRobotInterface interface
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

#ifndef MODULAR_ROBOT_INTERFACE_FACTORY_H
#define MODULAR_ROBOT_INTERFACE_FACTORY_H

#include <string>

#include "ModularRobotInterface.hpp"
#include "SimulatedModularRobotInterface.hpp"
#include "SerialModularRobotInterface.hpp"
#include "ConfigParser.h"

namespace hormodular {

/*!
 * \brief Creates different modular robot interfaces that follow the ModularRobotInterface interface
 * \param type Type of ModularRobotInterface to be created. Currently, only "simulated" or "serial"
 * are supported.
 * \param configParser ConfigParser containing the ModularRobotInterface configuration.
 * \return Pointer to the new ModularRobotInterface created.
 */
ModularRobotInterface * createModularRobotInterface( std::string type, ConfigParser configParser);

}

#endif //-- MODULAR_ROBOT_INTERFACE_FACTORY_H
