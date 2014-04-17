#include "gtest/gtest.h"
#include "SinusoidalOscillator.h"
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"
#include "GaitTable.h"

#include <iostream>
#include <string>

using namespace hormodular;

class MovementTestWithGaitTable : public testing::Test
{
    public:
        std::vector<Oscillator *> oscillators;
        ModularRobotInterface * robotInterface;
        ConfigParser configParser;
        GaitTable * gaitTable;

        static const std::string GAIT_TABLE_FILEPATH;

    virtual void SetUp()
    {
        //-- Read test data
        configParser.parse("../../data/robots/Test_robot.xml");

        //-- Create gait table
        gaitTable = new GaitTable(GAIT_TABLE_FILEPATH);

        //-- Create robot, simulated type
        robotInterface = createModularRobotInterface( "simulated", configParser);

        //-- Create sinusoidal oscillators with the test parameters
        for ( int i = 0; i < configParser.getNumModules(); i++)
            oscillators.push_back(new SinusoidalOscillator());
    }

    virtual void TearDown()
    {
        robotInterface->destroy();
        delete robotInterface;
        robotInterface = NULL;

        delete gaitTable;
        gaitTable = NULL;

        for ( int i = 0; i < (int) oscillators.size(); i++)
        {
            delete oscillators[i];
            oscillators[i] = NULL;
        }
    }
};

const std::string MovementTestWithGaitTable::GAIT_TABLE_FILEPATH = "../../data/test/test_gait_table.txt";


TEST_F( MovementTestWithGaitTable, robotExists)
{
    EXPECT_TRUE( robotInterface != NULL );

    for ( int i = 0; i < (int) oscillators.size(); i++)
        EXPECT_TRUE( oscillators[i] != NULL);
}

TEST_F( MovementTestWithGaitTable, robotDoesNotMoveIfNotWave)
{
    EXPECT_FLOAT_EQ( 0, robotInterface->getTravelledDistance());
}

TEST_F( MovementTestWithGaitTable, robotMovesIfWave)
{
    //-- Required variables
    unsigned long elapsed_time = 0;
    int step_ms = 1;
    unsigned long max_time_ms = 5000;
    std::vector<float> joint_values;

    std::vector<unsigned long> ids;
    ids.push_back(0);
    ids.push_back(1);


    //-- Initialize joint vector to 0
    for (int i = 0; i < (int) configParser.getNumModules(); i++)
        joint_values.push_back(0);

    //-- Reset robot
    robotInterface->reset();

    //-- Movement loop
    while( elapsed_time < max_time_ms )
    {
        //-- Get oscillator parameters from gait table:
        for( int i = 0; i < (int) ids.size(); i++)
        {
            std::vector<float> parameters = gaitTable->getParameters(ids[i]);
            oscillators[i]->setParameters(parameters[0], parameters[1], parameters[2], 1000);
        }

        //-- Update joint values
        for ( int i = 0; i < (int) oscillators.size(); i++)
            joint_values[i] = oscillators[i]->calculatePos(elapsed_time);

        //-- Send joint values
        robotInterface->sendJointValues(joint_values, step_ms);

        elapsed_time+=step_ms;
    }

    float distance = robotInterface->getTravelledDistance();
    std::cout << "Distance travelled: " << distance << std::endl;
    EXPECT_LT(0, distance );
}
