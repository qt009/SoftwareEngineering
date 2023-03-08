//@(#) Waage.cpp


#include "Waage.h"

void Waage::changeWeight(int v) {
    weight += v;
    if (weight < 0)
        weight = 0;
    deltaWeight += v;
    notify();
}

int Waage::tara() {
    return deltaWeight = 0;
}

int Waage::getWeight() const {
    return weight;
}

int Waage::getDelta() const {
    return deltaWeight;
}

Waage::Waage() {
    weight=0;
    deltaWeight=0;
}
