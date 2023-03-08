//@(#) Mixer.cpp


#include "Mixer.h"

Mixer::Mixer() : InternalDevice() {

}

void Mixer::doIt(float time) {
    myTimer->sleepInIntervals(time * 1000);
    std::cout << std::endl;
    needsCleaning = true;
}
