#include <limits.h>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "Subject.h"
#include "Observer.h"
#undef protected
#undef private

class SubjectTest : public ::testing::Test {
protected:
    Subject* r;

    virtual void SetUp() {
        r = new Subject();
        // you never know what the constructor is really doing
        // so make the list empty and fill it yourself!

        r->observers.clear();


    }

    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
        delete r;
    }
};

TEST_F(SubjectTest,testAttach){
    Observer*ob;
    r->attach(ob);
    int index=r->observers.size()-1;
    Observer*ob2=r->observers.at(index);
    EXPECT_EQ(ob2,ob);
}


