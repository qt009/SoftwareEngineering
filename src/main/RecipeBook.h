#ifndef RECIPEBOOK_H_489
#define RECIPEBOOK_H_489

#include <fstream>
#include <sstream>

#include <iostream>

#include <list>
#include <string>

#include "Recipe.h"

/**
 * @class RecipeBook
 *
 * @brief RecipeBook manages a collection of recipes
 *
 * A RecipeBook knows a list of recipes
 * You can ask for the number of recipes, query recipes by index
 * or delete a recipe
 *
 */
class RecipeBook {
    /**
    * This is the list of recipe pointers that the RecipeBook manages
    */
  private:
    std::list<Recipe *> mRecipe;
public:
    /**
     * @brief getter function for mRecipe
     * @return  list of recipe in recipe book
     */
    const std::list<Recipe *> &getMRecipe() const;

public:
    /** @brief Construktor that creates a RecipeBook
    * It uses temporarily an object of the class Initialisierer
    * to initialize the list of recipes pointers. After that the
    * Initialisierer is destroyed.
    */
    explicit RecipeBook();

    /** @brief removes all elements from mRecipe
    */
    virtual ~RecipeBook();

    /** @brief Returns the number of recipes
    * @return The number of recipes in the RecipeBook
    */
    int getNumberOfRecipes();

    /** @brief fetches the i-th recipe
    * @param [in] i a positive integer for the i-th recipe
    * @return A pointer to the requested recipe object, NULL for invalid i
    *
    * This method returns the i-th recipe;
    * where i is an integer from 0 to n-1
    * where n is the number of recipes in the RecipeBook
    */
    Recipe * getRecipe(unsigned int i);
    /**
     * @brief find the recipe with number
     * @param number is the recipe we need to find
     * @return the required recipe, return nullptr if not found
     */
    Recipe * findRecipeWithRecipeNo(int number);

    /** @brief Deletes the i-th recipe from the RecipeBook
    * @param [in] i a positive integer for the i-th recipe
    * @return Boolean that indicates whether the deletion was successful
    */
    bool deleteRecipe(unsigned int i);
    /**
     * @brief reads the file
     * @param [in] in is the file, which should opened
     */
    bool readFile(std::ifstream & in);
    /**
     * @brief reads the file
     * @param [recipe][inputString] recipe is object, which should be given, inputString is the info of recipe
     */
    bool readIngredients(Recipe *recipe, std::istringstream& inputString);
    /**
    * @brief takes the file
    * @param [in] in is the file, which should opened
    * @return in;
    */
    bool getFile(std::ifstream &in) const;
    /**
     * @brief takes size of m_recipe
     * @param [i] a iterator
     * @return i > mRecipe.size();
     */
    bool getSize(unsigned int i) const;

    /**
     * @brief makes Recipe examples for the programm and pushes examples in mRecipe
     */
    void makeRecipeExample();

    /**
     * add a recipe to list
     * @param r is recipe
     */
    void addRecipe(Recipe* r);
    /**
     * @brief makes Caipirinha Recipe example
     * @return recipe;
     */
    Recipe *getCaipirinhaRecipe();

    /**
    * @brief makes Planters Recipe example
    * @return recipe;
    */
    Recipe *getPlantersPunchRecipe();
    /**
     * @brief makes Margarita Recipe example
     * @return recipe;
     */
    Recipe *getMargaritaRecipe();
    /**
       * @brief makes Daiquiri Recipe example
       * @return recipe;
       */
    Recipe *getDaiquiriRecipe();
    /**
         * @brief makes Caipiroska Recipe example
         * @return recipe;
         */
    Recipe *getCaipiroskaRecipe();
    /**
       * @brief makes Caipirissima Recipe example
       * @return recipe;
       */
    Recipe *getCaipirissimaRecipe();
    /**
       * @brief makes CubanIsland Recipe example
       * @return recipe;
       */
    Recipe *getCubanIslandRecipe();
    /**
        * @brief makes MartiniJames Recipe example
        * @return recipe;
        */
    Recipe *getMartiniJamesBRecipe();
};

#endif

