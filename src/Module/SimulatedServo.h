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

#ifndef SIMULATEDSERVO_H
#define SIMULATEDSERVO_H

#include <openrave-core.h>
#include <iostream>
#include <sstream>
#include <semaphore.h>

#include "Servo.h"


class SimulatedServo : public Servo
{
    public:
        SimulatedServo();

        virtual void write( float angle);

        void init();
        void setOpenRaveController( OpenRAVE::ControllerBasePtr openRave_pcontroller);
        void setJointID( int joint_id);
        void setSemaphores( sem_t* update_time_sem, sem_t* current_servo_sem);


   private:
        bool configured;
        OpenRAVE::ControllerBasePtr openRave_pcontroller;
        int joint_id;
        sem_t * update_time_sem;
        sem_t * current_servo_sem;

};

#endif //-- SIMULATEDSERVO_H
