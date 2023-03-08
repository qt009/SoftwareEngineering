#include <limits.h>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "Waage.h"
#undef protected
#undef private

class WaageTest : public ::testing::Test {
protected:
    Waage* r;

    virtual void SetUp() {
        r = new Waage();
        r->weight=0;
        r->deltaWeight=0;

    }

    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
        delete r;
    }
};

TEST_F(WaageTest,changeWeightTest){
    int oldweight=r->weight;
    int v=34;
    r->changeWeight(v);
    EXPECT_EQ(r->weight,v+oldweight);

}

TEST_F(WaageTest,changeDeltaWeightTest){

    int olddeltaweight=r->deltaWeight;
    int v=45;
    r->changeWeight(v);
    EXPECT_EQ(r->deltaWeight,v+olddeltaweight);
}


TEST_F(WaageTest,TaraTest){
    r->tara();
    EXPECT_EQ(r->deltaWeight,0);

}

TEST_F(WaageTest,getWeightTest){

    EXPECT_EQ(r->getWeight(),r->weight);

}
TEST_F(WaageTest,getDeltaWeightTest){

    EXPECT_EQ(r->getDelta(),r->deltaWeight);

}