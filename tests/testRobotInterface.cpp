#include "gtest/gtest.h"
#include <string>
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"

using namespace hormodular;

class RobotInterfaceTest : public testing::Test
{

public:
    ModularRobotInterface * robotInterface;
    ConfigParser configParser;

    virtual void SetUp()
    {
        //-- Read test data
        configParser.parse("../../data/robots/Test_robot.xml");

        //-- Create robot, simulated type
        robotInterface = createModularRobotInterface( "simulated", configParser);
   	}

    virtual void TearDown()
    {
        robotInterface->destroy();
    }
};

TEST_F(RobotInterfaceTest,createdRobotInterfaceExists)
{
     EXPECT_TRUE(robotInterface != NULL);
}

TEST_F(RobotInterfaceTest,resetResetsRobotInterface)
{
//    robot->reset();

//    EXPECT_EQ(0, robot->getTravelledDistance());

//    int x, y;
//    robot->getPos( x, y);
//    EXPECT_EQ(0, x);
//    EXPECT_EQ(0, y);
    int result = robotInterface->reset();
    EXPECT_TRUE(result);

    std::vector<float> joint_values_received;
    joint_values_received = robotInterface->getJointValues();
    EXPECT_FLOAT_EQ(0, joint_values_received[0]);
    EXPECT_FLOAT_EQ(0, joint_values_received[1]);
}

TEST_F(RobotInterfaceTest, sendJointValuesSendsJointValues)
{
    robotInterface->reset();

    std::vector<float> joint_values_sent, joint_values_received;
    joint_values_sent.push_back(15);
    joint_values_sent.push_back(-15);

    for(int i = 0; i < 5000; i ++)
    {
        bool result = robotInterface->sendJointValues(joint_values_sent, 1);
        EXPECT_TRUE(result);
    }

    joint_values_received = robotInterface->getJointValues();
    EXPECT_NEAR(15, joint_values_received[0], 5);
    EXPECT_NEAR(-15, joint_values_received[1], 5);
}
