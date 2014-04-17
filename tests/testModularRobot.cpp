#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.h"
#include "Module.hpp"
#include "ModularRobotInterface.hpp"
#include "ModularRobotInterfaceFactory.hpp"
#include "GaitTable.h"
#include "ModularRobot.h"

using namespace hormodular;


class ModularRobotTest : public testing::Test
{
    public:
        ConfigParser configParser;
        ModularRobot * modularRobot;

        static const std::string FILEPATH;
        static const unsigned long max_time_ms = 5000;

        virtual void SetUp()
        {
            configParser.parse(FILEPATH);

            modularRobot = new ModularRobot(configParser);
        }

        virtual void TearDown()
        {
            delete modularRobot;
        }
};

//const std::string ConnectionsFromConfigParserTest::FILEPATH = "../../data/test/Test_robot.xml";
const std::string ModularRobotTest::FILEPATH = "../../data/test/Test_robot2.xml";

TEST_F( ModularRobotTest, robotMovesUsingHormonesAndTable)
{
    modularRobot->reset();

    modularRobot->run(max_time_ms);

    float distance = modularRobot->getTravelledDistance();
    std::cout << "Distance travelled: " << distance << std::endl;
    EXPECT_LT(600, distance );
}
