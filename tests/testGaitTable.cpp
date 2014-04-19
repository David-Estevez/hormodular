#include "gtest/gtest.h"
#include <iostream>
#include <string>
#include "GaitTable.h"


using namespace hormodular;

class GaitTableTest : public testing::Test
{
    public:
        GaitTable * gaitTable;
        static const float parameters1[3];
        static const float parameters2[3];

        virtual void SetUp()
        {
            gaitTable = new GaitTable( "../../data/test/test_gait_table.txt");
        }

        virtual void TearDown()
        {
            delete gaitTable;
            gaitTable = NULL;
        }
};

const float GaitTableTest::parameters1[3] = { 60, 0, 0};
const float GaitTableTest::parameters2[3] = { 60, 0, 120};

TEST_F( GaitTableTest, createdGaitTableExists)
{
    EXPECT_TRUE( gaitTable != NULL );
}

TEST_F( GaitTableTest, twoIDsLoaded)
{
    std::vector<unsigned long> IDs = gaitTable->getIDs();

    EXPECT_EQ(2, IDs.size());
    EXPECT_EQ(83506, IDs[0]);
    EXPECT_EQ(78896, IDs[1]);
    EXPECT_EQ(3, gaitTable->getNumParameters());
}

TEST_F( GaitTableTest, selectByIDReturnsParametersCorrectly)
{
    std::vector<float> answer1, answer2;

    answer1 = gaitTable->getParameters(83506);
    answer2 = gaitTable->getParameters(78896);

    ASSERT_EQ(3, answer1.size());
    ASSERT_EQ(3, answer2.size());

    for (int i = 0; i < 3; i++)
        EXPECT_FLOAT_EQ( parameters1[i], answer1[i]);

    for (int i = 0; i < 3; i++)
        EXPECT_FLOAT_EQ( parameters2[i], answer2[i]);
}
