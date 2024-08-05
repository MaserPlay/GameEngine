//
// Created by super on 31.07.2024.
//
#include "gtest/gtest.h"
#include <gmock/gmock.h>

#include <memory>
//TEST
#include "Physics.h"
#include "SystemAdapter.h"

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    ::testing::InitGoogleMock(&argc, argv);

    return RUN_ALL_TESTS();
}
TEST(SystemAdapterTest, Readifstream_to_memory){

}

TEST(PhysicsTest, AABBTest) {
    ASSERT_TRUE(AABB<short>(Quard<short>({0,0},1,1),Quard<short>({0,0},1,1)));
    ASSERT_FALSE(AABB<short>(Quard<short>({-1,-1},1,1),Quard<short>({0,0},1,1)));
    ASSERT_FALSE(AABB<short>(Quard<short>({2,2},1,1),Quard<short>({0,0},1,1)));
}

TEST(AudioTest, ReadingWav_fromifstream) {
    auto sf = std::make_unique<SoundFile>();
    ASSERT_NO_THROW(sf->openRead("test_wav.wav"));
    ASSERT_EQ(sf->getChannelCount(),1);
    ASSERT_EQ(sf->getSampleRate(),44100);
//    ASSERT_EQ(sf->getOpenAlDataSize(),13192);
}