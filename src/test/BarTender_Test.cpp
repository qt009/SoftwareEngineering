#include <limits.h>
#include <string>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "BarTender.h"
#undef protected
#undef private

#include <sstream>

class BarTenderTest: public ::testing::Test
{
protected:
    BarTender* bt;
    AvailableIngredients* ai ;
    DeviceVerwalter* dv;
    RecipeBook *testBook;
    Timer *myTimer;

    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;

    void SetUp() override
    {
        // Check whether cout works normal - otherwise you will get very strange errors
        // if someone else made a mistake when redirecting cout
        std::cout << "Start of " << "BarTenderTest" << std::endl << std::flush;

        // redirect cout to my test_cout stream for testing
        // and store orig cout for restoring after test (!!!do not forget to restore!!!)
        orig_cout = std::cout.rdbuf(test_cout.rdbuf());

        ai = new AvailableIngredients();
        dv = new DeviceVerwalter(ai);
        bt = new BarTender(dv);
        testBook = new RecipeBook();
        myTimer = myTimer->getInstance();
        myTimer->setTurbo(1000);
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
        std::cout.rdbuf(orig_cout); // redirect cout back to standard cout
        delete ai;
        ai = nullptr;


        delete dv;
        dv = nullptr;

        delete bt;
        bt = nullptr;


        // Check whether cout works normal again - otherwise the next one using cout
        // will get very strange behavior
        std::cout << "End of " << "BarTenderTest" << std::endl << std::flush;
    }
};

TEST_F(BarTenderTest, testConstructor){
    delete ai;
    ai = nullptr;

    delete dv;
    dv = nullptr;

    delete bt;
    bt = nullptr;

    AvailableIngredients* testAI = new AvailableIngredients();
    DeviceVerwalter* testDV = new DeviceVerwalter(testAI);
    bt = new BarTender(testDV);

    EXPECT_EQ(testDV, bt->myDeviceVerwalter);
}

TEST_F(BarTenderTest, test_CocktailZubereiten){
    for(int i = 0; i < testBook->getNumberOfRecipes(); ++i){
        Recipe* r = testBook->getRecipe(i);
        bool RecipeAvailable = true;
        for(int j{};j<r->getNoOfRecipeSteps() ;++j){

            auto rcpStep = r->getRecipeStep(j);

            for(auto zu = ai->zutaten->begin(); zu <= ai->zutaten->end(); ++zu){
                if(zu == ai->zutaten->end()) {
                    RecipeAvailable = false;
                    break;
                }
                if (rcpStep->getZutat() == *zu) break;
            }
            if(!RecipeAvailable) break;
        }
        if(!RecipeAvailable) continue;
        EXPECT_TRUE(bt->cocktailZubereiten(r));
    }
}

TEST_F(BarTenderTest, test_checkIfInRecipeSteps){
    const std::string name1 = "Eis";
    const std::string name2 = "Zitronensaft";
    Recipe *rzpt = testBook->getRecipe(0);

    EXPECT_TRUE(bt->checkIfInRecipeSteps(name1, rzpt));
    EXPECT_FALSE(bt->checkIfInRecipeSteps(name2, rzpt));
}