//@(#) Shaker.cpp


#include "Shaker.h"

int num=1000;
Shaker::Shaker() : InternalDevice() {
}

void Shaker::doIt(float time) {
    myTimer->sleepInIntervals(time * num);
    std::cout << std::endl;
    needsCleaning = true;
}
