//@(#) BarTender.h

#ifndef COCKTAILZUBEREITER_H_H
#define COCKTAILZUBEREITER_H_H



#include "Recipe.h"
#include "RecipeBook.h"
#include "DeviceVerwalter.h"

/**
 * @class BarTender
 * @brief Bereitet den Cocktail nach den Rezeptschritten zu.
 *  
 */
class BarTender {
public:
    /**
     * @brief constructor that created a BarTender object
     * @return a pointer to this created Bartender object
     * @param dv is a pointer of type DeviceVerwalter, which regulates the internal hardware
     */
    explicit BarTender(DeviceVerwalter * dv);
    /**
     * @brief check if cocktail can be generated with the given recipe, if yes then generate
     * @param rzpt recipe
     * @return true if cocktail is successfully generated, otherwise false
     */
    bool cocktailZubereiten(Recipe * rzpt);

    /**
     * check if this name is included in the recipe steps list
     * @param name is the name of the recipe step that needs to be checked
     * @param rzpt is the recipe
     * @return true if equal, else false
     */
    bool checkIfInRecipeSteps(const std::string& name, Recipe* rzpt);
    /**
     * @brief check if there's enough ingredient
     * @return return true if there's enough, false if not
     */
     bool checkRecipeIngredient(Recipe * rzpt);

private:
    /**
     * @brief a pointer of type DeviceVerwalter
     */
    DeviceVerwalter * myDeviceVerwalter;


};

#endif
