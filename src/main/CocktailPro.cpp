//@(#) CocktailPro.cpp


#include "CocktailPro.h"
#include <string>

//start CocktailPro, let customer choose cocktail and prepare it
void CocktailPro::start() {
    while (OperatingMode == OpMode::NORMAL) {
        int CocktailNo = waehle();
        if (CocktailNo == INPUT_CANCEL)
            OperatingMode = OpMode::STOP;
        else {
            if (isValidNumber(CocktailNo)) {
                Recipe *rezeptptr = theMischbaresRezeptbuch->findRecipeWithRecipeNo(CocktailNo);
                std::cout << rezeptptr->getName() << std::endl;
                theCocktailZubereiter->cocktailZubereiten(rezeptptr);
            } else {
                std::cout << "Falsche Cocktailnummer!" << std::endl;
            }
        }
    }
}

CocktailPro::CocktailPro(int argc, char **param) {
    theZutatenVerwalter = new AvailableIngredients;

    theMischbaresRezeptbuch = new MixableRecipeBook(theZutatenVerwalter);
    theDeviceVerwalter = new DeviceVerwalter(theZutatenVerwalter);
    theCocktailZubereiter = new BarTender(theDeviceVerwalter);
    theZutatenVerwalter = new AvailableIngredients;
    changeTequilaAmountForMargarita();

    Timer *theTimer = Timer::getInstance();
    if (argc == 2) {// this has to be changed later
        if (std::string(param[1]) == "-D") {
            this->OperatingMode = OpMode::DEMO;
            theTimer->setTurbo(1000);
            this->demo(1);
        } else { // Parameter => Turbo an
            theTimer->setTurbo(10);
        }
    }
    // Mischen
}

CocktailPro::CocktailPro(const CocktailPro &copy) {
    theZutatenVerwalter = new AvailableIngredients;
    *this->theZutatenVerwalter = *copy.theZutatenVerwalter;

    theMischbaresRezeptbuch = new MixableRecipeBook(theZutatenVerwalter);
    *this->theMischbaresRezeptbuch = *copy.theMischbaresRezeptbuch;

    theDeviceVerwalter = new DeviceVerwalter(theZutatenVerwalter);
    *this->theDeviceVerwalter = *copy.theDeviceVerwalter;

    theCocktailZubereiter = new BarTender(theDeviceVerwalter);
    *this->theCocktailZubereiter = *copy.theCocktailZubereiter;

    *this->theZutatenVerwalter = *copy.theZutatenVerwalter;

    Timer *theTimer = Timer::getInstance();
    OperatingMode = copy.OperatingMode;

    if(OperatingMode == OpMode::DEMO){
        theTimer->setTurbo(1000);
        this->demo(1);
    } else{
        theTimer->setTurbo(10);
    }

}

//for testing purpose
bool CocktailPro::demo(int i) {
    if (i == 0) i = 1;
    int CocktailNo = i;
    if (isValidNumber(CocktailNo)) {
        Recipe *rezeptptr = theMischbaresRezeptbuch->findRecipeWithRecipeNo(CocktailNo);
        std::cout << rezeptptr->getName() << std::endl;
        theCocktailZubereiter->cocktailZubereiten(rezeptptr);
        return true;
    } else {
        std::cout << "Falsche Cocktailnummer!" << std::endl;
        return false;
    }
}


int CocktailPro::waehle() {
    while (true) {
        std::cout << "********** Mischbare Rezepte **********" << std::endl;
        theMischbaresRezeptbuch->browse();
        std::cout << "Was haetten Sie denn gern? (-1 zum Verlassen)" << std::endl;

        std::string eingabe = "";

        //cin.ignore();
        std::cin >> eingabe;

        int zahl = atoi(eingabe.c_str());

        if (isValidNumber(zahl)) {
            return zahl;
        } else {
            //std::system("clear");
            std::cout << "MEEEP! Too many fingers on keyboard error!" << std::endl;
            std::cout << "Ihre Eingabe: " << eingabe << " existiert nicht!"
                      << std::endl;
        }
    }
}

bool CocktailPro::isValidNumber(int zahl) const {
    for(auto rcp : theMischbaresRezeptbuch->getMRecipe()){
        if (rcp->getRecipeNo() == zahl) return true;
    }
    if(zahl == INPUT_CANCEL) return true;
    return false;
}

CocktailPro::~CocktailPro() {
    delete theCocktailZubereiter;
    delete theDeviceVerwalter;
    delete theZutatenVerwalter;
}

CocktailPro &CocktailPro::operator= (const CocktailPro &cpy) {
    if(this != &cpy) {
        auto *tmp = new CocktailPro(cpy);
        std::swap(this->theCocktailZubereiter, tmp->theCocktailZubereiter);
        std::swap(this->theZutatenVerwalter, tmp->theZutatenVerwalter);
        std::swap(this->theDeviceVerwalter, tmp->theDeviceVerwalter);
        std::swap(this->theMischbaresRezeptbuch, tmp->theMischbaresRezeptbuch);
    }
    return *this;
}

CocktailPro::CocktailPro(bool demo) {
    theZutatenVerwalter = new AvailableIngredients;

    theMischbaresRezeptbuch = new MixableRecipeBook(theZutatenVerwalter);
    theDeviceVerwalter = new DeviceVerwalter(theZutatenVerwalter);
    theCocktailZubereiter = new BarTender(theDeviceVerwalter);
    theZutatenVerwalter = new AvailableIngredients;

    Timer *theTimer = Timer::getInstance();
    if (demo) {// this has to be changed later
        this->OperatingMode = OpMode::DEMO;
        theTimer->setTurbo(1000);
        this->demo(1);
    }
}

void CocktailPro::changeTequilaAmountForMargarita() {
    for(auto* recipe : theMischbaresRezeptbuch->getMRecipe()){
        if(recipe->getName() == "Margarita"){
            for (int i{}; i < recipe->getNoOfRecipeSteps(); ++i){
                if(recipe->getRecipeStep(i)->getZutat() == "Tequilla"){
                    recipe->getRecipeStep(i)->setMenge(450);
                    break;
                }
            }
            break;
        }
    }
}


