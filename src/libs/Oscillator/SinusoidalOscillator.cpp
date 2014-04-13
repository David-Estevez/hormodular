#include "SinusoidalOscillator.h"

hormodular::SinusoidalOscillator::SinusoidalOscillator(): Oscillator() {}

hormodular::SinusoidalOscillator::SinusoidalOscillator(float amplitude, float offset, float phase, int period_ms): Oscillator::Oscillator( amplitude, offset, phase, period_ms) {}

float hormodular::SinusoidalOscillator::calculatePos(unsigned long time)
{
   return amplitude*sin( 2*M_PI*time/period_ms + deg2rad(phase)) + offset;
}

float hormodular::SinusoidalOscillator::deg2rad(float angle_deg)
{
    return M_PI * angle_deg / 180;
}
