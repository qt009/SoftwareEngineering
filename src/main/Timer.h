//@(#) Timer.h

#ifndef TIMER_H_H
#define TIMER_H_H

#include <chrono>
using namespace std::chrono;
#include <iostream>


/**
 * @class Timer
 *
 * @brief Timer manages time on interval device
 *
 */
class Timer {
 public:

    /** @brief boosts booster to turbo
    */
    void setTurbo(int turbo);

    /** @brief returns the current instance information
    */
    static Timer * getInstance();

    /**
     * 	~Timer( )
     *     {
     *         instanceFlag = false;
     *     };
     */

    /** @brief to improve compatibility between Linux and Windows this implementation
    */
    void sleepInIntervals(long milliSeconds) const;

    /** @brief if netbeans does not recognize system_clock you have to set the project properties to C++11
    */
     void sleep(long delayInMs) const;


 private:
    /**
   * This value shows the actual instance
   */
    static bool instanceFlag;

    /**
    * This value shows the time
    */
    static Timer * theTimer;

    /**
   *  booster
   */
    int booster;

    /**
   *  @brief Timer constructor assings 1 to the booster
   */
    Timer() : booster(1) {
    };

};

#endif
