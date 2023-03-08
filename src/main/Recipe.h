#ifndef _REZEPT_H_479
#define _REZEPT_H_479

#include "RecipeStep.h"

#include <list>
#include <string>
/**
 * @class Recipe
 * @brief this class manages the step and content of recipe
 *
 */
class Recipe {
private:
    /**
     * @brief list of step in a recipe
     */
    std::list<RecipeStep*> mRecipeStep;
/**
 * @brief name of the recipe
 */
    std::string mName;

    /**
     * number of recipe;
     */
    int RecipeNo;
public:
    /**
     *
     * @return recipe number
     */
    int getRecipeNo() const;

    /**
     * set recipe number
     * @param recipeNo is the recipe number
     */
    void setRecipeNo(int recipeNo);

public:
    /**
     * @brief the default constructor clear all data in mRecipeStep und mName
     */
    Recipe(void);
    /**
     * @brief default destructor
     */
    ~Recipe();
/**
 * @brief get number of step in a recipe
 * @return return the number of step
 */
    int getNoOfRecipeSteps();
    /**
     * @brief get i-th step in the recipe
     * @param i is the i-th step in the recipe
     * @return the content of the step
     */
    RecipeStep * getRecipeStep(unsigned int i);
/**
 * @brief get function for recipe step's name
 * @return the name string
 */
    std::string getName(void) const;
/**
 * @brief set a new name for recipe step
 * @param Name name you want to set for the step
 */
    void setName(const std::string& Name);
/**
 * @brief add a new step to the recipe
 * @param z name of ingredient
 * @param m amount of ingredient
 */
    void appendStep(std::string z, float m);
/**
 * @brief browse recipe book
 */
    void browse();

};

#endif
