/**
 * @file JetonThread.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "JetonThread.h"

Consumer::Consumer()
{
    mCounter=0;
}

Consumer::Consumer(Semaphore *semaphore): pSemaphore(semaphore)
{
    mCounter = 0;
}

Consumer::~Consumer()
{

}

void Consumer::run()
{
    while(pSemaphore->take(1000)) ///< take a jeton every second
    {
        mCounter++;
    }
}

unsigned Consumer::getCounter()
{
    return mCounter;
}


Producer::Producer()
{
    mCounter=0;
    mMaxCount=10000;
}

Producer::Producer(Semaphore *semaphore, unsigned maxCount): pSemaphore(semaphore)
{
    mCounter = 0;
    mMaxCount=maxCount;
}

Producer::~Producer()
{

}

void Producer::run()
{
    for(unsigned i=0;i<mMaxCount;i++)
    {
        pSemaphore->give();
        mCounter++;
    }
}

unsigned Producer::getCounter()
{
    return mCounter;
}