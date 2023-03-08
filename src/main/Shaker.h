//@(#) Shaker.h

#ifndef SCHUETTLER_H_H
#define SCHUETTLER_H_H

#include "InternalDevice.h"

/**
 * @class Shaker
 *
 * @brief Shaker sets the internal device's time
 *
 */
class Shaker : public InternalDevice {
public:
    /** @brief Construktor
   */
    Shaker();

    /** @brief Makes the internal device sleep a certain time
    *
    */
    void doIt(float time) override;

private:
};

#endif
