//@(#) Mixer.h

#ifndef MIXER_H_H
#define MIXER_H_H

#include <iostream>

#include "InternalDevice.h"
/**
 * @class Mixer
 * @brief Mix ingredient \n
 */
class Mixer : public InternalDevice {
public:
    /**
     * @brief default constructor for Mixer
     */
    Mixer();

    /**
     * @brief set machine to sleep for an amount of time
     * @param time amount of time you want machine to sleep
     */

    void doIt(float time);

private:

};

#endif
