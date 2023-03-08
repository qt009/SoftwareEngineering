#include <limits.h>
#include <string>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "AvailableIngredients.h"
#undef protected
#undef private

#include <sstream>

class AvailableIngredientsTest: public ::testing::Test
{
protected:
    const std::string ZutatenFile = "zutaten.txt";
    AvailableIngredients* zv;
    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;

    void SetUp() override
    {
        // Check whether cout works normal - otherwise you will get very strange errors
        // if someone else made a mistake when redirecting cout
        std::cout << "Start of " << "AvailableIngredientsTest" << std::endl << std::flush;

      // redirect cout to my test_cout stream for testing
      // and store orig cout for restoring after test (!!!do not forget to restore!!!)
      orig_cout = std::cout.rdbuf(test_cout.rdbuf());

      zv = new AvailableIngredients();
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
        std::cout.rdbuf(orig_cout); // redirect cout back to standard cout
        delete zv;
        zv = nullptr;
        // Check whether cout works normal again - otherwise the next one using cout
        // will get very strange behavior
         std::cout << "End of " << "AvailableIngredientsTest" << std::endl << std::flush;
    }
};

TEST_F(AvailableIngredientsTest, browse){
    std::string browseOutput = this->test_cout.str();
    std::string zutat;
    int ingredientNumber = 0 ;

    int beginOfLinePos = 0 ;
    int outputLineCount = 0;
    std::string delim =  "\n" ;
    while( (beginOfLinePos = browseOutput.find(delim)) != std::string::npos )
    {
        zutat = browseOutput.substr(0, beginOfLinePos);
        browseOutput.erase(0, beginOfLinePos + delim.length()); // erase \n

        if(outputLineCount++ < 2) continue; // skip the intro
        if(zutat.rfind("**", 0) == 0) break;
        /*
         * This method returns the position of the first character
         * of the last match of that given character or string before
         * that position else it returns string::npos
         */

        EXPECT_EQ(zutat, zv->getZutat(ingredientNumber++));
    }
}

TEST_F(AvailableIngredientsTest, getAnzahlVorhandeneZutaten)
{
    EXPECT_EQ(16,zv->getAnzahlVorhandeneZutaten());
}

TEST_F(AvailableIngredientsTest, FileZutatenDotTxtIsAvailable)
{
    // SetUp() redirects the standard cout to another stream (test_cout)
    // this stream can be read and compared
    // in TearDown() the normal cout is restored again

    test_cout.clear();
    zv->ZutatenDateiEinlesen("zutaten.txt");
    EXPECT_EQ("Oeffne Zutatendatei", test_cout.str().substr(0, 19));
    //std::string s = test_cout.str();
    //std::cout << "!!!" << s.substr(0,31) << "!!!" << std::endl;
}

TEST_F(AvailableIngredientsTest, FileZutatenDotTxtIsNotAvailable)
{
    // Test asserts that an exception is thrown and that the type of the exception is the one expected
    //https://stackoverflow.com/questions/23270078/test-a-specific-exception-type-is-thrown-and-the-exception-has-the-right-propert
    EXPECT_THROW(
    {
        try
        {
            zv->ZutatenDateiEinlesen("xxxx.txt");
        }
        catch( std::string e)
        {
            std::cout << e << std::endl;
            EXPECT_EQ("File not found", e.substr(0,14));
            throw;
        }
    }, std::string );
}

TEST_F(AvailableIngredientsTest, constructor){
    zv->zutaten->clear();
    delete zv;
    zv = nullptr;

    zv = new AvailableIngredients();
    EXPECT_EQ(zv->anzahlDosierer, 16);
}

TEST_F(AvailableIngredientsTest, constructor_with_DEBUG_true){
    zv->zutaten->clear();
    delete zv;
    zv = nullptr;

    bool DEBUG = true;
    zv = new AvailableIngredients(DEBUG);
    EXPECT_EQ(zv->anzahlDosierer, 11);
}

TEST_F(AvailableIngredientsTest, constructor_with_DEBUG_false){
    zv->zutaten->clear();
    delete zv;
    zv = nullptr;

    bool DEBUG = false;
    zv = new AvailableIngredients(DEBUG);
    EXPECT_EQ(zv->anzahlDosierer, 16);
}



TEST_F(AvailableIngredientsTest, DummyZutatenEinfuegen){
    zv->zutaten->clear();
    EXPECT_EQ(0, zv->getAnzahlVorhandeneZutaten());

    zv->DummyZutatenEinfuegen();
    EXPECT_EQ(8, zv->getAnzahlVorhandeneZutaten());
}

TEST_F(AvailableIngredientsTest, getZutat){
    for( int i = 0; i < zv->getAnzahlVorhandeneZutaten(); ++i) {
        EXPECT_FALSE(zv->getZutat(i).empty());
    }
}

TEST_F(AvailableIngredientsTest, copyConstructor){
    auto* test = new AvailableIngredients(*zv);
    EXPECT_EQ(test->anzahlDosierer, 16);
    bool result = (*(test->zutaten) == *(zv->zutaten));
    EXPECT_TRUE(result);
}

TEST_F(AvailableIngredientsTest, testAsignmentOperator){
    AvailableIngredients AI;
    auto& testIfEqual = AI;
    EXPECT_EQ(&testIfEqual,&AI);

    AvailableIngredients testIfNotEqual;
    testIfNotEqual = AI;
    EXPECT_EQ(testIfNotEqual.anzahlDosierer, 16);
    bool result = (*(testIfNotEqual.zutaten) == *(AI.zutaten));
    EXPECT_TRUE(result);

}

