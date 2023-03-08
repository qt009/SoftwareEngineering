//@(#) Drainer.cpp


#include "Drainer.h"

Drainer::Drainer(float g, int ze, Waage * wg) : InternalDevice() {
    this->grammProZeit = g;
    this->zeiteinheit = ze;
    this->myWaage = wg;
    this->myWaage->attach(this);
}

Drainer::~Drainer(){

}

//

void Drainer::update() {
    if (!this->doinIt) return;
    if (myWaage->getWeight() <= this->value)
        doinIt = 0;
}

//drain the cocktail from the tank to the customer
void Drainer::doIt(float m_value) {
    std::cout << "Ihr Cocktail hat ein Gesamtgewicht von " << myWaage->getWeight() << "g" << std::endl;
    std::cout << "Entleervorgang wird begonnen..." << std::endl;
    this->value = m_value;
    doinIt = 1;
    while (doinIt) {
        myTimer->sleepInIntervals(zeiteinheit);
        myWaage->changeWeight(-grammProZeit);
    }
    std::cout << std::endl;
    std::cout << "Entleervorgang wurde beendet, bitte entnehmen Sie ihren Cocktail!" << std::endl;
    std::cout << std::endl;
    needsCleaning = true;
}
