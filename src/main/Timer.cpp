//@(#) Timer.cpp


#include "Timer.h"

const int maxValue = 1000;
void Timer::setTurbo(int turbo) {
    this->booster = turbo;
}

Timer * Timer::getInstance() {
    if (!instanceFlag) {
        theTimer = new Timer();
        instanceFlag = true;
        return theTimer;
    } else {
        return theTimer;
    }
}

void Timer::sleep(long delayInMs) const {
    // if netbeans does not recognize system_clock you have to set the project properties to C++11:
    // Project-Properties->Code Assistance -> C++ (and C). Set it to C++!
    long nowMillis = time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();
    long limit = nowMillis + (delayInMs / booster);
    
    while (limit > nowMillis) {

        nowMillis = time_point_cast<milliseconds>(system_clock::now()).time_since_epoch().count();
    }
}

void Timer::sleepInIntervals(long milliSeconds) const {
    // to improve compatibility between Linux and Windows this implementation
    // is using busy wait (and avoids threads)! On purpose...
    long delay=0;
    
    while (milliSeconds > 0) {
        if (milliSeconds >= maxValue){
            std::cout << "*" << std::flush;
            delay = maxValue;
            milliSeconds = milliSeconds - delay;
        } else {
            std::cout << "." << std::flush;
            delay = milliSeconds;
            milliSeconds = 0;
        }
        sleep(delay);
    }   
}


bool Timer::instanceFlag = false;

Timer * Timer::theTimer = nullptr;