//@(#) Drainer.h

#ifndef ENTLEERER_H_H
#define ENTLEERER_H_H

#include <iostream>

#include "Observer.h"
#include "InternalDevice.h"
#include "Waage.h"

/**
 * @class Drainer
 * @brief this class inherited from InternalDevice and Observer\n
 * function: release the cocktail from the tank
 */
class Drainer : public InternalDevice, public Observer {
public:
    /**
     * @brief construct an object of type Drainer
     * @param g the amount of the to be drained cocktail over a timeframe
     * @param ze the timeframe
     * @param wg a pointer of type Waage (a weight)
     * @return a pointer to the created object
     */
    Drainer(float g, int ze, Waage * wg);
    /**
     * destructor
     */
    ~Drainer();

    /**
     * @brief update the boolean variable doInIt inherited from InternalDevice
     */
    void update();

    /**
     * @brief drain the cocktail in a m_value
     * @param m_value is the amount to be drained
     */
    void doIt(float m_value);

private:
    float grammProZeit;

    Waage * myWaage;

    float value;

};

#endif
