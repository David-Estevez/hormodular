//------------------------------------------------------------------------------
//-- Orientation
//------------------------------------------------------------------------------
//--
//-- 3d vector representing the orientation of a module
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

#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

#include <eigen3/Eigen/Geometry>
#include "Utils.hpp"

namespace hormodular {

class Orientation
{
    public:
        Orientation();
        Orientation(int roll, int pitch, int yaw);
        Orientation(std::string serialized_orientation);

        Orientation& operator+=(const Orientation& a);
        Orientation& operator-=(const Orientation& b);

        int getRoll() const;
        void setRoll(int value);

        int getPitch() const;
        void setPitch(int value);

        int getYaw() const;
        void setYaw(int value);

        std::string str();

        static int getRelativeOrientation( int connector, Orientation localOrient, Orientation remoteOrient );

        friend Orientation operator+(Orientation& a, Orientation& b);
        friend Orientation operator-(Orientation& a, Orientation& b);
private:
        int roll;
        int pitch;
        int yaw;

        int angle0to360(int angle);
        static double deg2rad( double angle);
        static double rad2deg(double angle);
        static bool vector_equal( Eigen::Vector3d a, Eigen::Vector3d b);
};

Orientation operator+(Orientation& a, Orientation& b);
Orientation operator-(Orientation& a, Orientation& b);

}
#endif //-- ORIENTATION_H
