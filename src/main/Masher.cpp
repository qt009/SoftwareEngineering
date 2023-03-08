//@(#) Masher.cpp


#include "Masher.h"

Masher::Masher() : InternalDevice() {
}

void Masher::doIt(float time) {
    myTimer->sleepInIntervals(time * 1000);
    std::cout << std::endl;
    needsCleaning = true;
}
