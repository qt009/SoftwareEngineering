#include <limits.h>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "RecipeStep.h"
#undef protected
#undef private

class RecipeStepTest : public ::testing::Test {
protected:
    RecipeStep* r;

    virtual void SetUp() {
        r = new RecipeStep();

        std::string x="";
        r->setZutat(x);
        r->setMenge(0);

    }

    virtual void TearDown() {
        // Code here will be called immediately after each test
        // (right before the destructor).
        delete r;
    }
};

TEST_F(RecipeStepTest,getMengeTest){
    float neumeng=10.8;
    r->setMenge(10.8);
    float meng= r->getMenge();
    EXPECT_EQ(meng,neumeng);
}

TEST_F(RecipeStepTest,getZutatTest){
    std::string neuZutat="Cola";
    r->setZutat(neuZutat);

    std::string testvar=r->getZutat();
    EXPECT_EQ(testvar,neuZutat);

}

TEST_F(RecipeStepTest,setZutatTest){

    std::string neuZutat="Cola";
    r->setZutat(neuZutat);

    EXPECT_EQ(r->getZutat(),"Cola");

}
TEST_F(RecipeStepTest,setMengeTest){

    float neuMenge=32.7;
    r->setMenge(neuMenge);

    EXPECT_EQ(r->getMenge(),neuMenge);

}