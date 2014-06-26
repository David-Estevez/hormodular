#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include <vector>
#include "ConfigParser.h"

using namespace hormodular;

class ConfigParserTest : public testing::Test
{
    public:
        ConfigParser configParser;

        static const std::string FILEPATH;

        virtual void SetUp()
        {
            configParser.parse(FILEPATH);
        }
};

//const std::string ConfigParserTest::FILEPATH = "../../data/test/Test_robot.xml";
const std::string ConfigParserTest::FILEPATH = "../../data/test/Test_robot2.xml";

TEST_F( ConfigParserTest, robotNameIsOk)
{
    EXPECT_STREQ( "Test_robot", configParser.getRobotName().c_str() );
}


TEST_F( ConfigParserTest, simulationFileIsOk)
{
    EXPECT_STREQ( "../../data/models/REPY-2.1/Kusanagi-2.env.xml", configParser.getSimulationFile().c_str() );
}

TEST_F( ConfigParserTest, gaitTableFolderIsOk)
{
    EXPECT_STREQ( "../../data/gait tables/test", configParser.getGaitTableFolder().c_str() );
}


TEST_F( ConfigParserTest, frequencyTableIsOk)
{
    EXPECT_STREQ( "../../data/gait tables/frequencies.txt", configParser.getFrequencyTableFile().c_str() );
}


TEST_F( ConfigParserTest, serialPortIsOk)
{
    EXPECT_STREQ( "/dev/ttyUSB0", configParser.getSerialPort().c_str() );
}

TEST_F( ConfigParserTest, masterJointsAreOk)
{
    ASSERT_EQ(1, configParser.getMasterJoints().size() );
    EXPECT_EQ(0, configParser.getMasterJoints()[0]);
}

TEST_F( ConfigParserTest, slaveJointsAreOk)
{
    ASSERT_EQ(1, configParser.getSlaveJoints().size() );
    EXPECT_EQ(1, configParser.getSlaveJoints()[0]);
}

TEST_F( ConfigParserTest, numberOfModulesIsOk)
{
    EXPECT_EQ(2, configParser.getNumModules());
}

TEST_F( ConfigParserTest, jointIDsAreOk)
{
    EXPECT_EQ( 0, configParser.getJointID(0));
    EXPECT_EQ( 1, configParser.getJointID(1));
}

TEST_F( ConfigParserTest, functionIDsAreOk)
{
    std::vector<ModuleFunction> id_function_vector = configParser.getFunctionIDs();
    EXPECT_EQ( ModuleFunction_limb, id_function_vector.at(0));
    EXPECT_EQ( ModuleFunction_coxa, id_function_vector.at(1));
}

TEST_F( ConfigParserTest, depthIDsAreOk)
{
    std::vector<int> id_depth_vector = configParser.getDepthIDs();
    EXPECT_EQ( 0, id_depth_vector.at(0));
    EXPECT_EQ(-1, id_depth_vector.at(1));
}

TEST_F( ConfigParserTest, shapeIDsAreOk)
{
    std::vector<unsigned long> id_shape_vector = configParser.getShapeIDs();
    EXPECT_EQ(42, id_shape_vector.at(0));
    EXPECT_EQ(66, id_shape_vector.at(1));
}

TEST_F( ConfigParserTest, numLimbsIDsAreOk)
{
    std::vector<int> id_num_limbs_vector = configParser.getNumLimbsIDs();
    EXPECT_EQ(1, id_num_limbs_vector.at(0));
    EXPECT_EQ(1, id_num_limbs_vector.at(1));
}

TEST_F( ConfigParserTest, limbIDsAreOk)
{
    std::vector<int> id_limbs_vector = configParser.getLimbsIDs();
    EXPECT_EQ(0, id_limbs_vector.at(0));
    EXPECT_EQ(-1, id_limbs_vector.at(1));
}

TEST_F( ConfigParserTest, connectorInfoIsOk)
{
    //-- Increase legibility
    static const int FRONT = 0;
    static const int LEFT = 1;
    static const int BACK = 2;
    static const int RIGHT = 3;

    static const int CONNECTED_TO = 0;
    static const int CONNECTOR = 1;
    static const int ORIENTATION = 2;

    //--Get info
    std::vector< std::vector<int> > connector1info, connector2info;
    connector1info = configParser.getConnectorInfo(0);
    connector2info = configParser.getConnectorInfo(1);

    //-- Check assertions
    EXPECT_EQ(1, connector1info[FRONT][CONNECTED_TO]);
    EXPECT_EQ(BACK, connector1info[FRONT][CONNECTOR]);
    EXPECT_EQ(0, connector1info[FRONT][ORIENTATION]);

    EXPECT_EQ(0, connector1info[RIGHT].size());
    EXPECT_EQ(0, connector1info[BACK].size());
    EXPECT_EQ(0, connector1info[LEFT].size());

    EXPECT_EQ(0, connector2info[BACK][CONNECTED_TO]);
    EXPECT_EQ(FRONT, connector2info[BACK][CONNECTOR]);
    EXPECT_EQ(0, connector2info[BACK][ORIENTATION]);

    EXPECT_EQ(0, connector2info[FRONT].size());
    EXPECT_EQ(0, connector2info[RIGHT].size());
    EXPECT_EQ(0, connector2info[LEFT].size());
}

TEST_F( ConfigParserTest, orientationReadOk)
{
    //--Get info
    std::vector<Orientation> orientations = configParser.getOrientations();

    ASSERT_EQ(2, orientations.size());

    EXPECT_EQ(0, orientations[0].getRoll());
    EXPECT_EQ(0, orientations[0].getPitch());
    EXPECT_EQ(0, orientations[0].getYaw());

    EXPECT_EQ(0, orientations[1].getRoll());
    EXPECT_EQ(0, orientations[1].getPitch());
    EXPECT_EQ(0, orientations[1].getYaw());
}
