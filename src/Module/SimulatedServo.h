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

#include "Servo.h"


class SimulatedServo : public Servo
{
    public:
        SimulatedServo();

        virtual void write( float angle);

        void init();
        void setOpenRaveController( OpenRAVE::ControllerBasePtr openRave_pcontroller);
        void setJointID( int joint_id);
        void setSemaphoreKeys( int key_update_time, int key_current_servo);


   private:
        bool configured;
        OpenRAVE::ControllerBasePtr openRave_pcontroller;
        int joint_id;
        int key_update_time;
        int key_current_servo;

};

#endif //-- SIMULATEDSERVO_H
