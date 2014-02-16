//------------------------------------------------------------------------------
//-- SinusoidalOscillator
//------------------------------------------------------------------------------
//--
//-- Sinusoidal oscillator
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

/*! \file SinusoidalOscillator.h
 *  \brief Generate oscillations using a sine function
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 27th, 2013
 */

#ifndef SINUSOIDAL_OSCILLATOR_H
#define SINUSOIDAL_OSCILLATOR_H

#include <stdint.h>
#include <cmath>
#include <iostream>

#include "Oscillator.h"

/*! \class SinusoidalOscillator
 *  \brief Generate oscillations using a sine function
 */
class SinusoidalOscillator: public Oscillator
{
    public:
        SinusoidalOscillator();
        SinusoidalOscillator( uint8_t amplitude, uint8_t offset, float phase, uint16_t period_ms = 4000);

        virtual float calculatePos( uint32_t time );

    private:
        float deg2rad( float angle_deg);
};

#endif
