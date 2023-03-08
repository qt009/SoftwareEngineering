//@(#) Subject.h

#ifndef SUBJECT_H_H
#define SUBJECT_H_H

#include "Observer.h"

#include <vector>
#include <iostream>

/**
 * @class Subject
 * @brief Subject manages with 3 functions a collection of observers
 * A Subject knows a vector of observers
 */
class Subject {
public:
    /**
    * @brief this function adds the given parameter to the observers vector
    */
    void attach(Observer * observer);


    /**
    * @brief this function updates the observers vector
    */
    void notify();

private:
  /**
  * @brief This is the vector of observers pointers that the Subject manages
  */
    std::vector<Observer *> observers;

};

#endif
