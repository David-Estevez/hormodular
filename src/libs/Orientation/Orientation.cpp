#include "Orientation.hpp"


hormodular::Orientation::Orientation()
{
    roll = 0; pitch = 0; yaw = 0;
}

hormodular::Orientation::Orientation(int roll, int pitch, int yaw)
{
    this->roll = roll%360;
    this->pitch = pitch%360;
    this->yaw = yaw%360;
}

hormodular::Orientation &hormodular::Orientation::operator+=(const hormodular::Orientation &a)
{
    roll = ( roll + a.roll)%360;
    pitch = (pitch + a.pitch)%360;
    yaw = ( yaw + a.yaw )%360;

    return *this;
}

hormodular::Orientation &hormodular::Orientation::operator-=(const hormodular::Orientation &a)
{
    roll = ( roll - a.roll)%360;
    pitch = (pitch - a.pitch)%360;
    yaw = ( yaw - a.yaw )%360;

    return *this;
}

int hormodular::Orientation::getYaw() const
{
    return yaw;
}

void hormodular::Orientation::setYaw(int value)
{
    yaw = value%360;
}

int hormodular::Orientation::getPitch() const
{
    return pitch;
}

void hormodular::Orientation::setPitch(int value)
{
    pitch = value%360;
}

int hormodular::Orientation::getRoll() const
{
    return roll;
}

void hormodular::Orientation::setRoll(int value)
{
    roll = value%360;
}

hormodular::Orientation hormodular::operator+(hormodular::Orientation &a, hormodular::Orientation &b)
{
    return Orientation( (a.roll + b.roll)%360, (a.pitch + b.pitch)%360, (a.yaw + b.yaw)%360 );
}


hormodular::Orientation hormodular::operator-(hormodular::Orientation &a, hormodular::Orientation &b)
{
    return Orientation( (a.roll - b.roll)%360, (a.pitch - b.pitch)%360, (a.yaw - b.yaw)%360 );
}

