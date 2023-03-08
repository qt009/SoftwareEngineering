//@(#) AvailableIngredients.h

#ifndef VorhandeneZutaten_H_H
#define VorhandeneZutaten_H_H

#include <string>
#include <map>
#include <vector>
#include <list>
#include <fstream>

#include <iostream>

/**
 * @class AvailableIngredients
 * @brief
 *  Liest Zutaten aus Liste ein.
 *  Merkt sich in der Liste die Zutaten + Aggregatszustand.
 *
 */
class AvailableIngredients {
 public:
    /**
     * @brief a default constructor
     * @return A pointer to the created AvailableIngredients
     */
    AvailableIngredients(void);

    /**
     * @brief a constructor with debug mode as parameter
     * @param DEBUG_Mode set static debug mode
     */
    explicit AvailableIngredients(bool DEBUG_Mode);
    /**
     * @brief generate a copy constructor
     * @param copy
     */
    AvailableIngredients(AvailableIngredients& copy);

    /**
     * this creates a copy using assignment operator '='
     * @param cpy the object that needs to be copied
     * @return this object
     */
    AvailableIngredients& operator= (const AvailableIngredients& cpy);
    /**
     * @brief destructor \n
     * This will destroy the object
     */
    virtual ~AvailableIngredients();

    /**
     * @brief browse the available ingredients
     */
    void browse(void);

    /**
     * @brief get the ingredient
     */
    std::string getZutat(int);

    /**
     *
     * @return number of available ingredients
     */
    int getAnzahlVorhandeneZutaten();

 private:
    /**
     * @brief collection of ingredients
     */
    std::vector<std::string> * zutaten;

    /**
     * @brief debug mode
     */
    static bool DEBUG;

    /**
     * @brief add dummy ingredients
     */
    void DummyZutatenEinfuegen();

    /**
     * @brief read the ingredients file
     */
    virtual void ZutatenDateiEinlesen(std::string);

    /**
     * @brief number of dosier
     */
    int anzahlDosierer;

};
static std::string FileName;
#endif
