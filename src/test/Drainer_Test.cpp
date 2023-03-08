
#include <string>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "Drainer.h"
#undef protected
#undef private

class DrainerTest: public::testing::Test{
protected:
    Drainer* myDrainer = nullptr;
    Waage* myWaage = new Waage();
    float grammProZeit = 10;
    int zeitEinheit = 5;

    void SetUp(){
        std::cout << "Start of Drainer Test" << std::endl;

        myDrainer = new Drainer(grammProZeit, zeitEinheit, myWaage);
    }

    void TearDown(){
        delete myDrainer;
        myDrainer = nullptr;

        delete myWaage;
        myWaage = nullptr;

        std::cout << "End of DrainerTest" << std::endl;
    }
};
TEST_F(DrainerTest, update){
    myDrainer->update();
    if(myWaage->getWeight() <= myDrainer->value){
        EXPECT_EQ(0, myDrainer->doinIt);
    }
    else{
        EXPECT_EQ(1, myDrainer->doinIt);
    }
}

TEST_F(DrainerTest,doIt){
    float m_value = myDrainer->value;
    myDrainer->doIt(m_value);
    EXPECT_EQ(myDrainer->doinIt,0);
    EXPECT_EQ(myWaage->getWeight(),0);
}

//TEST_F(DrainerTest, getIsDeviceActiveFlag){
//    myDrainer->isDeviceActive = false;
//
//    EXPECT_FALSE(myDrainer->isUpdateNeeded());
//}
//
//TEST_F(DrainerTest, checkUpdateNeededWorkingCorrect){
//    myDrainer->myWaage->weight = 2;
//    myDrainer->minimumWeightValue = 3;
//
//    EXPECT_FALSE(myDrainer->isUpdateNeeded());
//}
//
//TEST_F(DrainerTest, checkConstructorValues){
//    EXPECT_EQ(5, myDrainer->gramsPerTimeUnit);
//    EXPECT_EQ(5, myDrainer->workingTimeUnit);
//    EXPECT_EQ(myWaage, myDrainer->myWaage);
//}
//
//TEST_F(DrainerTest, checkEmptyingActionWorkingCorrect){
//    myDrainer->emptying();
//
//    EXPECT_TRUE(myDrainer->getIsClean());
//    EXPECT_FALSE(myDrainer->isDeviceActive);
//}