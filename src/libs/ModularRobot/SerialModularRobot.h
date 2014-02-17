//------------------------------------------------------------------------------
//-- SerialModularRobot
//------------------------------------------------------------------------------
//--
//-- Modular robot controlled by serial port
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

#ifndef SERIAL_MODULAR_ROBOT_H
#define SERIAL_MODULAR_ROBOT_H

#include <iostream>
#include <vector>
#include <semaphore.h>

#include "ModularRobot.h"
#include "SerialModule.h"
#include "SerialStream.h"

class SerialModularRobot : public ModularRobot
{
    public:
        SerialModularRobot( std::string port_name, int n_modules, std::string gait_table_file);
        ~SerialModularRobot();

        void reset();

    private:
        bool checkConnection(); //-- Check that the robot is ready and waiting
        virtual void updateTime();
        virtual void calculatePos(); //-- Empty

        SerialPort * serial_port;
        std::string serial_port_name;
        int * joint_position_array;

        //-- Semaphores for syncing:
        sem_t* modules_semaphores;
        sem_t updateTime_semaphore;


};

#endif // SERIAL_MODULAR_ROBOT_H
