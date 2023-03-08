//
// Created by trung on 12/1/22.
//
#include <limits.h>
#include <string>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "Mixer.h"
#undef protected
#undef private

#include <sstream>

class MixerTest: public ::testing::Test
{
protected:
    Timer * timer;
    Mixer * mixer;
    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;

    void SetUp() override
    {
        std::cout << "Start of " << "MixerTest" << std::endl << std::flush;
        timer = Timer::getInstance();
        mixer = new Mixer();

    }

    virtual void TearDown()
    {
        delete mixer;

        std::cout << "End of " << "MixerTest" << std::endl << std::flush;
    }
};


TEST_F(MixerTest, doItTest){
    mixer->doIt(1);
    EXPECT_EQ(true, mixer->needsCleaning);
}