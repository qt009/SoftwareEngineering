//@(#) Waage.h

#ifndef WAAGE_H_H
#define WAAGE_H_H

#include "Subject.h"



/**
 * @class Waage
 * @brief Waage manages weight information
 * You can ask for the weight or change it
 */
class Waage : public Subject {
 public:
/** @brief Construktor that creates a RecipeBook
    */
    Waage();

   /** @brief changes weight with parameter v
    */
    void changeWeight(int v);

    /** @brief the delta is assigned  zero
    */
    int tara();

    /** @brief the function returns weight
    */
    int getWeight() const;


    /** @brief the function returns deltaWeight
    */
    int getDelta() const;
 private:


    int weight{};
    int deltaWeight{};
};

#endif
