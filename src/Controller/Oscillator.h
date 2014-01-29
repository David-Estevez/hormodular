//------------------------------------------------------------------------------
//-- Oscillator
//------------------------------------------------------------------------------
//--
//-- Abstract class that serves as a base to create different oscillators
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

/*! \file Oscillator.h
 *  \brief Abstract class that serves as a base to create different oscillators
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 * \date Nov 27th, 2013
 */

#ifndef OSCILLATOR_H
#define OSCILLATOR_H

#include <stdint.h>
#include <iostream>

/*! \class Oscillator
 *  \brief Abstract class that serves as a base to create different oscillators
 */
class Oscillator
{

   public:
        void setPeriod( uint16_t period_ms);
        uint16_t getPeriod( );

        void setAmplitude( float amplitude);
        float getAmplitude();

        void setOffset(float offset);
        float getOffset();

        void setPhase( float phase);
        float getPhase();

        /*! \brief Set all the oscillator parameters at once
         *
         * \param amplitude Amplitude of the oscillation, [0,90] degrees
         * \param offset Offset of the oscillation, [-90,90] degrees
         * \param phase Phase of the oscillation [0, 360] degrees
         * \param period Period of the oscillation in ms. A value of 0 means "use the current value".
         */
        void setParameters( uint8_t amplitude, uint8_t offset, float phase, uint16_t period_ms = 0);

        /*! \brief Calculate the position of the oscillator at time
         *
         *  \param time Time at which the oscillation is calculated
         *  \return Position of the oscillator at given time
         */
        virtual float calculatePos( uint32_t time ) = 0;

    protected:
        Oscillator();
        Oscillator(float amplitude, float offset, float phase, uint16_t period_ms = 4000);

        uint16_t period_ms;
        float amplitude;
        float offset;
        float phase;
};

#endif
