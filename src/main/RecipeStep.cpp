
#include <algorithm>

#include "RecipeStep.h"

RecipeStep::RecipeStep() : rezeptZutat(""), rezeptMenge(0) {
//  this->rezeptZutat = "";
    //this->rezeptMenge = 0;
}

RecipeStep::~RecipeStep() {
    this->rezeptZutat = "";
    this->rezeptMenge = 0;
}

std::string RecipeStep::getZutat() const {
    return rezeptZutat;
}

float RecipeStep::getMenge() const {
    return rezeptMenge;
}

void RecipeStep::setZutat(std::string& mZutat) {
    this->rezeptZutat = mZutat;
}

void RecipeStep::setMenge(float neuMenge) {
    this->rezeptMenge = neuMenge;
}
