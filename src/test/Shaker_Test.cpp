#include <limits.h>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "Shaker.h"
#undef protected
#undef private

class ShakerTest : public ::testing::Test {
protected:
    Shaker* r;

    virtual void SetUp() {
        r = new Shaker();

    }

    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
        delete r;
    }
};

