//------------------------------------------------------------------------------
//-- Orientation
//------------------------------------------------------------------------------
//--
//-- 3D vector representing the orientation of a module
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

#include "Orientation.hpp"


hormodular::Orientation::Orientation()
{
    roll = 0; pitch = 0; yaw = 0;
}

hormodular::Orientation::Orientation(int roll, int pitch, int yaw)
{
    this->roll = angle0to360(roll);
    this->pitch = angle0to360(pitch);
    this->yaw = angle0to360(yaw);
}

hormodular::Orientation::Orientation(std::string serialized_orientation)
{
    std::vector<std::string> components = splitString(serialized_orientation);

    if (components.size() == 3)
    {
        roll = angle0to360( atoi( components[0].c_str() ) );
        pitch= angle0to360( atoi( components[1].c_str() ) );
        yaw =  angle0to360( atoi( components[2].c_str() ) );
    }
    else
    {
        std::cerr << "[Orientation] Error: bad string!" << std::endl;
        roll = 0; pitch = 0; yaw = 0;
    }
}

hormodular::Orientation &hormodular::Orientation::operator+=(const hormodular::Orientation &a)
{
    roll = angle0to360( roll + a.roll);
    pitch= angle0to360( pitch + a.pitch);
    yaw  = angle0to360( yaw + a.yaw );

    return *this;
}

hormodular::Orientation &hormodular::Orientation::operator-=(const hormodular::Orientation &a)
{
    roll = angle0to360( roll - a.roll);
    pitch= angle0to360( pitch - a.pitch);
    yaw  = angle0to360( yaw - a.yaw );

    return *this;
}

int hormodular::Orientation::getYaw() const
{
    return yaw;
}

void hormodular::Orientation::setYaw(int value)
{
    yaw =angle0to360(value);
}

std::string hormodular::Orientation::str()
{
    std::stringstream sstream;
    sstream << roll << " " << pitch << " " << yaw;

    return sstream.str();
}

int hormodular::Orientation::getRelativeOrientation(int connector, hormodular::Orientation localOrient, hormodular::Orientation remoteOrient)
{
    //-- Create rotation matrices for local orientation:
    Eigen::AngleAxisd rollAngle( deg2rad(localOrient.getRoll()), Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd pitchAngle( deg2rad(localOrient.getPitch()), Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd yawAngle( deg2rad(localOrient.getYaw()), Eigen::Vector3d::UnitX());

    Eigen::Quaterniond q0 = yawAngle * pitchAngle * rollAngle ;
    Eigen::Matrix3d rotationMatrix = q0.matrix();

    //-- Create rotation matrices for the other orientation:
    Eigen::AngleAxisd otherRollAngle(  deg2rad(remoteOrient.getRoll()), Eigen::Vector3d::UnitZ());
    Eigen::AngleAxisd otherPitchAngle( deg2rad(remoteOrient.getPitch()), Eigen::Vector3d::UnitY());
    Eigen::AngleAxisd otherYawAngle(   deg2rad(remoteOrient.getYaw()), Eigen::Vector3d::UnitX());

    Eigen::Quaterniond q1 = otherYawAngle * otherPitchAngle * otherRollAngle;
    Eigen::Matrix3d otherRotationMatrix = q1.matrix();

    Eigen::Matrix3d relativeRotation = rotationMatrix.inverse() * otherRotationMatrix;

    Eigen::Vector3d new_z = relativeRotation * Eigen::Vector3d::UnitZ();

//    std::cout << "New_z: " << std::endl << new_z << std::endl << std::endl;

    //-- Get connector base vector for the rotations:
    Eigen::Vector3d base_vector;
    if ( connector == 0 || connector == 2)
    {
        //-- Y axis
        base_vector = Eigen::Vector3d::UnitY();
    }
    else if ( connector == 1 || connector == 3)
    {
        //-- X axis
        base_vector = Eigen::Vector3d::UnitX();
    }

    //-- Try for rotations to fit the vector
    for ( int i = 0; i < 4; i++)
    {
        Eigen::AngleAxisd rotAngle( deg2rad(i*90), base_vector);
        Eigen::Matrix3d rotMatrix = rotAngle.matrix();
        Eigen::Vector3d result_vector = rotMatrix * Eigen::Vector3d::UnitZ();

//        std::cout << "i = " << i << std::endl << result_vector << std::endl << std::endl;

        if ( vector_equal(result_vector, new_z) )
            return i;
    }

    return -1;
}

int hormodular::Orientation::angle0to360(int angle)
{
    angle %= 360;

    if (angle < 0)
        angle+=360;

    return angle;
}

double hormodular::Orientation::deg2rad(double angle)
{
    return angle*M_PI/180.0;
}

double hormodular::Orientation::rad2deg(double angle)
{
    return angle*180.0/M_PI;
}

bool hormodular::Orientation::vector_equal(Eigen::Vector3d a, Eigen::Vector3d b)
{
    static const float threshold = 0.0001;
    return abs(a[0] - b[0]) <= threshold &&
            abs(a[1] - b[1]) <= threshold &&
            abs(a[2] - b[2]) <= threshold;
}


int hormodular::Orientation::getPitch() const
{
    return pitch;
}

void hormodular::Orientation::setPitch(int value)
{
    pitch = angle0to360(value);
}

int hormodular::Orientation::getRoll() const
{
    return roll;
}

void hormodular::Orientation::setRoll(int value)
{
    roll = angle0to360(value);
}

hormodular::Orientation hormodular::operator+(hormodular::Orientation &a, hormodular::Orientation &b)
{
    return Orientation( (a.roll + b.roll), (a.pitch + b.pitch), (a.yaw + b.yaw) );
}


hormodular::Orientation hormodular::operator-(hormodular::Orientation &a, hormodular::Orientation &b)
{
    return Orientation( (a.roll - b.roll), (a.pitch - b.pitch), (a.yaw - b.yaw) );
}

