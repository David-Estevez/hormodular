#include "SinusoidalOscillator.h"

SinusoidalOscillator::SinusoidalOscillator(): Oscillator() {}

SinusoidalOscillator::SinusoidalOscillator(uint8_t amplitude, uint8_t offset, float phase, uint16_t period_ms): Oscillator::Oscillator( amplitude, offset, phase, period_ms) {}

float SinusoidalOscillator::calculatePos(uint32_t time)
{
    return 90 + amplitude*sin( 2*M_PI*time/period_ms + deg2rad(phase)) + offset;
}

float SinusoidalOscillator::deg2rad(float angle_deg)
{
    return M_PI * angle_deg / 180;
}
