#include "gtest/gtest.h"

#define protected public
#define private public
#include "CocktailPro.h"
#undef protected
#undef private

class UserStory1 : public::testing::Test {
protected:
    CocktailPro* cocktailPro;

    void SetUp() override{
        std::cout<<"Start of UserStory1 Demo"<<std::endl;
        int argc{ 1 };
        std::string str{ "CocktailPro.exe" };
        char* args{ &str[0] };
        char** argv = new char*[1]{ args };
        cocktailPro = new CocktailPro{ argc, argv };

        if(argv) {
            delete[] argv;
            argv = nullptr;
        }

        Timer* timer = Timer::getInstance();
        timer->setTurbo(1000);
    }

    void TearDown() override{
        if(cocktailPro){
            delete cocktailPro;
            cocktailPro = nullptr;
        }
        std::cout<<"End of UserStory1 Test. Die CocktailNo bleibt unverändert"<<std::endl;
    }
};


TEST_F(UserStory1, checkCocktailNumberAfterDeletingIngredient) {
    cocktailPro->theMischbaresRezeptbuch->browse();

    auto* ingredients = cocktailPro->theMischbaresRezeptbuch->myZutatenVerwalter;
    unsigned int wodkaIndex{0};
    for(; wodkaIndex < ingredients->zutaten->size(); ++wodkaIndex) {
        if("Wodka" == ingredients->zutaten->at(wodkaIndex)) break;
    }
    auto begin = ingredients->zutaten->begin();
    ingredients->zutaten->erase(begin + wodkaIndex, begin + wodkaIndex +1);
    cocktailPro->theMischbaresRezeptbuch->setZutatenVerwalter(ingredients);
    std::cout << "Wodka wurde aus der Zutatenliste entfernt." << std::endl;

    for (int i = 0; i < cocktailPro->theMischbaresRezeptbuch->getNumberOfRecipes(); i++) {

        Recipe *recipe = cocktailPro->theMischbaresRezeptbuch->getRecipe(i);
        cocktailPro->theMischbaresRezeptbuch->searchRecipe(recipe, i);
    }
    cocktailPro->theMischbaresRezeptbuch->browse();
}

TEST_F(UserStory1, checkCocktailNumberAfterAddingIngredient){
    auto* recipe = new Recipe;
    recipe->setRecipeNo(10);
    recipe->setName("MyLemonadeTest");
    recipe->appendStep("Zitronensaft", 5);
    recipe->appendStep("Eis", 20);
    recipe->appendStep("Mischen", 20);

    cocktailPro->theMischbaresRezeptbuch->browse();
    cocktailPro->theMischbaresRezeptbuch->addRecipe(recipe);
    for (int i = 0; i < cocktailPro->theMischbaresRezeptbuch->getNumberOfRecipes(); i++) {

        Recipe *re = cocktailPro->theMischbaresRezeptbuch->getRecipe(i);
        cocktailPro->theMischbaresRezeptbuch->searchRecipe(re, i);
    }
    cocktailPro->theMischbaresRezeptbuch->browse();
}