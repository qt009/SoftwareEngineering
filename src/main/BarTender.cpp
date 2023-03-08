//@(#) BarTender.cpp


#include "BarTender.h"

BarTender::BarTender(DeviceVerwalter * dv) {
    myDeviceVerwalter = dv;
}

//prepare cocktail with the given recipe
bool BarTender::cocktailZubereiten(Recipe * rzpt) {
    //std::system("clear");
    std::cout << "Hallo, ich bin der BarTender!" << std::endl
              << "Ich habe Ihre Bestellung: " << rzpt->getName() << " erhalten." << std::endl
              << "Jetzt geht es los!\n" << std::endl;
    if(!checkRecipeIngredient(rzpt)) {
        std::cout << "There's not enough ingredient" << std::endl;
        return false;
    }
    int i;

    //TODO: user story 5, wenn die Zutaten nicht mehr reichen, dann abbrechen sie die Prozess
    for (i = 0; i < rzpt->getNoOfRecipeSteps(); i++) {
        RecipeStep * schritt = rzpt->getRecipeStep(i);
        std::string zutat = schritt->getZutat();
        float menge = schritt->getMenge();
        std::cout << "Rezeptschritt: " << zutat << ", " << menge << std::endl;
        myDeviceVerwalter->rezeptSchrittZubereiten(zutat, menge);
    }
    myDeviceVerwalter->myEntleerer->doIt(i);

    for (std::map<std::string, InternalDevice *>::iterator i1 = myDeviceVerwalter->myDevices->begin();
         i1 != myDeviceVerwalter->myDevices->end(); ++i1) {
        if(checkIfInRecipeSteps(i1->first, rzpt)) {
            std::cout << "Device mit der Aktion: " << i1->first << " wird jetzt geputzt: " << std::endl;
            i1->second->putzen();
        }
    }
    return (true);
}

bool BarTender::checkIfInRecipeSteps(const std::string &name, Recipe *rzpt) {
    for(int i = 0; i<rzpt->getNoOfRecipeSteps();++i){
        if(rzpt->getRecipeStep(i)->getZutat() == name) return true;
    }
    return false;
}
bool BarTender::checkRecipeIngredient(Recipe *rzpt) {
    for (int i = 0; i < rzpt->getNoOfRecipeSteps(); i++) {
        RecipeStep * schritt = rzpt->getRecipeStep(i);
        std::string zutat = schritt->getZutat();
        if(zutat == "Entleeren" || zutat == "Stampfen" || zutat == "Schuetteln" || zutat == "Mischen" ) {
            continue;
        }
        float menge = schritt->getMenge();
        float vorhandenMenge = dynamic_cast<Dispenser*>(myDeviceVerwalter->myDevices->at(zutat))->getGesamtgewicht();
        if(zutat == "Limettenstuecke") {
            int stckProZeit = reinterpret_cast<Dispenser*>(myDeviceVerwalter->myDevices->at(zutat))->getStueckProZeit();
            menge = menge * stckProZeit;
        }
        if(menge > vorhandenMenge) {
            return false;
        }
    }
    return true;
}

