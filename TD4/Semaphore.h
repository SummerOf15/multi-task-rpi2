/**
 * @file Semaphore.h
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef SEMAPHORE_H_INCLUDED_2021_04_03
#define SEMAPHORE_H_INCLUDED_2021_04_03

#include "Mutex.h"
#include <climits>

class Semaphore
{
public:
    /**
     * @brief Construct a new Semaphore object
     * 
     * @param initCount init number of jetons in the Semaphore
     * @param maximumCount maximum number of jetons 
     */
    Semaphore(unsigned initCount = 0, unsigned maximumCount = UINT_MAX);
    
    /**
     * @brief add a jeton
     * 
     */
    void give();

    /**
     * @brief remove a jeton
     * 
     */
    void take();

    /**
     * @brief remove a jeton after a while
     * 
     * @param timeout_ms time
     * @return true successfully 
     * @return false failed
     */
    bool take(double timeout_ms);

private:
    volatile unsigned counter; ///< current number of jetons in this Semaphore
    unsigned maxCount; ///< maximum number of jetons 
    Mutex mMutex;
};

#endif