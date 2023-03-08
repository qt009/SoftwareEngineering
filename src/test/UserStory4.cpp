//
// Created by edward on 12.01.23.
//

#include <limits.h>
#include "gtest/gtest.h"


#define protected public
#define private public
#include "AvailableIngredients.h"
#include "Dispenser.h"
#include "DeviceVerwalter.h"
#undef protected
#undef private

class UserStory4Test : public ::testing::Test {
protected:
    Timer * timer;

    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;

    std::basic_streambuf<char>* orig_cin;
    std::stringstream test_cin;

    virtual void SetUp() {
        std::cout << "Start of " << "UserStory4Test" << std::endl << std::flush;

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
        std::cout << "End of " << "UserStory4Test" << std::endl << std::flush;
    }

};

TEST_F(UserStory4Test, storyTest)
{
    //create AvailableIngredients, replace Ingredients from file
    AvailableIngredients * zv = new AvailableIngredients();
    zv->zutaten->clear();
    zv->zutaten->push_back("Zutat1");
    zv->zutaten->push_back("Zutat1");
    zv->zutaten->push_back("Zutat1");
    zv->zutaten->push_back("Zutat2");
    zv->zutaten->push_back("Zutat2");
    zv->zutaten->push_back("Zutat3");
    zv->zutaten->push_back("Limettenstuecke");
    zv->zutaten->push_back("Limettenstuecke");
    zv->zutaten->push_back("Eis");
    zv->zutaten->push_back("Eis");
    zv->zutaten->push_back("Mischen");
    zv->zutaten->push_back("Stampfen");
    zv->zutaten->push_back("Schuetteln");

    //create Deviceverwalter with Testingredients
    DeviceVerwalter *dv = new DeviceVerwalter(zv);

    //test if DeviceVerwalter has correctly added the ingredients with duplicates
    EXPECT_EQ(3000, dynamic_cast<Dispenser*>(dv->myDevices->at("Zutat1"))->getGesamtgewicht());
    EXPECT_EQ(2000, dynamic_cast<Dispenser*>(dv->myDevices->at("Zutat2"))->getGesamtgewicht());
    EXPECT_EQ(1000, dynamic_cast<Dispenser*>(dv->myDevices->at("Zutat3"))->getGesamtgewicht());
    EXPECT_EQ(1000, dynamic_cast<Dispenser*>(dv->myDevices->at("Limettenstuecke"))->getGesamtgewicht());
    EXPECT_EQ(1000, dynamic_cast<Dispenser*>(dv->myDevices->at("Eis"))->getGesamtgewicht());


    //DeviceVerwalter should only see 9 Devices, it counts duplicate
    //(5 more dispenser from test ingredient, 4 default)
    EXPECT_EQ(9, dv->myDevices->size());



    dv->myDevices->at("Zutat1")->doIt(1100);
    EXPECT_EQ(1900, dynamic_cast<Dispenser *>(dv->myDevices->at("Zutat1"))->getGesamtgewicht());


    //test each case
    Waage * testWaage = new Waage();
    Dispenser * dispenserTest = new Dispenser(1, 250, "Testzutat", testWaage);

    //add an additional dispenser to it
    dispenserTest->addDispenser();

    EXPECT_EQ(2000, dispenserTest->getGesamtgewicht());
    //test dispensing from first dispenser
    dispenserTest->doIt(800);
    EXPECT_EQ(200, dispenserTest->gesamtgewicht);
    EXPECT_EQ(1000, dispenserTest->additionalDispenser->gesamtgewicht);
    //test reaching 0 on first dispenser
    dispenserTest->doIt(200);
    EXPECT_EQ(0, dispenserTest->gesamtgewicht);
    EXPECT_EQ(1000, dispenserTest->additionalDispenser->gesamtgewicht);
    //test dispensing from second dispenser when first is empty
    dispenserTest->doIt(800);
    EXPECT_EQ(0, dispenserTest->gesamtgewicht);
    EXPECT_EQ(200, dispenserTest->additionalDispenser->gesamtgewicht);

    //reset dispensers
    dispenserTest->gesamtgewicht = 1000;
    dispenserTest->additionalDispenser->gesamtgewicht = 1000;
    //test dispensing more then first dispenser holds
    dispenserTest->doIt(1500);
    EXPECT_EQ(0, dispenserTest->gesamtgewicht);
    EXPECT_EQ(500, dispenserTest->additionalDispenser->gesamtgewicht);

    delete zv;
    delete dv;
    delete testWaage;
    delete dispenserTest;

}