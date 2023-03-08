//@(#) AvailableIngredients.cpp

#include "AvailableIngredients.h"
//
const std::string ZutatenFile = "zutaten.txt";
bool AvailableIngredients::DEBUG = false;
AvailableIngredients::AvailableIngredients(void) {
    zutaten = new std::vector<std::string>;

    // int einlesen(list<string>* zutaten, std::string FileName)
    // Stream anlegen


    ZutatenDateiEinlesen(ZutatenFile);


    browse();

    zutaten->push_back("Mischen");
    zutaten->push_back("Stampfen");
    zutaten->push_back("Schuetteln");

    anzahlDosierer = zutaten->size();

}

AvailableIngredients::AvailableIngredients(bool DEBUG_Mode) {

    DEBUG = DEBUG_Mode;
    // int einlesen(list<string>* zutaten, std::string FileName)
    // Stream anlegen

    if (DEBUG) {
        zutaten = new std::vector<std::string>;
        DummyZutatenEinfuegen();
        browse();

        zutaten->push_back("Mischen");
        zutaten->push_back("Stampfen");
        zutaten->push_back("Schuetteln");

        anzahlDosierer = zutaten->size();
    } else {
        zutaten = new std::vector<std::string>;
        ZutatenDateiEinlesen(ZutatenFile);
        browse();

        zutaten->push_back("Mischen");
        zutaten->push_back("Stampfen");
        zutaten->push_back("Schuetteln");

        anzahlDosierer = zutaten->size();
    }


}

AvailableIngredients::AvailableIngredients(AvailableIngredients &copy) {
    zutaten = new std::vector<std::string>;
    for(const auto& p: *copy.zutaten){
        zutaten->push_back(p);
    }
    browse();

    anzahlDosierer = copy.anzahlDosierer;

}


AvailableIngredients::~AvailableIngredients(void) {

}

//readFile
void AvailableIngredients::ZutatenDateiEinlesen(std::string myfile) {
    std::ifstream in;

    FileName = myfile;

    in.open(FileName.c_str(), std::ios::in); // c_str wandelt den String in char[]
    // das braucht fstream

    if (!in) {// File konnte nicht geoeffnet werden
        std::string my_exception = "File not found: " + FileName;
        std::cout << my_exception << std::endl;
        throw my_exception;
    }

    std::cout << "Oeffne Zutatendatei " << FileName << std::endl;

    std::string zeile;
    while (getline(in, zeile)) {

        // Cut trailing \r - to make Linux or Windows Files equal
        if (zeile.size() && zeile[zeile.size() - 1] == '\r') {
            zeile = zeile.substr(0, zeile.size() - 1);
        }

        this->zutaten->push_back(zeile);
    }
    in.close();
}


void AvailableIngredients::DummyZutatenEinfuegen() {
    zutaten->push_back("Limettenstuecke");
    zutaten->push_back("Zucker");
    zutaten->push_back("Cointreau");
    zutaten->push_back("Eis");
    zutaten->push_back("Wodka");
    zutaten->push_back("Rum weiss");
    zutaten->push_back("Zitronensaft");
    zutaten->push_back("Grenadine");
    //    zutaten->push_back("Limettensaft");
    //    zutaten->push_back("Tequilla");
    //    zutaten->push_back("Gin");
    //    zutaten->push_back("Noilly Prat");
}

void AvailableIngredients::browse(void) {
    std::cout << "*********** Verfuegbare Einheiten bzw. Zutaten: ***********" << std::endl;
    for (unsigned int i = 0; i < zutaten->size(); i++/*std::string zutat : zutaten*/) {
        std::cout << zutaten->at(i) << std::endl;
    }
    std::cout << "**********************************************************" << std::endl;
}

std::string AvailableIngredients::getZutat(int i) {
    return zutaten->at(i);
}

int AvailableIngredients::getAnzahlVorhandeneZutaten() {
    return zutaten->size();
}

AvailableIngredients& AvailableIngredients::operator= (const AvailableIngredients &cpy) {
    if (this != &cpy) {
        delete zutaten;
        zutaten = new std::vector<std::string>;
        for (const auto &p: *cpy.zutaten) {
            zutaten->push_back(p);
        }
        browse();
        anzahlDosierer = cpy.anzahlDosierer;


    }
    return *this;
}



