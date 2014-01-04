//------------------------------------------------------------------------------
//-- Servo
//------------------------------------------------------------------------------
//--
//-- Base class for different types of servos for modular robots
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


#ifndef SERVO_H
#define SERVO_H

#include <inttypes.h>

class Servo
{
    public:
        virtual void write( float angle) = 0;

    protected:
        Servo();
        float pos_angle;
};

#endif //-- SERVO_H
