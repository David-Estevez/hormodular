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
#include <utility>

class Servo
{
    public:
        virtual void write( float angle) = 0;

    protected:
        Servo();
        /**
         * @brief checkLimits Checks if a value is within the joint allowed values
         * @param value Value to check
         * @return If within the limits, returns the same value as given, if not
         *          returns the closest limit.
         */
        float checkLimits( float value );

        float pos_angle;
        std::pair<float, float> joint_limits;
};

#endif //-- SERVO_H
