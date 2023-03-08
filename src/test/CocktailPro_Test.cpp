#include <limits.h>
#include <string>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "CocktailPro.h"
#undef protected
#undef private

#include <sstream>

class CocktailProTest: public ::testing::Test
{
protected:
    const std::string ZutatenFile = "zutaten.txt";

    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;

    CocktailPro* cp;
    Timer* t;

    void SetUp() override
    {
        // Check whether cout works normal - otherwise you will get very strange errors
        // if someone else made a mistake when redirecting cout
        std::cout << "Start of " << "CocktailProTest" << std::endl << std::flush;

        // redirect cout to my test_cout stream for testing
        // and store orig cout for restoring after test (!!!do not forget to restore!!!)
        orig_cout = std::cout.rdbuf(test_cout.rdbuf());

        cp = new CocktailPro(true);
        t = Timer::getInstance();
        t->setTurbo(1000);

    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
        std::cout.rdbuf(orig_cout); // redirect cout back to standard cout
        delete cp;
        cp = nullptr;
        // Check whether cout works normal again - otherwise the next one using cout
        // will get very strange behavior
        std::cout << "End of " << "CocktailProTest" << std::endl << std::flush;
    }
};

TEST_F(CocktailProTest, test_start){
    cp->OperatingMode = cp->NORMAL;
    std::stringstream iss("2 3 0 99 -1");
    std::cin.rdbuf(iss.rdbuf());
    cp->start();
}

TEST_F(CocktailProTest, test_constructor_with_params){

    int argc = 2;
    char** param = new char*[2];
    std::string argv1 = "testing";
    std::string argv2 = "-D";
    param[0] = const_cast<char*>(argv1.c_str());
    param[1] = const_cast<char*>(argv2.c_str());

    auto * c= new CocktailPro(argc, param);
    EXPECT_TRUE(c->OperatingMode == c->DEMO);

}

TEST_F(CocktailProTest, test_copyConstructor){
    auto* cpTest = new CocktailPro(*cp);
    EXPECT_EQ(cpTest->theZutatenVerwalter->getAnzahlVorhandeneZutaten(),
              cp->theZutatenVerwalter->getAnzahlVorhandeneZutaten());

    EXPECT_EQ(cpTest->theMischbaresRezeptbuch->getNumberOfRecipes(),
              cp->theMischbaresRezeptbuch->getNumberOfRecipes());

    EXPECT_EQ(cpTest->theDeviceVerwalter->myDevices->size(),
              cp->theDeviceVerwalter->myDevices->size());

    EXPECT_EQ(cp->OperatingMode, cpTest->OperatingMode);

    cp->OperatingMode = cp->NORMAL;
    auto *cpTest2 = new CocktailPro(*cp);
    EXPECT_EQ(cpTest2->theZutatenVerwalter->getAnzahlVorhandeneZutaten(),
              cp->theZutatenVerwalter->getAnzahlVorhandeneZutaten());

    EXPECT_EQ(cpTest2->theMischbaresRezeptbuch->getNumberOfRecipes(),
              cp->theMischbaresRezeptbuch->getNumberOfRecipes());

    EXPECT_EQ(cpTest2->theDeviceVerwalter->myDevices->size(),
              cp->theDeviceVerwalter->myDevices->size());

    EXPECT_EQ(cp->OperatingMode, cpTest2->OperatingMode);

    delete cpTest;
    delete cpTest2;
}

//TEST_F(CocktailProTest, test_demo){
//    EXPECT_TRUE(cp->demo(0));
//    EXPECT_FALSE(cp->demo(2));
//    EXPECT_TRUE(cp->demo(8));
//}
//
//TEST_F(CocktailProTest, test_waehle){
//    std::stringstream iss("6");
//    std::cin.rdbuf(iss.rdbuf());
//    EXPECT_EQ(cp->waehle(),6);
//}

TEST_F(CocktailProTest, test_isValidNumber){
    EXPECT_TRUE(cp->isValidNumber(-1));
    EXPECT_FALSE(cp->isValidNumber(4));
}

TEST_F(CocktailProTest, testDestructor){
    delete cp;
    cp = nullptr;

    EXPECT_TRUE(cp == nullptr);
}

TEST_F(CocktailProTest,testAssignmentOperator){
    auto* cpTest = new CocktailPro(true);
    *cpTest = *cp;
    EXPECT_EQ(cpTest->theZutatenVerwalter->getAnzahlVorhandeneZutaten(),
              cp->theZutatenVerwalter->getAnzahlVorhandeneZutaten());

    EXPECT_EQ(cpTest->theMischbaresRezeptbuch->getNumberOfRecipes(),
              cp->theMischbaresRezeptbuch->getNumberOfRecipes());

    EXPECT_EQ(cpTest->theDeviceVerwalter->myDevices->size(),
              cp->theDeviceVerwalter->myDevices->size());

    EXPECT_EQ(cp->OperatingMode, cpTest->OperatingMode);

}

TEST_F(CocktailProTest, testConstructorWithDemo){
    delete cp;
    cp = nullptr;

    cp = new CocktailPro(true);
    EXPECT_TRUE(cp->OperatingMode = cp->DEMO);
}

TEST_F(CocktailProTest, testChangeTequillaAmountForMargarita){
    float newMenge = 450;
    float thisMenge;
    for(auto* recipe : cp->theMischbaresRezeptbuch->getMRecipe()){
        if(recipe->getName() == "Margarita"){
            for (int i{}; i < recipe->getNoOfRecipeSteps(); ++i){
                if(recipe->getRecipeStep(i)->getZutat() == "Tequilla"){
                    recipe->getRecipeStep(i)->setMenge(newMenge);
                    thisMenge = recipe->getRecipeStep(i)->getMenge();
                    break;
                }
            }
            break;
        }
    }
    EXPECT_EQ(thisMenge, newMenge);
}