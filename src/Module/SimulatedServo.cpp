//------------------------------------------------------------------------------
//-- SimulatedServo
//------------------------------------------------------------------------------
//--
//-- Servo for a simulated robot on openRAVE
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

#include "SimulatedServo.h"


SimulatedServo::SimulatedServo()
{
    //-- Default values
    configured = false;
    joint_id = -1;
    key_update_time = -1;
    key_current_servo = -1;
}

void SimulatedServo::write(float angle)
{
    if ( configured )
    {

        std::stringstream is, os;
        is << "setpos1 " << joint_id << " " << angle;

        //-- Lock semaphore

        //-- Move servo
        openRave_pcontroller->SendCommand(os, is);
        std::cout << "Wrote: " << angle << " to servo." << std::endl;

        //-- Unlock semaphore

        //-- Store new value:
        this->pos_angle = angle;
    }
}

void SimulatedServo::init()
{
    //-- Create semaphores
    //-- Set configured to true
    configured = true;
}

void SimulatedServo::setOpenRaveController(OpenRAVE::ControllerBasePtr openRave_pcontroller)
{
    if ( openRave_pcontroller != NULL )
        this->openRave_pcontroller = openRave_pcontroller;
}

void SimulatedServo::setJointID(int joint_id)
{
    if ( joint_id >= 0)
        this->joint_id = joint_id;
    else
        std::cerr << "[SimulatedServo] Error: invalid joint ID, must be >= 0." << std::endl;
}

void SimulatedServo::setSemaphoreKeys(int key_update_time, int key_current_servo)
{
    if ( key_update_time >= 0 && key_current_servo >= 0)
    {
        this->key_update_time = key_update_time;
        this->key_current_servo = key_current_servo;
    }
}
