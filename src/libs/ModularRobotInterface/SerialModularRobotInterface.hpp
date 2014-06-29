//------------------------------------------------------------------------------
//-- SerialModularRobotInterface
//------------------------------------------------------------------------------
//--
//-- Interface to the modular robot via serial port
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

#ifndef SERIAL_MODULAR_ROBOT_INTERFACE_H
#define SERIAL_MODULAR_ROBOT_INTERFACE_H

#include "ModularRobotInterface.hpp"
#include "ConfigParser.h"
#include <string>
#include <vector>
#include <iostream>
#include <SerialStream.h>

namespace hormodular {

class SerialModularRobotInterface : public ModularRobotInterface
{
    public:
        SerialModularRobotInterface(ConfigParser configParser);

        virtual bool start();
        virtual bool stop();
        virtual bool destroy();
        virtual bool reset();

        virtual bool setProperty(std::string property, std::string value);

        virtual float getTravelledDistance();
        virtual bool sendJointValues(std::vector<float> joint_values, float step_ms=0);
        virtual std::vector<float> getJointValues();

   private:
        //-- Hardware configuration related things
        std::string port_name;
        SerialPort* serialPort;
        std::vector<int> masterJoints;
        std::vector<int> slaveJoints;

        int step_ms;

        int n_modules;
        std::vector<float> joint_values;

        //-- Serial port related functions:
        bool initSerialPort();
        bool checkConnection();
        bool toggleLED();
        bool sendJointValuesSerial(std::vector<float> joint_values);
};

}

#endif //-- SERIAL_MODULAR_ROBOT_INTERFACE_H
