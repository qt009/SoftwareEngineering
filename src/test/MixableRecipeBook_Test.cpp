#include <limits.h>
#include <string>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "MixableRecipeBook.h"
#undef protected
#undef private

#include <sstream>

class MixableRecipeBookTest: public ::testing::Test
{
protected:
    AvailableIngredients *zv;
    MixableRecipeBook * book;
    std::basic_streambuf<char>* orig_cout;
    std::stringstream test_cout;

    void SetUp() override
    {
        // Check whether cout works normal - otherwise you will get very strange errors
        // if someone else made a mistake when redirecting cout
        std::cout << "Start of " << "MixableRecipeBookTest" << std::endl << std::flush;

        // redirect cout to my test_cout stream for testing
        // and store orig cout for restoring after test (!!!do not forget to restore!!!)

        orig_cout = std::cout.rdbuf(test_cout.rdbuf());

        zv = new AvailableIngredients();
        book = new MixableRecipeBook(zv);
        test_cout.str("");
    }

    virtual void TearDown()
    {
        // Code here will be called immediately after each test
        // (right before the destructor).
        std::cout.rdbuf(orig_cout); // redirect cout back to standard cout
        delete zv;
        delete book;

        // Check whether cout works normal again - otherwise the next one using cout
        // will get very strange behavior
        std::cout << "End of " << "MixableRecipeBookTest" << std::endl << std::flush;
    }
};

TEST_F(MixableRecipeBookTest, browseTest){
    test_cout.str("");
    book->browse();
    std::string output = test_cout.str();

    EXPECT_EQ(!std::string::npos, output.find("Es gibt 6 Cocktails") == std::string::npos);

}