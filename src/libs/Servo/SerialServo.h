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

#ifndef SERIALSERVO_H
#define SERIALSERVO_H

#include <iostream>
#include <sstream>
#include <semaphore.h>

#include "Servo.h"

//#define DEBUG_MESSAGES

class SerialServo : public Servo
{
    public:
        SerialServo();

        virtual void write( float angle);

        void init();
        void setJointValuePtr( int * pjoint_value );
        void setJointInvert( bool enabled );
        void setSemaphores( sem_t* update_time_sem, sem_t* current_servo_sem);


   private:
        bool configured;
        bool inverted;
        int * pjoint_value;
        sem_t * update_time_sem;
        sem_t * current_servo_sem;

};

#endif //-- SERIALSERVO_H
