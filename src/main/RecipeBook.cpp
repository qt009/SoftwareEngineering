#include <algorithm>
#include "RecipeBook.h"

Recipe* RecipeBook::getCaipirinhaRecipe(){
    auto* recipe = new Recipe();
    recipe->setName("Caipirinha");
    recipe->appendStep("Limettenstuecke", 8);
    recipe->appendStep("Zucker", 15);
    recipe->appendStep("Stampfen", 20);
    recipe->appendStep("Eis", 90);
    recipe->appendStep("Cachaca", 5);
    recipe->appendStep("Mischen", 10);
    return recipe;
}

Recipe* RecipeBook::getPlantersPunchRecipe(){
    auto* recipe = new Recipe();
    recipe->setName("Planters Punch");
    recipe->appendStep("Zitronensaft", 2);
    recipe->appendStep("Grenadine", 1);
    recipe->appendStep("Orangensaft", 8);
    recipe->appendStep("Rum braun", 6);
    recipe->appendStep("Eis", 100);
    recipe->appendStep("Mischen", 20);
    return recipe;
}

Recipe* RecipeBook::getMargaritaRecipe(){
    auto* recipe = new Recipe;
    recipe->setName("Margarita");
    recipe->appendStep("Zitronensaft", 2);
    recipe->appendStep("Cointreau", 2);
    recipe->appendStep("Tequilla", 4);
    recipe->appendStep("Eis", 50);
    recipe->appendStep("Mischen", 20);
    return recipe;
}


Recipe* RecipeBook::getDaiquiriRecipe(){
    auto* recipe = new Recipe;
    recipe->setName("Daiquiri");
    recipe->appendStep("Limettensaft", 2);
    recipe->appendStep("Zuckersirup", 2);
    recipe->appendStep("Rum weiss", 5);
    recipe->appendStep("Eis", 50);
    recipe->appendStep("Mischen", 20);
    return recipe;
}


Recipe* RecipeBook::getCaipiroskaRecipe(){
    auto* recipe = new Recipe;
    recipe->setName("Caipiroska");
    recipe->appendStep("Limettenstuecke", 8);
    recipe->appendStep("Zucker", 15);
    recipe->appendStep("Stampfen", 20);
    recipe->appendStep("Eis", 90);
    recipe->appendStep("Wodka", 5);
    recipe->appendStep("Mischen", 10);
    return recipe;
}

Recipe* RecipeBook::getCaipirissimaRecipe(){
    auto* recipe = new Recipe;
    recipe->setName("Caipirissima");
    recipe->appendStep("Limettenstuecke", 8);
    recipe->appendStep("Zucker", 15);
    recipe->appendStep("Stampfen", 20);
    recipe->appendStep("Eis", 90);
    recipe->appendStep("Rum weiss", 5);
    recipe->appendStep("Mischen", 10);
    return recipe;
}


Recipe* RecipeBook::getCubanIslandRecipe(){
    auto* recipe = new Recipe;
    recipe->setName("Cuban Island");
    recipe->appendStep("Zitronensaft", 2);
    recipe->appendStep("Cointreau", 2);
    recipe->appendStep("Rum weiss", 2);
    recipe->appendStep("Wodka", 2);
    recipe->appendStep("Eis", 30);
    recipe->appendStep("Mischen", 30);
    return recipe;
}

Recipe* RecipeBook::getMartiniJamesBRecipe(){
    auto* recipe = new Recipe;
    recipe->setName("Martini James B");
    recipe->appendStep("Gin", 6);
    recipe->appendStep("Wodka", 2);
    recipe->appendStep("Noilly Prat", 1);
    recipe->appendStep("Schuetteln", 10);
    return recipe;
}



RecipeBook::RecipeBook() {
    mRecipe.clear();

    // create a stream
    std::ifstream in;

    std::string fileName = "Rezepte.csv";
    // open file
    in.open(fileName.c_str(), std::ios::in);

    if (getFile(in)) { // file could not be opened

    makeRecipeExample();

    } else {
        readFile(in);
    }
    //use to remove cpp check warning, do nothing here
    addRecipe(nullptr);
}




bool RecipeBook::getFile(std::ifstream &in) const { return !in; }

RecipeBook::~RecipeBook() {
   mRecipe.clear();
}

int RecipeBook::getNumberOfRecipes() {
    return int(mRecipe.size());
}

Recipe * RecipeBook::getRecipe(unsigned int i) {
    if (getSize(i)) return nullptr;
    else {
        std::list<Recipe*>::iterator p; // Iterator
        advance(p = mRecipe.begin(), i); // p now points to the i-th element
        return *p; // value of p - the pointer back
    }
}

bool RecipeBook::getSize(unsigned int i) const { return i > mRecipe.size(); }

bool RecipeBook::deleteRecipe(unsigned int i) {
    if (i >= mRecipe.size())
        return false;
    else {
        std::list<Recipe*>::iterator p; // Iterator
        advance(p = mRecipe.begin(), i); // now p points to the i-th Element
        mRecipe.erase(p); // delete the element p is pointing to
        return true; // Success!
    }
}

void RecipeBook::makeRecipeExample() {
    auto* r1 = getCaipirinhaRecipe();
    this->mRecipe.push_back(r1);

    auto* r2 = getMargaritaRecipe();
    this->mRecipe.push_back(r2);

    auto* r3 = getDaiquiriRecipe();
    this->mRecipe.push_back(r3);

    auto* r4 = getPlantersPunchRecipe();
    this->mRecipe.push_back(r4);

    auto* r5 = getCaipiroskaRecipe();
    this->mRecipe.push_back(r5);

    auto* r6 = getCaipirissimaRecipe();
    this->mRecipe.push_back(r6);

    auto* r7 = getCubanIslandRecipe();
    this->mRecipe.push_back(r7);

    auto* r8 = getMartiniJamesBRecipe();
    this->mRecipe.push_back(r8);
}

bool RecipeBook::readFile(std::ifstream &in) {

    if(in)
    {

        /* Read and print */
        std::string line;

        std::getline(in, line);


        while (std::getline(in, line)) {
            std::istringstream inputString(line);
            auto* r1 = new Recipe;
            readIngredients(r1, inputString);
        }


        in.close();
        return true;
    }
    else
    {
        return false;
    }

}

bool RecipeBook::readIngredients(Recipe *recipe, std::istringstream &inputString) {
    std::string ingredient;
    std::string tempString;
    std::string name;
    if(inputString)
    {
        getline(inputString, name, ';');

        recipe->setName(name);

        while (getline(inputString, ingredient, ';') && !ingredient.empty()) {
            float number{};
            if (getline(inputString, tempString, ';')) {
                std::istringstream(tempString) >> number;
            }
            recipe->appendStep(ingredient, number);
        }
        recipe->setRecipeNo(mRecipe.size() + 1);
        this->mRecipe.push_back(recipe);
        return true;
    }
    else
    {
        return false;
    }

}

const std::list<Recipe *> &RecipeBook::getMRecipe() const {
    return mRecipe;
}

Recipe *RecipeBook::findRecipeWithRecipeNo(int number) {
    for(auto& re: mRecipe){
        if(re->getRecipeNo() == number) return re;
    }
    return nullptr;
}

void RecipeBook::addRecipe(Recipe *r) {
    if(r == nullptr) {
        return;
    }
    mRecipe.push_back(r);
}

