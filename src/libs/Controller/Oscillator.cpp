#include "Oscillator.h"



//-- Setting and getting parameters
//-------------------------------------------------------------------------------------------
void Oscillator::setPeriod(uint16_t period_ms)
{
    if ( period_ms != 0)
    {
        this->period_ms = period_ms;
    }
    else
    {
        this->period_ms = 4000;
        std::cerr << "[Oscillator] Period cannot be set to 0 ms. Setting to " << (int)this->period_ms << std::endl;
    }
}

void Oscillator::setAmplitude(float amplitude)
{
    if ( amplitude <= 90 )
    {
        this->amplitude = amplitude;
    }
    else
    {
        this->amplitude = 0;
        std::cerr << "[Oscillator] Amplitude out of range [0,90] (Got: " << (int)amplitude << ")" << std::endl;
    }
}

void Oscillator::setOffset(float offset)
{
    if ( offset >= -90 && offset <= 90 )
    {
        this->offset = offset;
    }
    else
    {
        this->offset = 0;
        std::cerr << "[Oscillator] Offset out of range [-90,90] (Got: " << (int)offset << ")" << std::endl;
    }
}

void Oscillator::setPhase(float phase)
{
    this->phase = phase;
}

void Oscillator::setParameters(uint8_t amplitude, uint8_t offset, float phase, uint16_t period_ms)
{
    setAmplitude(amplitude);
    setOffset(offset);
    setPhase(phase);
    setPeriod(period_ms);
}

uint16_t Oscillator::getPeriod()    { return period_ms; }
float Oscillator::getAmplitude() { return amplitude; }
float Oscillator::getOffset()    { return offset; }
float Oscillator::getPhase()     { return phase; }

//-- Constructors
Oscillator::Oscillator()
{
    this->amplitude = 0;
    this->offset = 0;
    this->phase = 0;
    this->period_ms = 4000;
}

Oscillator::Oscillator(float amplitude, float offset, float phase, uint16_t period_ms)
{
    setParameters(amplitude, offset, phase, period_ms);
}
