#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.h"

using namespace hormodular;

class Connector
{
    public:
        std::vector<int> inputBuffer;
        std::vector<int> outputBuffer;

        Connector * remoteConnector;
};

class Module
{
    public:
        Module()
        {
            for(int i = 0; i < 4; i++)
                connectors.push_back(new Connector() );
        }

        ~Module()
        {
            for(int i = 0; i < 4; i++)
                delete connectors[i];
        }

        bool attach( int localConnector, Connector* remoteConnector, int orientation = -1)
        {
            if (localConnector < 0 || localConnector >= (int) connectors.size())
            {
                std::cerr << "[Module] Error: could not attach to connector: " << localConnector << std::endl;
                return false;
            }

            connectors[localConnector]->remoteConnector = remoteConnector;

            std::cout << "[Module] Warning: ignoring orientation!" << std::endl;

            return true;
        }

        Connector* getConnector(int localConnector)
        {
            if (localConnector < 0 || localConnector >= 4)
            {
                std::cerr << "[Module] Error: could not get connector: " << localConnector << std::endl;
                return NULL;
            }
            else
            {
                return connectors[localConnector];
            }
        }

    private:
        std::vector<Connector*> connectors;
};


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

    //-- Destroy modules
    for(int i = 0; i < (int) modules.size(); i++)
    {
        delete modules[i];
        modules[i] = NULL;
    }

}
