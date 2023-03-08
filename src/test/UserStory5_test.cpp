//
// Created by edward on 19.01.23.
//
#include <limits.h>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "AvailableIngredients.h"
#include "Dispenser.h"
#include "DeviceVerwalter.h"
#include "RecipeBook.h"
#include "BarTender.h"
#undef protected
#undef private

class UserStory5Test : public ::testing::Test {
protected:
    Timer * timer;

    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;

    std::basic_streambuf<char>* orig_cin;
    std::stringstream test_cin;
    RecipeBook* r;
    BarTender* b;

    virtual void SetUp() {
        std::cout << "Start of " << "UserStory5Test" << std::endl << std::flush;

        orig_cout = std::cout.rdbuf(test_cout.rdbuf());
        orig_cin = std::cin.rdbuf(test_cin.rdbuf());
        timer = Timer::getInstance();
        timer->setTurbo(1'000'000);
        test_cout.str("");


    }

    virtual void TearDown() {
        std::cout.rdbuf(orig_cout);
        std::cin.rdbuf(orig_cin);
        timer->setTurbo(1);
        std::cout << "End of " << "UserStory5Test" << std::endl << std::flush;
    }
};

TEST_F(UserStory5Test, storyTest)
{
    //create AvailableIngredients, replace Ingredients from file
    AvailableIngredients * zv = new AvailableIngredients();
    zv->zutaten->clear();
    zv->zutaten->push_back("Zucker");
    zv->zutaten->push_back("Cachaca");
    zv->zutaten->push_back("Limettenstuecke");
    zv->zutaten->push_back("Eis");
    zv->zutaten->push_back("Mischen");
    zv->zutaten->push_back("Stampfen");
    zv->zutaten->push_back("Schuetteln");

    //create Deviceverwalter with Testingredients
    DeviceVerwalter *dv = new DeviceVerwalter(zv);

    //test if DeviceVerwalter has correctly added the ingredients with duplicates
    EXPECT_EQ(1000, dynamic_cast<Dispenser*>(dv->myDevices->at("Zucker"))->getGesamtgewicht());
    EXPECT_EQ(1000, dynamic_cast<Dispenser*>(dv->myDevices->at("Cachaca"))->getGesamtgewicht());
    EXPECT_EQ(1000, dynamic_cast<Dispenser*>(dv->myDevices->at("Limettenstuecke"))->getGesamtgewicht());
    EXPECT_EQ(1000, dynamic_cast<Dispenser*>(dv->myDevices->at("Eis"))->getGesamtgewicht());
    r = new RecipeBook();
    // you never know what the constructor is really doing
    // so make the list empty and fill it yourself!
    r->mRecipe.clear();

    //create new recipe with 1 simple ingredient
    Recipe* r1;
    Recipe* r2;
    r1 = new Recipe;
    r1->setName("Caipirinha");
    r1->appendStep("Cachaca", 1001);
    r->mRecipe.push_back(r1);
    r2 = new Recipe;
    r2->setName("Caipirinha");
    r2->appendStep("Cachaca", 200);
    r->mRecipe.push_back(r2);

    //create a bartender to test
    b = new BarTender(dv);

    //test the function checkRecipeIngredient
    EXPECT_FALSE(b->checkRecipeIngredient(r1));
    EXPECT_TRUE(b->checkRecipeIngredient(r2));

    b->cocktailZubereiten(r1);
    //this should return false and cancle the function, therefore no ingredient would be used
    EXPECT_EQ(1000, dynamic_cast<Dispenser*>(dv->myDevices->at("Cachaca"))->getGesamtgewicht());
    b->cocktailZubereiten(r2);
    //this will return true and 200g of Cachaca will be used
    EXPECT_EQ(800, dynamic_cast<Dispenser*>(dv->myDevices->at("Cachaca"))->getGesamtgewicht());
    b->cocktailZubereiten(r1);
    EXPECT_EQ(800, dynamic_cast<Dispenser*>(dv->myDevices->at("Cachaca"))->getGesamtgewicht());
    //test again with main function of bartender
    EXPECT_TRUE(b->cocktailZubereiten(r2));
    EXPECT_EQ(600, dynamic_cast<Dispenser*>(dv->myDevices->at("Cachaca"))->getGesamtgewicht());
    EXPECT_FALSE(b->cocktailZubereiten(r1));

    delete r1;
    delete r2;
    delete zv;
    delete dv;
    delete r;
    delete b;


}