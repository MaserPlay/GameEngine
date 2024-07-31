//
// Created by super on 31.07.2024.
//
#include "gtest/gtest.h"
#include <gmock/gmock.h>
//TEST
#include "Physics.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}

TEST(PhysicsTest, AABBTest) {
    ASSERT_TRUE(AABB<short>(Quard<short>({0,0},1,1),Quard<short>({0,0},1,1)));
    ASSERT_FALSE(AABB<short>(Quard<short>({-1,-1},1,1),Quard<short>({0,0},1,1)));
    ASSERT_FALSE(AABB<short>(Quard<short>({2,2},1,1),Quard<short>({0,0},1,1)));
}