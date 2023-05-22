#include <gtest/gtest.h>
#include "timer.h"

TEST(SimpleTimerTest, simpleTest) {
    ecs::utils::Timer timer;
    timer.Tick(0);
    ecs::utils::TimeStamp ts = timer.GetTimeStamp();
    EXPECT_EQ(uint32_t(ts), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
