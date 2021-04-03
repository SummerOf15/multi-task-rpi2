/**
 * @file IncrMutex.h
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef INCRMUTEX_H_INCLUDED_2021_04_03
#define INCRMUTEX_H_INCLUDED_2021_04_03

#include "Mutex.h"
#include "Thread.h"

class IncrMutex:public Thread
{
public:
    /**
     * @brief Construct a new Incr Thread object
     * 
     */
    IncrMutex();

    /**
     * @brief Construct a new Incr Mutex object
     * 
     * @param loop loop number
     * @param counter 
     * @param priority priority of the thread
     * @param schedPolicy schedule policy
     * @param mutex mutex
     */
    IncrMutex(unsigned loop, double *counter, int priority, int schedPolicy, Mutex *mutex);

    /**
     * @brief Destroy the Incr Thread object
     * 
     */
    ~IncrMutex();

    /**
     * @brief Get the Counter object
     * 
     * @return double counter value
     */
    double getCounter();

protected:
    /**
     * @brief increase the counter
     * 
     */
    void run() override;

private:
    unsigned mLoop; ///< the number of loops
    volatile double* pCounter; ///< counter
    Mutex *pMutex; ///< mutex
};

#endif