//@(#) DeviceVerwalter.h

#ifndef DEVICEVERWALTER_H_H
#define DEVICEVERWALTER_H_H

#include <string>
#include <map>

#include "InternalDevice.h"
#include "AvailableIngredients.h"
#include "Dispenser.h"
#include "Mixer.h"
#include "Masher.h"
#include "Shaker.h"
#include "Drainer.h"
#include "Waage.h"

/**
 * @class DeviceVerwalter
 * @brief Befuellt die Dispenser, verwaltet die Interne Hardware
 *  
 */
class DeviceVerwalter {
public:
    /**
     * @brief create an object of type DeviceVerwalter
     * @param ze is a pointer of type AvailableIngredients
     * @return a pointer to this created object
     */
    explicit DeviceVerwalter(AvailableIngredients * ze);

    /**
     * @brief prepare steps to make the recipe
     * @param zutat is the name of the ingredient
     * @param menge is the amount of the ingredient
     */
    void rezeptSchrittZubereiten(std::string zutat, float menge);

    /**
     * a drainer object of type pointer Drainer
     */
    Drainer * myEntleerer;
    /**
     * @brief a pointer of type map\n
     * key is a name of an InternalDevice object\n
     * value is a pointer of type InternalDevice
     */
    std::map<std::string, InternalDevice *> * myDevices;
private:
    /**
     * @brief set the attribute myZutatenVerwalter
     * @param ze is a pointer of type AvailableIngredients
     */
    void setZutatenVerwalter(AvailableIngredients * ze);

    Mixer * myMixer;

    Masher * myStampfer;

    Shaker * mySchuettler;

    AvailableIngredients * myZutatenVerwalter;

    Waage * theWaage;

    /**
     * @brief create devices
     */
    void createDevices();

};

#endif
