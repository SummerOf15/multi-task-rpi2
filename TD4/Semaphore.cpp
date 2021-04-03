/**
 * @file Semaphore.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Semaphore.h"
#include "TimeUtils.h"


Semaphore::Semaphore(unsigned initCount, unsigned maximumCount)
{
    counter = initCount;
	maxCount = maximumCount;
}

void Semaphore::give()
{
    Mutex::Lock lock(mMutex); ///< lock the number
    while(counter > maxCount)
    {
        lock.wait();
    }
    counter++;
    lock.notify();
}

void Semaphore::take()
{
    Mutex::Lock lock(mMutex);
    while(counter == 0)
    {
        lock.wait();
    }
    counter--;
    lock.notify(); ///< unlock the number
}

bool Semaphore::take(double timeout_ms)
{
    Mutex::Lock lock(mMutex);
    if(counter == 0)
    {
        lock.wait(timeout_ms);
    }
    if(counter == 0) ///< after timeout_ms, there is still no jeton
    {
        return false;
    }
    counter--;
    lock.notify(); ///< unlock the number
    return true;
}