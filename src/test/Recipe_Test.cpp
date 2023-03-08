//
// Created by trung on 12/1/22.
//
#include <string>
#include "gtest/gtest.h"

#define protected public
#define private public
#include "Recipe.h"
#undef protected
#undef private

#include <sstream>

class RecipeTest: public ::testing::Test
{
protected:
    Recipe * recipe;
    std::stringstream test_cout;

    void SetUp() override
    {
        std::cout << "Start of " << "RecipeTest" << std::endl << std::flush;
        recipe = new Recipe();
    }

    virtual void TearDown()
    {

        delete recipe;

        std::cout << "End of " << "RecipeTest" << std::endl << std::flush;
    }
};

TEST_F(RecipeTest, getNoOfRecipeStepsTest) {
    recipe->appendStep("Zucker", 12);
    EXPECT_EQ(1, recipe->getNoOfRecipeSteps());
}

TEST_F(RecipeTest, getRecipeStepTest){
    recipe->appendStep("Eis", 12);
    EXPECT_EQ("Eis",  recipe->getRecipeStep(0)->getZutat());
}

TEST_F(RecipeTest, getNameTest){
    recipe->setName("Test");
    EXPECT_EQ("Test", recipe->getName());
}

TEST_F(RecipeTest, setNameTest){
    recipe->setName("Test");
    EXPECT_EQ("Test", recipe->mName);
}

TEST_F(RecipeTest, browseTest){
}

TEST_F(RecipeTest, appendStepTest){
    recipe->appendStep("Eis", 12);
    EXPECT_EQ("Eis",  recipe->getRecipeStep(0)->getZutat());
}

TEST_F(RecipeTest, doubleIngrdientsTest) {
    recipe->appendStep("Zutat", 10);
    recipe->appendStep("Mischen", 10);
    recipe->appendStep("Stampfen", 20);
    recipe->appendStep("Schuetteln", 30);
    EXPECT_EQ(10, recipe->getRecipeStep(0)->getMenge());
    EXPECT_EQ(10, recipe->getRecipeStep(1)->getMenge());
    EXPECT_EQ(20, recipe->getRecipeStep(2)->getMenge());
    EXPECT_EQ(30, recipe->getRecipeStep(3)->getMenge());
}