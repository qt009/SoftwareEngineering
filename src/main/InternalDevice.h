//@(#) InternalDevice.h

#ifndef INTERNALDEVICE_H_H
#define INTERNALDEVICE_H_H

#include "Timer.h"

/**
 * @class InternalDevice
 *
 * @brief InternalDevice includes masher, mixer, shaker, dispenser and drainer \n
 *
 */
class InternalDevice {
public:
    /**
     * @brief pure virtual function doIt for others machines
     * @param value
     */
    virtual void doIt(float value) = 0;
    /**
     * @brief print out putzen messages
     */
    void putzen();

private:
    /**
     * @brief set timer
     */
    void setTimer();


public:
    /**
     * @brief default constructor for internal device
     */
    InternalDevice();
//    /**
//     * @brief getter function
//     * @return value of needCleaning
//     */
//     bool wasUsed() {return needsCleaning;}
protected:
    /**
     * @brief time unit
     */
    int zeiteinheit;
    /**
     * @brief status
     */
    bool doinIt;
    /**
     * @brief Timer object
     */
    Timer * myTimer;
    /**
     * @brief value to track if devices needs to be cleaned
     * need to set true in doIt(), so the device is cleaned
     * set to false in putzen()
     */
     bool needsCleaning;

};

#endif
