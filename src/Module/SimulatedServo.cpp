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
    update_time_sem = NULL;
    current_servo_sem = NULL;
}

void SimulatedServo::write(float angle)
{
    if ( configured )
    {
        std::stringstream is, os;
        is << "setpos1 " << joint_id << " " << angle;

        //-- Lock semaphore
        sem_wait( current_servo_sem);

        //-- Move servo
        openRave_pcontroller->SendCommand(os, is);
        std::cout <<"[Debug]Wrote: " << angle << " to servo " << joint_id << std::endl;
        std::cout.flush();

        //-- Unlock semaphore
        sem_post( update_time_sem);

        //-- Store new value:
        this->pos_angle = angle;
    }
}

void SimulatedServo::init()
{
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

void SimulatedServo::setSemaphores(sem_t* update_time_sem, sem_t* current_servo_sem)
{
    if ( update_time_sem != NULL && current_servo_sem != NULL)
    {
        this->update_time_sem = update_time_sem;
        this->current_servo_sem = current_servo_sem;
    }
}
