#include "gtest/gtest.h"
#include "SinusoidalOscillator.h"
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"

#include <iostream>

using namespace hormodular;


class MovementTest : public testing::Test
{
    public:
        std::vector<Oscillator *> oscillators;
        ModularRobotInterface * robotInterface;
        ConfigParser configParser;

        static const float AMPLITUDE = 60;
        static const float OFFSET = 0;
        static const int PERIOD = 1000;
        static const float PHASE = 120;

    virtual void SetUp()
    {
        //-- Read test data
        configParser.parse("../../data/robots/Test_robot.xml");

        //-- Create robot, simulated type
        robotInterface = createModularRobotInterface( "simulated", configParser);

        //-- Create sinusoidal oscillators with the test parameters
        for ( int i = 0; i < configParser.getNumModules(); i++)
            oscillators.push_back(new SinusoidalOscillator( AMPLITUDE, OFFSET, PHASE*i, PERIOD));
    }

    virtual void TearDown()
    {
        robotInterface->destroy();
        delete robotInterface;
        robotInterface = NULL;

        for ( int i = 0; i < (int) oscillators.size(); i++)
        {
            delete oscillators[i];
            oscillators[i] = NULL;
        }
    }
};

TEST_F( MovementTest, robotExists)
{
    EXPECT_TRUE( robotInterface != NULL );

    for ( int i = 0; i < (int) oscillators.size(); i++)
        EXPECT_TRUE( oscillators[i] != NULL);
}

TEST_F( MovementTest, robotDoesNotMoveIfNotWave)
{
    EXPECT_FLOAT_EQ( 0, robotInterface->getTravelledDistance());
}

TEST_F( MovementTest, robotMovesIfWave)
{
    //-- Required variables
    unsigned long elapsed_time = 0;
    int step_ms = 1;
    unsigned long max_time_ms = 5000;
    std::vector<float> joint_values;

    //-- Initialize joint vector to 0
    for (int i = 0; i < (int) configParser.getNumModules(); i++)
        joint_values.push_back(0);

    //-- Reset robot
    robotInterface->reset();

    //-- Movement loop
    while( elapsed_time < max_time_ms )
    {
        //-- Update joint values
        for ( int i = 0; i < (int) oscillators.size(); i++)
            joint_values[i] = oscillators[i]->calculatePos(elapsed_time);

        //-- Send joint values
        robotInterface->sendJointValues(joint_values, step_ms);

        elapsed_time+=step_ms;
    }

    float distance = robotInterface->getTravelledDistance();
    std::cout << "Distance travelled: " << distance << std::endl;
    EXPECT_LT(0.1, distance );
}
