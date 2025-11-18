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

// Design-by-Contract tests for computeHeatingTimeDbC
class ComputeHeatingTimeDbCTest : public ::testing::Test {
protected:
    uint16_t result;
};

TEST_F(ComputeHeatingTimeDbCTest, ValidIncreasingTemperature) {
    // PRECONDITION: finalTemp >= initialTemp, time != nullptr
    // POSTCONDITION: returns true, *time = 10
    bool ret = computeHeatingTimeDbC(20U, 30U, &result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result, 10U);
}

TEST_F(ComputeHeatingTimeDbCTest, ValidSameTemperature) {
    // PRECONDITION: finalTemp >= initialTemp, time != nullptr
    // POSTCONDITION: returns true, *time = 0
    bool ret = computeHeatingTimeDbC(25U, 25U, &result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result, 0U);
}

TEST_F(ComputeHeatingTimeDbCTest, PreconditionViolation_DecreasingTemperature) {
    // PRECONDITION VIOLATED: finalTemp < initialTemp
    // POSTCONDITION: returns false, *time unchanged
    result = 999U;
    bool ret = computeHeatingTimeDbC(50U, 49U, &result);
    EXPECT_FALSE(ret);
    EXPECT_EQ(result, 999U);  // No side effects on failure
}

TEST_F(ComputeHeatingTimeDbCTest, PreconditionViolation_NullPointer) {
    // PRECONDITION VIOLATED: time == nullptr
    // POSTCONDITION: returns false, no crash
    bool ret = computeHeatingTimeDbC(20U, 30U, nullptr);
    EXPECT_FALSE(ret);
}

TEST_F(ComputeHeatingTimeDbCTest, ValidLargeTemperatureDifference) {
    // INVARIANT: result fits in uint16_t
    // POSTCONDITION: returns true, *time = 200
    bool ret = computeHeatingTimeDbC(0U, 200U, &result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result, 200U);
}

TEST_F(ComputeHeatingTimeDbCTest, ValidMaxTemperatureDifference) {
    // INVARIANT: result fits in uint16_t even at max uint8_t difference
    // POSTCONDITION: returns true, *time = 255
    bool ret = computeHeatingTimeDbC(0U, 255U, &result);
    EXPECT_TRUE(ret);
    EXPECT_EQ(result, 255U);
}

