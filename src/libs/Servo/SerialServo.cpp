//------------------------------------------------------------------------------
//-- SerialServo
//------------------------------------------------------------------------------
//--
//-- Servo for a serial-port-controlled robot on openRAVE
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

#include "SerialServo.h"

SerialServo::SerialServo()
{
    //-- Default values:
    pos_angle = 90;
    joint_limits = std::pair<float, float>( 0, 180);
    configured = false;
    pjoint_value = NULL;
    update_time_sem = NULL;
    current_servo_sem = NULL;
}

void SerialServo::write(float angle)
{
    if ( configured )
    {
        //-- Calculate new position:
        if ( !inverted )
            pos_angle = (int) checkLimits(90 + angle);
        else
            pos_angle = (int) checkLimits(90 - angle);

        //-- Lock semaphore
        sem_wait( current_servo_sem);

        //-- Move servo
        *pjoint_value = pos_angle;

        //-- Unlock semaphore
        sem_post( update_time_sem);


    }
}

void SerialServo::init()
{
    configured = true;
}

void SerialServo::setJointValuePtr(int *pjoint_value)
{
    this->pjoint_value = pjoint_value;
}

void SerialServo::setJointInvert(bool enabled)
{
    inverted = enabled;
}

void SerialServo::setSemaphores(sem_t* update_time_sem, sem_t* current_servo_sem)
{
    if ( update_time_sem != NULL && current_servo_sem != NULL)
    {
        this->update_time_sem = update_time_sem;
        this->current_servo_sem = current_servo_sem;
    }
}
