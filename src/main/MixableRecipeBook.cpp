//@(#) MixableRecipeBook.cpp


#include "MixableRecipeBook.h"
#include <iostream>
//

void MixableRecipeBook::browse() {
    std::cout << "*********************************************" << std::endl;
    std::cout << "Es gibt " << this->getNumberOfRecipes() << " Cocktails" << std::endl;

    for (int i = 0; i<this->getNumberOfRecipes(); i++) {
        Recipe* r = this->getRecipe(i);
        std::cout << r->getRecipeNo() << ". ";
        r->browse();
        std::cout << std::endl;
    }
    std::cout << "*********************************************" << std::endl;

}

MixableRecipeBook::MixableRecipeBook(AvailableIngredients * zv) {

    // Debug *********
    std::cout << "********** Rezepte vor dem Filtern **********" << std::endl;
    browse();
    // ******************

    setZutatenVerwalter(zv);
//function to update all Recipe in a book
//function to search all recipe steps in a recipe
//function to delete recipe if ingredient is not found then decrement recipe index by 1
  for (int i = 0; i < getNumberOfRecipes(); i++) {
    //bool x;
    Recipe *recipe = getRecipe(i);
    searchRecipe(recipe, i);
    //x = true;
    /*for (int j = 0; j < recipe->getNoOfRecipeSteps(); j++) {
      std::string gesuchteZutat;
      gesuchteZutat = recipe->getRecipeStep(j)->getZutat();
      //bool zOk = false;

      for (int k = 0; k < myZutatenVerwalter->getAnzahlVorhandeneZutaten(); k++) {
        if (myZutatenVerwalter->getZutat(k) == gesuchteZutat) {
          //zOk = true;
          return;
          //break;
        }
        deleteRecipe(i);
        --i;
      }



      if (!zOk) {
        x = false;
      }
    }*/
    /*if (!x) {
      if(deleteRecipe(i)) {
          --i;
          continue;
      };
    }*/
  }
}

void MixableRecipeBook::setZutatenVerwalter(AvailableIngredients * zv) {
    myZutatenVerwalter = zv;
}

bool MixableRecipeBook::searchIngredientInRecipe(AvailableIngredients *pZutatenVerwalter, std::string& gesuchteZutat) {
    for(int i{}; i < pZutatenVerwalter->getAnzahlVorhandeneZutaten(); i++) {
        if(pZutatenVerwalter->getZutat(i) == gesuchteZutat) {
            return true;
        }
    }
    return false;
}
void MixableRecipeBook::searchRecipe(Recipe *r, int& index) {
    for(int i{}; i < r->getNoOfRecipeSteps(); i ++) {
        std::string gesuchteZutat = r->getRecipeStep(i)->getZutat();
        if(!searchIngredientInRecipe(myZutatenVerwalter, gesuchteZutat)) {
          deleteRecipe(index);
          index--;
          break;
      }
    }
}
