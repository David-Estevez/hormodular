#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.h"
#include "Module.hpp"
#include "SinusoidalOscillator.h"
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"
#include "GaitTable.h"

using namespace hormodular;


class ModularRobotTest : public testing::Test
{
    public:
        ConfigParser configParser;
        std::vector<Module *> modules;
        ModularRobotInterface * robotInterface;
        GaitTable * gaitTable;

        static const std::string FILEPATH;

        virtual void SetUp()
        {
            configParser.parse(FILEPATH);

            //-- Create as many modules as needed
            for(int i = 0; i < configParser.getNumModules(); i++)
                modules.push_back( new Module(configParser) );

            //-- Create robot, simulated type
            robotInterface = createModularRobotInterface( "simulated", configParser);
        }

        virtual void TearDown()
        {
            robotInterface->destroy();
            delete robotInterface;
            robotInterface = NULL;

            //-- Destroy modules
            for(int i = 0; i < (int) modules.size(); i++)
            {
                delete modules[i];
                modules[i] = NULL;
            }
        }
};

//const std::string ConnectionsFromConfigParserTest::FILEPATH = "../../data/test/Test_robot.xml";
const std::string ModularRobotTest::FILEPATH = "../../data/test/Test_robot2.xml";

TEST_F( ModularRobotTest, robotMovesUsingHormonesAndTable)
{


    //-- Attach the modules to the other modules
    for(int i = 0; i < (int) modules.size(); i++)
    {
        std::vector< std::vector<int> > connectorConfig = configParser.getConnectorInfo(i);

        for (int j = 0; j < (int) connectorConfig.size(); j++)
        {
            if ( connectorConfig[j].size() != 0 )
            {
                int moduleConnectedTo = connectorConfig[j][0];
                int connectorConnectedTo = connectorConfig[j][1];
                int orientation = connectorConfig[j][2];
                EXPECT_TRUE(modules[i]->attach( j,
                                                modules[moduleConnectedTo]->getConnector(connectorConnectedTo),
                                                orientation));
            }
            else
                EXPECT_TRUE(modules[i]->attach(j, NULL));
        }
    }

    //-- Check that they are attached correctly
    EXPECT_EQ(modules[1]->getConnector(2), modules[0]->getConnector(0)->remoteConnector );
    EXPECT_EQ(modules[0]->getConnector(0), modules[1]->getConnector(2)->remoteConnector );

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
        //-- Process incoming hormones
        for(int i = 0; i < (int) modules.size(); i++)
            EXPECT_TRUE(modules[i]->processHormones());

        //-- Get oscillator parameters from gait table:
        for( int i = 0; i < (int) modules.size(); i++)
        {
            EXPECT_TRUE(modules[i]->updateOscillatorParameters());
        }

        //-- Update joint values
        for ( int i = 0; i < (int) modules.size(); i++)
            joint_values[i] = modules[i]->calculateNextJointPos();

        //-- Send joint values
        robotInterface->sendJointValues(joint_values, step_ms);

        //-- Send hormones
        for(int i = 0; i < (int) modules.size(); i++)
            EXPECT_TRUE(modules[i]->sendHormones());

        //-- Update time:
        for ( int i = 0; i < (int) modules.size(); i++)
            EXPECT_TRUE( modules[i]->updateElapsedTime(step_ms));

        elapsed_time+=step_ms;
    }

    float distance = robotInterface->getTravelledDistance();
    std::cout << "Distance travelled: " << distance << std::endl;
    EXPECT_LT(600, distance );
}
