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

#include "Servo.h"

Servo::Servo()
{
    pos_angle = 0;
}


float Servo::checkLimits(float value)
{
    if ( value < joint_limits.first )
        return joint_limits.first;
    else if ( value > joint_limits.second )
        return joint_limits.second;
    else
        return value;
}
