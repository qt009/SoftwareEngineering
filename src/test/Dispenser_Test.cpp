
#include <string>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "Dispenser.h"
#undef protected
#undef private

class DispenserTest: public::testing::Test{
protected:
    Waage* myWaage = new Waage();
    Dispenser* myDispenser = nullptr;
    int ze = 1;
    float grammProZeit = 10;
    std::string zutat = "Eis";

    void SetUp(){
        std::cout << "Start of DispenserTest" << std::endl;

        //Dummy Dispenser
        myDispenser = new Dispenser(grammProZeit, ze, zutat, myWaage);
    }

    void TearDown(){
        delete myDispenser;
        myDispenser = nullptr;

        delete myWaage;
        myWaage = nullptr;

        std::cout << "End of DispenserTest" << std::endl;
    }
};
TEST_F(DispenserTest, update){
    myDispenser->doinIt = false;
    myDispenser->update();
    EXPECT_EQ(0, myDispenser->doinIt);

}

TEST_F(DispenserTest,doIt){
    float menge = 47;

    myDispenser->doIt(menge);
    if(zutat == "Eis") {
        if (static_cast<int>(menge) % static_cast<int>(myWaage->getDelta()) == 0) {
            EXPECT_EQ(menge, myWaage->getDelta());
        } else EXPECT_NE(menge, myWaage->getDelta());
    }
    else {
        EXPECT_EQ(menge, myWaage->getDelta());
    }
}


TEST_F(DispenserTest, getStueckProZeit){
    EXPECT_EQ(grammProZeit, myDispenser->getStueckProZeit());
}

