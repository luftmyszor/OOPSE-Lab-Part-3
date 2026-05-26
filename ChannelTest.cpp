// #include "pch.h"

#include "Channel.h"

struct ChannelFixture : public ::testing::Test {
    // You can remove any or all of the following functions if their bodies would
    // be empty.
    ChannelFixture() {
        // You can do set-up work for each test here.
    }
    ~ChannelFixture() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }
    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
    // Objects declared here can be used by all tests in the test suite for Channel.
    std::vector<double> inputs { 1., 2., 3., 4., 1.5, 1.99, 2.5, 3.5, 4.5, 4.99 };
    int bits { 16 };
    std::chrono::milliseconds clock_rate { 100 };
    double rangeMin { -5. }, rangeMax { 5. };
    double sensitivity { 1. }, trigger_level { 2. };
    ADC<short, 4> adc { bits, clock_rate, -5., 5., 1., 2. };
    Channel<short, 4> channel { std::move(adc) };
};

TEST_F(ChannelFixture, Initialization) {
    EXPECT_EQ(bits, channel.get_adc().bits);
    EXPECT_EQ(rangeMin, channel.get_adc().rangeMin);
    EXPECT_EQ(rangeMax, channel.get_adc().rangeMax);
    EXPECT_EQ(sensitivity, channel.get_adc().sensitivity);
    EXPECT_EQ(trigger_level, channel.get_adc().trigger_level);
}