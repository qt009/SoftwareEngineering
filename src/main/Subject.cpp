//@(#) Subject.cpp


#include "Subject.h"

void Subject::attach(Observer * observer) {
    this->observers.push_back(observer);
}


void Subject::notify() {
    for (int i = observers.size() - 1; i >= 0; i--) {
        observers.at(i)->update();
    }
}
