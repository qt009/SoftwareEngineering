#include "gtest/gtest.h"

#define protected public
#define private public
#include "CocktailPro.h"
#undef protected
#undef private

class UserStory3 : public::testing::Test {
protected:
    CocktailPro* cocktailPro;

    void SetUp() override{
        std::cout<<"Start of UserStory3 Test"<<std::endl;
        cocktailPro = new CocktailPro(true);
    }

    void TearDown() override{
        if(cocktailPro){
            delete cocktailPro;
            cocktailPro = nullptr;
        }
        std::cout<<"End of UserStory3 Test"<<std::endl;
    }
};

TEST_F (UserStory3, testCocktailTaste){
    auto* devs = cocktailPro->theDeviceVerwalter->myDevices;
    for(auto iter = devs->begin(); iter != devs->end(); iter ++){
        if(dynamic_cast<Dispenser*>(iter->second) != nullptr){
            auto* dispenser = dynamic_cast<Dispenser*>(iter->second);
            //setTank to almost full
            dispenser->fillingStatus = 0;
        }
    }
    for (int i = 1; i<=8; ++i){
        if ((i == 2) || (i == 4)) continue;
        if (cocktailPro->isValidNumber(i)) {
            Recipe *rezeptptr = cocktailPro->theMischbaresRezeptbuch->findRecipeWithRecipeNo(i);
            std::cout << rezeptptr->getName() << std::endl;
            EXPECT_TRUE(cocktailPro->theCocktailZubereiter->cocktailZubereiten(rezeptptr));
        }
    }

}


