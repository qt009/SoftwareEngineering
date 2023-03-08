//@(#) MixableRecipeBook.h

#ifndef MISCHBARESREZEPTBUCH_H_H
#define MISCHBARESREZEPTBUCH_H_H

#include "Recipe.h"
#include "RecipeBook.h"
#include "AvailableIngredients.h"

#include <iostream>
#include <fstream>
#include <string>

/**
 *  @class MixableRecipeBook
 *  @brief this class knows mixable recipe based on ingredient and can output those \n
 *
 */
class MixableRecipeBook : public RecipeBook {
public:
    /**
     * @brief search for recipe that match available ingredient
     * @param ze is available ingredient
     */
    explicit MixableRecipeBook(AvailableIngredients * ze);
    /**
     * @brief browse recipe book
     */
    void browse();

private:
    /**
     * @brief pointer to AvailableIngredient
     */
    AvailableIngredients * myZutatenVerwalter;
    /**
     * @brief pointer to vector of recipes
     */
    std::vector<Recipe *> rezepte;
    /**
     * @brief set value for available ingredient
     * @param ze is available ingredient
     */
  void setZutatenVerwalter(AvailableIngredients * ze);
  /**
   * @brief search the
   * @param pZutatenVerwalter pointer to ZutatenVerwalter
   * @param gesuchteZutat the ingredient to look for in recipe
   * @return true if searched ingredient is there, false if not
   */
  bool searchIngredientInRecipe(AvailableIngredients* pZutatenVerwalter, std::string& gesuchteZutat);
  /**
   * @brief search the recipe if available Ingredient matched in any step
   * @param r recipe to search
   * @param index of recipe in a recipe book
   */
  void searchRecipe(Recipe* r, int& index);

};

#endif
