
#include <algorithm>
#include <iostream>

#include "Recipe.h"

Recipe::Recipe(void) {
    mRecipeStep.clear();
    mName = "";
    static int RecipeID = 0;
    RecipeNo = RecipeID;
    RecipeID++;
}

Recipe::~Recipe() {
}

int Recipe::getNoOfRecipeSteps() {
    return (mRecipeStep.size());
}

RecipeStep * Recipe::getRecipeStep(unsigned int i) {
    if (i > mRecipeStep.size()) return NULL;
    else {
        std::list<RecipeStep*>::iterator p; // Iterator
        advance(p = mRecipeStep.begin(), i); // p zeigt jetzt auf das i-te Element
        return (*p); // Adresse vom Wert von p - also den Pointer auf den der Iterator zeigt
    }
}

std::string Recipe::getName(void) const {
    return mName;
}

void Recipe::setName(const std::string& Name) {
    this->mName = Name;
}

void Recipe::browse() {
    std::cout << mName << ": ";
    for (int i = 0; i< this->getNoOfRecipeSteps(); i++) {
        if (i > 0) std::cout << ", ";
        std::cout << getRecipeStep(i)->getZutat();
    }
}

void Recipe::appendStep(std::string z, float m) {
    RecipeStep* t;
    t = new RecipeStep;
    t->setZutat(z);
    t->setMenge(m);
    mRecipeStep.push_back(t);
}

int Recipe::getRecipeNo() const {
    return RecipeNo;
}

void Recipe::setRecipeNo(int recipeNo) {
    RecipeNo = recipeNo;
}
