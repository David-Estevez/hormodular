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
