//@(#) DeviceVerwalter.cpp


#include "DeviceVerwalter.h"

DeviceVerwalter::DeviceVerwalter(AvailableIngredients * zv) {
    setZutatenVerwalter(zv);
    this->createDevices();
}



void DeviceVerwalter::createDevices() {   //Geräte werden erstellt
    theWaage = new Waage();
    myDevices = new std::map<std::string, InternalDevice *>;  //[Keyword - Gerät]-Paare werden gespeichert

    myEntleerer = new Drainer(25, 1000, theWaage);
    myDevices->insert(std::make_pair("Entleeren", myEntleerer));

    myStampfer = new Masher();
    myDevices->insert(std::make_pair("Stampfen", myStampfer));

    mySchuettler = new Shaker();
    myDevices->insert(std::make_pair("Schuetteln", mySchuettler));

    myMixer = new Mixer();
    myDevices->insert(std::make_pair("Mischen", myMixer));

    std::string myZutat;
    for (int i = myZutatenVerwalter->getAnzahlVorhandeneZutaten() - 4; i >= 0; i--) {
        myZutat=myZutatenVerwalter->getZutat(i);  // [Zutat - Dispenser]-Paare werden erstellt und gespeichert
        if (myZutat == "Eis")                     //special case: Eis und Limettenstuecke -> grammProZeit weicht von standard ab
            myDevices->insert(std::make_pair(myZutat, new Dispenser(20, 1000, myZutat, theWaage)));
        else if (myZutat == "Limettenstuecke")
            myDevices->insert(std::make_pair(myZutat, new Dispenser(10, 1000, myZutat, theWaage)));
        else {
            if (myDevices->find(myZutat) != myDevices->end())
                dynamic_cast<Dispenser*>(myDevices->at(myZutat))->addDispenser();
            else
                myDevices->insert(std::make_pair(myZutat, new Dispenser(1, 250, myZutat, theWaage)));
        }
    }
}
void DeviceVerwalter::setZutatenVerwalter(AvailableIngredients * zv) {
    myZutatenVerwalter = zv;
}

//prepare cocktail with the given recipe and amount
void DeviceVerwalter::rezeptSchrittZubereiten(std::string zutat, float menge) {

    if (zutat == "Limettenstuecke") {
        //nach stücke bestellen
        int stckProZeit = reinterpret_cast<Dispenser*>(myDevices->at(zutat))->getStueckProZeit();
        myDevices->at(zutat)->doIt(menge * stckProZeit);
    } else {
        myDevices->at(zutat)->doIt(menge);
    }
}

