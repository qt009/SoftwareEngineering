//
// Created by trung on 12/1/22.
//
#include "gtest/gtest.h"

#define protected public
#define private public
#include "Masher.h"
#undef protected
#undef private

#include <sstream>
class MasherTest: public ::testing::Test {
protected:
    Timer * myTimer;
    Masher * masher;
    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;
    void SetUp() override {
        std::cout << "Start of " << "MasherTest" << std::endl << std::flush;
        myTimer = Timer::getInstance();

        masher = new Masher();

    }


    virtual void TearDown()
    {
        delete masher;
        std::cout << "End of " << "MasherTest" << std::endl << std::flush;
    }
};

TEST_F(MasherTest, doItTest){
    masher->doIt(1);
    EXPECT_EQ(true, masher->needsCleaning);
}