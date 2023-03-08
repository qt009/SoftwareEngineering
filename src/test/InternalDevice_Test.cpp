//
// Created by trung on 12/1/22.
//


#include <string>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "InternalDevice.h"
#include "Mixer.h"
#undef protected
#undef private

#include <sstream>

class InternalDeviceTest: public ::testing::Test
{
protected:
    InternalDevice * internalDevice;
    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;

    void SetUp() override
    {
        std::cout << "Start of " << "InternalDeviceTest" << std::endl << std::flush;


        internalDevice = new Mixer();

    }

    virtual void TearDown()
    {
        delete internalDevice;

        std::cout << "End of " << "DispenserTest" << std::endl << std::flush;
    }
};

TEST_F(InternalDeviceTest, putzenTest){
    internalDevice->putzen();
    EXPECT_EQ(false, internalDevice->needsCleaning);
}