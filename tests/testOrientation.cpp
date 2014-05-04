#include "gtest/gtest.h"
#include "Orientation.hpp"
#include <eigen3/Eigen/Geometry>

#include <iostream>

using namespace hormodular;


TEST( TestOrientation, SumOrientationOk )
{
    Orientation x1(0, 0, 180);
    Orientation x2(0, 90, 0);
    Orientation x3(-90, 0, 90);
    Orientation x4(90, 0, -90);

    Orientation result = x1 + x2;
    EXPECT_EQ(0 , result.getRoll());
    EXPECT_EQ(90 , result.getPitch());
    EXPECT_EQ(180 , result.getYaw());

    result = x3 + x4;
    EXPECT_EQ(0 , result.getRoll());
    EXPECT_EQ(0 , result.getPitch());
    EXPECT_EQ(0 , result.getYaw());

    result = x2 + x3;
    EXPECT_EQ(270 , result.getRoll());
    EXPECT_EQ(90 , result.getPitch());
    EXPECT_EQ(90 , result.getYaw());

    result = x1 + x3;
    EXPECT_EQ(270 , result.getRoll());
    EXPECT_EQ(0 , result.getPitch());
    EXPECT_EQ(270 , result.getYaw());

    result = x1 + x1;
    EXPECT_EQ(0 , result.getRoll());
    EXPECT_EQ(0 , result.getPitch());
    EXPECT_EQ(0 , result.getYaw());
}

TEST( TestOrientation, SubstractOrientationOk )
{
    Orientation x1(0, 0, 180);
    Orientation x2(0, 90, 0);
    Orientation x3(-90, 0, 90);
    Orientation x4(90, 0, -90);

    Orientation result = x1 - x2;
    EXPECT_EQ(0 , result.getRoll());
    EXPECT_EQ(270 , result.getPitch());
    EXPECT_EQ(180 , result.getYaw());

    result = x3 - x4;
    EXPECT_EQ(180 , result.getRoll());
    EXPECT_EQ(0 , result.getPitch());
    EXPECT_EQ(180 , result.getYaw());

    result = x2 - x3;
    EXPECT_EQ(90 , result.getRoll());
    EXPECT_EQ(90 , result.getPitch());
    EXPECT_EQ(270 , result.getYaw());

    result = x1 - x3;
    EXPECT_EQ(90 , result.getRoll());
    EXPECT_EQ(0 , result.getPitch());
    EXPECT_EQ(90 , result.getYaw());

    result = x1 - x1;
    EXPECT_EQ(0 , result.getRoll());
    EXPECT_EQ(0 , result.getPitch());
    EXPECT_EQ(0 , result.getYaw());
}

TEST( TestOrientation, getRelativeOrientationOk)
{
    Orientation x0(  0,  0, 180);
    Orientation x1(  0, 90,   0);
    Orientation x2(-90,  0,  90);
    Orientation x3( 90,  0, -90);
    Orientation x4(  0,  0,   0);
    Orientation x5(-90,  0,   0);
    Orientation x6( 90,  0,   0);
    Orientation x7(180, -90,   0);
    Orientation x8(180,  0,   0);

    Orientation x5_2( -90,   0,  90);
    Orientation x6_2(  90,   0, -90);
    Orientation x7_2( -90,   0,   0);
    Orientation x8_2(  90,   0,   0);
    Orientation x9_2( -90,   0,   0);
    Orientation x10_2( 90,   0,   0);


    EXPECT_EQ(3, Orientation::getRelativeOrientation(1, x0, x2));
    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x0, x1));
    EXPECT_EQ(1, Orientation::getRelativeOrientation(3, x0, x3));
    EXPECT_EQ(3, Orientation::getRelativeOrientation(0, x0, x7));

    EXPECT_EQ(3, Orientation::getRelativeOrientation(0, x1, x4));
    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x1, x0));

    EXPECT_EQ(3, Orientation::getRelativeOrientation(0, x2, x5));
    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x2, x0));

    EXPECT_EQ(3, Orientation::getRelativeOrientation(0, x3, x6));
    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x3, x0));

    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x4, x1));
    EXPECT_EQ(1, Orientation::getRelativeOrientation(1, x4, x5_2));
    EXPECT_EQ(3, Orientation::getRelativeOrientation(3, x4, x6_2));

    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x5, x2));

    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x6, x3));

    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x7, x0));
    EXPECT_EQ(3, Orientation::getRelativeOrientation(0, x7, x8));

    EXPECT_EQ(1, Orientation::getRelativeOrientation(2, x8, x7));

    EXPECT_EQ(3, Orientation::getRelativeOrientation(0, x5_2, x9_2));
    EXPECT_EQ(3, Orientation::getRelativeOrientation(2, x5_2, x4));

    EXPECT_EQ(3, Orientation::getRelativeOrientation(0, x6_2, x10_2));
    EXPECT_EQ(3, Orientation::getRelativeOrientation(2, x6_2, x4));

}
