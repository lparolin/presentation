#include "../heating.h"
#include <gtest/gtest.h>

TEST(ComputeHeatingTime, IncreasingTemperature) {
    EXPECT_EQ(computeHeatingTime(20U, 30U), 10U);
}

TEST(ComputeHeatingTime, SameTemperature) {
    EXPECT_EQ(computeHeatingTime(25U, 25U), 0U);
}

TEST(ComputeHeatingTime, DecreasingTemperatureNoUnderflow) {
    EXPECT_EQ(computeHeatingTime(50U, 49U), 0U);
}

// int main(int argc, char **argv) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
