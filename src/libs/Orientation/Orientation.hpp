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

/*! \file Orientation.hpp
 *  \brief 3D vector representing the orientation of a module
 *
 * \author David Estévez Fernández ( http://github.com/David-Estevez )
 */

#ifndef ORIENTATION_H
#define ORIENTATION_H

#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

#include <eigen3/Eigen/Geometry>
#include "Utils.hpp"

namespace hormodular {

/*!
 *  \class Orientation
 *  \brief 3D vector representing the orientation of a module
 */

class Orientation
{
    public:
        Orientation();
        Orientation(int roll, int pitch, int yaw);

        /*!
         * \brief Creates an Orientation object from a space-separated string containing the serialized data
         *
         * The string format is the following: "roll pitch yaw" (i.e. "90 180 270")
         *
         * \param serialized_orientation Space-separated string containing the roll, pitch and yaw.
         */
        Orientation(std::string serialized_orientation);



        //! \brief Sums the Orientations component by component
        Orientation& operator+=(const Orientation& a);

        //! \brief Sums the Orientations component by component
        friend Orientation operator+(Orientation& a, Orientation& b);

        //! \brief Substracts the Orientations component by component
        Orientation& operator-=(const Orientation& b);

        //! \brief Substracts the Orientations component by component
        friend Orientation operator-(Orientation& a, Orientation& b);



        int getRoll() const;
        void setRoll(int value);
        int getPitch() const;
        void setPitch(int value);
        int getYaw() const;
        void setYaw(int value);



        /*!
         * \brief Outputs a space-separated string containing the serialized data for this orientation
         *
         * The string format is the following: "roll pitch yaw" (i.e. "90 180 270")
         **/
        std::string str();

        /*!
         * \brief Returns the relative orientaion between two orientations, encoded as a number between 0 and 3
         *
         * This number represents the number of 90º turns we have to rotate the local module around the axis
         * of the local reference system that is in the same direction as the normal vector of the local
         * connector surface, such as the Z axis of the local reference system of both modules coincide.
         *
         */
        static int getRelativeOrientation( int connector, Orientation localOrient, Orientation remoteOrient );


private:
        int roll;
        int pitch;
        int yaw;

        //! \brief Maps the current angle to a value between 0 and 360
        int angle0to360(int angle);

        //! \brief Converts an angle in degrees to radians
        static double deg2rad( double angle);

        //! \brief Converts an angle in radians to degrees
        static double rad2deg(double angle);

        //! \brief Checks if two Eigen::Vector3d are equal
        static bool vector_equal( Eigen::Vector3d a, Eigen::Vector3d b);
};

//! \brief Sums the Orientations component by component
Orientation operator+(Orientation& a, Orientation& b);

//! \brief Substracts the Orientations component by component
Orientation operator-(Orientation& a, Orientation& b);

}
#endif //-- ORIENTATION_H
