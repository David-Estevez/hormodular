#include "gtest/gtest.h"
#include <string>
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"

using namespace hormodular;

class SerialModularRobotInterfaceTest : public testing::Test
{

public:
    ModularRobotInterface * robotInterface;
    ConfigParser configParser;

    virtual void SetUp()
    {
        //-- Read test data
        configParser.parse("../../data/robots/Test_robot.xml");

        //-- Create robot, serial type
        robotInterface = createModularRobotInterface( "serial", configParser);
        robotInterface->start();
    }

    virtual void TearDown()
    {
        robotInterface->stop();
        robotInterface->destroy();
    }
};

TEST_F(SerialModularRobotInterfaceTest,createdRobotInterfaceExists)
{
     EXPECT_TRUE(robotInterface != NULL);
}

TEST_F(SerialModularRobotInterfaceTest,resetResetsRobotInterface)
{
    int result = robotInterface->reset();
    EXPECT_TRUE(result);

    std::vector<float> joint_values_received;
    joint_values_received = robotInterface->getJointValues();
    EXPECT_FLOAT_EQ(0, joint_values_received[0]);
    EXPECT_FLOAT_EQ(0, joint_values_received[1]);
}

TEST_F(SerialModularRobotInterfaceTest, sendJointValuesSendsJointValues)
{
    robotInterface->reset();

    std::vector<float> joint_values_sent, joint_values_received;
    joint_values_sent.push_back(30);
    joint_values_sent.push_back(-45);

    for(int i = 0; i < 5000; i ++)
    {
        bool result = robotInterface->sendJointValues(joint_values_sent, 20);
        EXPECT_TRUE(result);
    }

    joint_values_received = robotInterface->getJointValues();
    EXPECT_NEAR(30, joint_values_received[0], 5);
    EXPECT_NEAR(-45, joint_values_received[1], 5);
}

TEST_F(SerialModularRobotInterfaceTest, ToggleLED)
{
    robotInterface->reset();

    ASSERT_TRUE(robotInterface->setProperty("LED", "toggle"));
    usleep(500000);
}
