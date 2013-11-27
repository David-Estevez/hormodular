#include "Oscillator.h"



//-- Setting and getting parameters
//-------------------------------------------------------------------------------------------
void Oscillator::setPeriod(uint16_t period_ms)
{
    if ( period_ms != 0)
        this->period_ms = period_ms;
    else
        std::cerr << "[Oscillator] Period cannot be set to 0 ms";
}

void Oscillator::setAmplitude(uint8_t amplitude)
{
    if ( amplitude <= 90 )
        this->amplitude = amplitude;
    else
        std::cerr << "[Oscillator] Amplitude out of range [0,90] (Got: " << amplitude << ")\n";
}

void Oscillator::setOffset(int8_t offset)
{
    if ( offset >= -90 && offset <= 90 )
        this->offset = offset;
    else
        std::cerr << "[Oscillator] Offset out of range [-90,90] (Got: " << offset << ")\n";
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
    if ( period_ms != 0 ) this->period_ms = period_ms;
}

uint16_t Oscillator::getPeriod()    { return period_ms; }
uint8_t Oscillator::getAmplitude() { return amplitude; }
int8_t Oscillator::getOffset()    { return offset; }
float Oscillator::getPhase()     { return phase; }

//-- Constructors
Oscillator::Oscillator()
{
    this->amplitude = 0;
    this->offset = 0;
    this->phase = 0;
    this->period_ms = 4000;
}

Oscillator::Oscillator(uint8_t amplitude, uint8_t offset, float phase, uint16_t period_ms)
{
    this->amplitude = amplitude;
    this->offset = offset;
    this->phase = phase;
    this->period_ms = period_ms;
}
