//@(#) Dispenser.cpp


#include "Dispenser.h"

Dispenser::Dispenser(float g, int ze, const std::string& m_inhalt, Waage * wg) : InternalDevice(), inhalt(m_inhalt){
    this->grammProZeit = g;
    this->zeiteinheit = ze;

    this->myWaage = wg;
    this->myWaage->attach(this);

}

void Dispenser::update() {
    if (!this->doinIt) return;
    if (myWaage->getDelta() >= gwicht) {
        doinIt = false;
    }

}

//dispense the fluid in an amount measured by gramm
void Dispenser::doIt(float gramm) {

    if(getGesamtgewicht()<gramm){
        std::cout << "Behälter müssen alle Neu befüllt werden.";
        exit(0);
    }

    if (gesamtgewicht >= gramm) {
        dispense(gramm);  //dispenser does it itself when it has enough
    } else if (additionalDispenser != nullptr) {  //when we have a backup
        if (gesamtgewicht > 0) {  //when the dispenser is not empty
            int remainder = gesamtgewicht;
            dispense(gesamtgewicht);  //dispense everything
            additionalDispenser->doIt(gramm - remainder); //have backup dispense the rest
        } else
            additionalDispenser->doIt(gramm); //when dispenser is empty, have other dispenser do everything
    }
    if (output)
        std::cout << "Es wurden " << gramm << "g " << inhalt
                  << " abgefuellt. Restinhalt: " << getGesamtgewicht() << "g\n\n";
}

//a measuring unit over a period of time
int Dispenser::getStueckProZeit() {
    return this->grammProZeit;
}
void Dispenser::setOutput(bool x) {
    output = x;
}
void Dispenser::addDispenser() {
    if(additionalDispenser == nullptr) {
        additionalDispenser = new Dispenser(grammProZeit, zeiteinheit, inhalt, myWaage);
        additionalDispenser->setOutput(false);
        //output of additional Dispenser set to false to prevent duplicate on printing
    }
    else {
        //add another dispenser to backup dispenser, creating a chain
        additionalDispenser->addDispenser();
    }
}
int Dispenser::getGesamtgewicht() const {
    if (additionalDispenser == nullptr)
        return gesamtgewicht;
    else
        return gesamtgewicht + additionalDispenser->getGesamtgewicht();
}

void Dispenser::putzen() {
    needsCleaning = false;
    if (additionalDispenser != nullptr) {
        additionalDispenser->putzen();
    }
}

void Dispenser::dispense(int gramm) {
    this->gwicht = gramm;
    myWaage->tara();
    doinIt = true;
    std::cout << inhalt << " Ventil wurde geoeffnet" << std::endl;
    while (doinIt) {
        myTimer->sleepInIntervals(zeiteinheit);
        myWaage->changeWeight(grammProZeit);
        //myWaage->changeWeight(0);
    }
    std::cout << std::endl << inhalt << " Ventil wurde geschlossen" << std::endl;
    gesamtgewicht = gesamtgewicht - myWaage->getDelta();
}
