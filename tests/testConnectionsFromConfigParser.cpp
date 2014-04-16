#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.h"
#include "Module.hpp"

using namespace hormodular;


class ConnectionsFromConfigParserTest : public testing::Test
{
    public:
        ConfigParser configParser;
        std::vector<Module *> modules;

        static const std::string FILEPATH;

        virtual void SetUp()
        {
            configParser.parse(FILEPATH);
        }
};

//const std::string ConnectionsFromConfigParserTest::FILEPATH = "../../data/test/Test_robot.xml";
const std::string ConnectionsFromConfigParserTest::FILEPATH = "../../data/test/Test_robot2.xml";

TEST_F( ConnectionsFromConfigParserTest, connectionsLoadedOk)
{
    //-- Create as many modules as needed
    for(int i = 0; i < configParser.getNumModules(); i++)
        modules.push_back( new Module() );

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

    //------------------------------------------------------------------------------------
    //-- Hormone communication
    //------------------------------------------------------------------------------------
    for( int j = 0; j < 5; j++)
        for(int i = 0; i < (int) modules.size(); i++)
        {
            EXPECT_TRUE(modules[i]->processHormones());
            EXPECT_TRUE(modules[i]->sendHormones());
        }

    EXPECT_EQ( 0, modules[0]->getID() );
    EXPECT_EQ( 1, modules[1]->getID() );


    //-- End of Hormone communication
    //------------------------------------------------------------------------------------


    //-- Destroy modules
    for(int i = 0; i < (int) modules.size(); i++)
    {
        delete modules[i];
        modules[i] = NULL;
    }

}
