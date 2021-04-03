/**
 * @file IncrThread.h
 * @author zk
 * @brief a thread to count numbers
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef INCRTHREAD_INCLUDED_2021_04_03
#define INCRTHREAD_INCLUDED_2021_04_03

#include "Thread.h"

class IncrThread:public Thread
{
public:
    /**
     * @brief Construct a new Incr Thread object
     * 
     */
    IncrThread();

    /**
     * @brief Construct a new Incr Thread object
     * 
     * @param loop the number of loops
     * @param &counter address of counter
     */
    IncrThread(unsigned loop, double *counter, int priority, int shedPolicy);

    /**
     * @brief Destroy the Incr Thread object
     * 
     */
    ~IncrThread();

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
    void run();

private:
    unsigned mLoop; ///< the number of loops
    double* pCounter; ///< counter
};

#endif