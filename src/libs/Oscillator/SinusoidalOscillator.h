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
 */

#ifndef SINUSOIDAL_OSCILLATOR_H
#define SINUSOIDAL_OSCILLATOR_H

#include <stdint.h>
#include <cmath>
#include <iostream>

#include "Oscillator.h"

namespace hormodular {

/*! \class SinusoidalOscillator
 *  \brief Generate oscillations using a sine function
 */
class SinusoidalOscillator: public Oscillator
{
    public:
        SinusoidalOscillator();
        SinusoidalOscillator( float amplitude, float offset, float phase, int period_ms = 4000);

        virtual float calculatePos( unsigned long time );

    private:
        float deg2rad( float angle_deg);
};
}
#endif
