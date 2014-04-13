#include "Oscillator.h"



//-- Setting and getting parameters
//-------------------------------------------------------------------------------------------
void hormodular::Oscillator::setPeriod(int period_ms)
{
    if ( period_ms != 0)
    {
        this->period_ms = period_ms;
    }
    else
    {
        this->period_ms = 4000;
        std::cerr << "[Oscillator] Period cannot be set to 0 ms. Setting to " << this->period_ms << std::endl;
    }
}

void hormodular::Oscillator::setAmplitude(float amplitude)
{
    if ( amplitude <= 90 )
    {
        this->amplitude = amplitude;
    }
    else
    {
        this->amplitude = 0;
        std::cerr << "[Oscillator] Amplitude out of range [0,90] (Got: " << amplitude << ")" << std::endl;
    }
}

void hormodular::Oscillator::setOffset(float offset)
{
    if ( offset >= -90 && offset <= 90 )
    {
        this->offset = offset;
    }
    else
    {
        this->offset = 0;
        std::cerr << "[Oscillator] Offset out of range [-90,90] (Got: " << offset << ")" << std::endl;
    }
}

void hormodular::Oscillator::setPhase(float phase)
{
    this->phase = phase;
}

void hormodular::Oscillator::setParameters(float amplitude, float offset, float phase, int period_ms)
{
    setAmplitude(amplitude);
    setOffset(offset);
    setPhase(phase);
    setPeriod(period_ms);
}

int hormodular::Oscillator::getPeriod()    { return period_ms; }
float hormodular::Oscillator::getAmplitude() { return amplitude; }
float hormodular::Oscillator::getOffset()    { return offset; }
float hormodular::Oscillator::getPhase()     { return phase; }

//-- Constructors
hormodular::Oscillator::Oscillator()
{
    this->amplitude = 0;
    this->offset = 0;
    this->phase = 0;
    this->period_ms = 4000;
}

hormodular::Oscillator::Oscillator(float amplitude, float offset, float phase, int period_ms)
{
    setParameters(amplitude, offset, phase, period_ms);
}
