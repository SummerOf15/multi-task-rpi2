/**
 * @file IncrMutex.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "IncrMutex.h"


IncrMutex::IncrMutex(unsigned loop, double *counter, int priority, int schedPolicy, Mutex *mutex) : Thread()
{
    mLoop=loop;
    pCounter=counter;
    pMutex=mutex;

    setScheduling(schedPolicy, priority);
}

IncrMutex::IncrMutex()
{

}

IncrMutex::~IncrMutex()
{

}

void IncrMutex::run()
{
    Mutex::Lock lock(*pMutex);

    for(unsigned i=0; i < mLoop; i++)
    {
        *pCounter += 1.0;
    }
}

double IncrMutex::getCounter()
{
    return *pCounter;
}