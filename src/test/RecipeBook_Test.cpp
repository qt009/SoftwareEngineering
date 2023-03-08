#include <limits.h>
#include "gtest/gtest.h"

// Using this ugly tweak you make all private elements public!
// But be careful! Some methods are private for good reasons!
// So please use this trick only if you really need it!
#define protected public
#define private public
#include "RecipeBook.h"
#undef protected
#undef private

class RecipeBookTest : public ::testing::Test {
 protected:
  RecipeBook* r;

  virtual void SetUp() {
        r = new RecipeBook();
        // you never know what the constructor is really doing
        // so make the list empty and fill it yourself!
        
        r->mRecipe.clear();
        Recipe* r1;

        r1 = new Recipe;
        r1->setName("Caipirinha");
        r1->appendStep("Limettenstuecke", 8);
        r->mRecipe.push_back(r1);

        r1 = new Recipe;
        r1->setName("Margarita");
        r1->appendStep("Zitronensaft", 2);
        r->mRecipe.push_back(r1);
          
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test
    // (right before the destructor).
    delete r;
  }
};

TEST_F(RecipeBookTest,getNumberOfRecipesReturnsValueOfAttribute){
    int noOfRecipes=r->mRecipe.size();
    EXPECT_EQ(noOfRecipes,r->getNumberOfRecipes());
}

TEST_F(RecipeBookTest,getRecipeReturnsCorrectRecipe){
    Recipe* rez;
    rez = r->getRecipe(0);
    EXPECT_EQ(rez->getName(),"Caipirinha");

    rez = r->getRecipe(1);
    EXPECT_EQ(rez->getName(),"Margarita");
}

TEST_F(RecipeBookTest,deleteRecipeRemovesCorrectRecipe){
    EXPECT_FALSE(r->deleteRecipe(-1));
    EXPECT_FALSE(r->deleteRecipe(42));
    EXPECT_FALSE(r->deleteRecipe(2)); 
    
    EXPECT_TRUE(r->deleteRecipe(0));
    // Since recipe #0 is deleted now Margarita is #0
    Recipe* rez;
    rez = r->getRecipe(0);
    EXPECT_EQ(rez->getName(),"Margarita");    
}

TEST_F(RecipeBookTest, readfileTest)
{
    std::ifstream wrongFile;

    EXPECT_TRUE(r->readFile(wrongFile));
}

TEST_F(RecipeBookTest, addRecipe){
    Recipe* re = r->getCubanIslandRecipe();
    r->addRecipe(re);
    auto iter = r->mRecipe.begin();
    advance(iter,2);
    EXPECT_EQ((*iter)->getName(), "Cuban Island");
}

