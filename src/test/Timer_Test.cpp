#include <limits.h>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "Timer.h"
#undef protected
#undef private

class TimerTest : public ::testing::Test {
protected:
    Timer* r;

    virtual void SetUp() {
        r = new Timer();

        r->instanceFlag=false;
        r->theTimer=nullptr;
    }

    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
        delete r;
    }
};

TEST_F(TimerTest,setTurboTest){
    int neuTurbo=54;
    r->setTurbo(neuTurbo);

    EXPECT_EQ(neuTurbo,r->booster);
}

TEST_F(TimerTest,getInstanceTest){

    EXPECT_NE(r->getInstance(), nullptr);

}

