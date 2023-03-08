//@(#) Dispenser.h

#ifndef DOSIERER_H_H
#define DOSIERER_H_H

#include <string>
#include <iostream>

#include "Observer.h"
#include "InternalDevice.h"
#include "Waage.h"
/**
 * @class Dispenser
 * @brief this class inherited from InternalDevice and Observer\n
 * function: dispense an amount of ingredient when requested
 */
class Dispenser : public InternalDevice, public Observer {
public:
    /**
     * @brief a constructor of type Dispenser
     * @param g the amount of the to be dispensed ingredient over a timeframe
     * @param ze the timeframe
     * @param m_inhalt the m_inhalt
     * @param wg a pointer of type Waage (a weight)
     * @return a pointer to the created object
     */
    Dispenser(float g, int ze, const std::string& m_inhalt, Waage * wg);

    /**
     * @brief update the boolean variable doInIt which is inherited from InternalDevice
     */
    virtual void update();

    /**
     * @brief dispense in grams
     * @param gramm is the amount to be dispensed, measured in grams
     */
    void doIt(float gramm);

    /**
     *
     * @return  the amount of the attribute grammProZeit
     */
    int getStueckProZeit();
    /**
     * @brief add a new addtional dispenser
     */
    void addDispenser();
    /**
     *
     * @param x status of output
     */
    void setOutput(bool x);
    /**
     * @brief get gesamtgewicht
     */
    int getGesamtgewicht() const;
    /**
     * @brief clean the dispenser
     */
    void putzen();

    /**
     *
     * @param gramm amount of ingredient to dispense
     * @brief dispense ingredient
     */
    void dispense(int gramm);

private:
    /**
     * @brief the number of grams put on the scale per time internal
     */
    float grammProZeit;
/**
 * @brief the scale is used for weighing
 */
    Waage * myWaage;
/**
 * @brief the weight that should be on the scale
 */
    float gwicht;
/**
 * @brief the content to be loaded in Dispenser
 */
    std::string inhalt;

    int fillingStatus;
    /**
     * @brief pointer to dispenser with the same content
     */
    Dispenser* additionalDispenser = nullptr;
    /**
     * @brief the number of gram in the additionalDispenser
     */
     int gesamtgewicht = 1000;
     /**
      * @brief variable to show wether object can output in Doit
      */
     bool output = true;
};

#endif
