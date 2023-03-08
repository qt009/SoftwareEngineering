//@(#) InternalDevice.cpp


#include "InternalDevice.h"

void InternalDevice::setTimer() {
}

InternalDevice::InternalDevice() {
    myTimer = Timer::getInstance();
    this->doinIt = 0;       //false
    zeiteinheit = 0;
    setTimer();
    needsCleaning = false;
}

void InternalDevice::putzen() {
//    std::cout << "Ich putze mich..." << std::endl;
//    myTimer->sleep(500);
//    std::cout << "Ich bin fertig mit putzen!" << std::endl;
    needsCleaning = false;
}
