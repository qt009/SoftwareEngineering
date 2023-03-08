#ifndef _REZEPTSCHRITT_H_472
#define _REZEPTSCHRITT_H_472

#include <list>
#include <string>

/**
 * @class RecipeStep
 *
 * @brief RecipeStep creates recipe with ingredients and amounts
 *
 * You can ask for the amount or ingredient of recipe
 *
 */
class RecipeStep {

 private:
    /**
   * This is the string of recipe ingredients
   */
    std::string rezeptZutat;
    /**
   * This is the amount of recipe ingredients
   */
    float rezeptMenge;

 public:
    /**
     * @brief Construktor assigns values for rezeptMenge and rezeptZutat
     */
    RecipeStep();
    /** @brief all values are reset
    */
    ~RecipeStep();

    /** @brief Returns the ingredient of recipes
    * @return The ingredient of recipes in the RecipeStep
    */
    std::string getZutat() const;

    /** @brief Returns the amount of recipes
    * @return The amount of recipes in the RecipeStep
    */
    float getMenge() const;

    /**
     * @brief given parameter is assigned to rezeptZutat
    */
    void setZutat(std::string& mZutat);

    /**
    * @brief given parameter is assigned to rezeptMenge
   */
    void setMenge(float neuMenge);

};
#endif
