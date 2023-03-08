//@(#) Masher.h

#ifndef STAMPFER_H_H
#define STAMPFER_H_H

#include "InternalDevice.h"
/**
 * @class Masher
 *
 * @brief Masher device to mash ingredient \n
 *
 */
class Masher : public InternalDevice {
public:
    /**
     *  @brief default constructor for masher
     */
    Masher();
    /**
     *
     * @brief put machine to sleep for an amount of time
     *
     * @param time amount of time you want machine to sleep
     *
     */
    void doIt(float time);

private:
};

#endif
