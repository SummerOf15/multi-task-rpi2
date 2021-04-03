/**
 * @file IncrThread.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "IncrThread.h"
#include <iostream>

IncrThread::IncrThread()
{

}

IncrThread::IncrThread(unsigned loop, double *counter, int priority, int shedPolicy):Thread()
{
    mLoop=loop;
    pCounter=counter;
    setScheduling(shedPolicy,priority);
}

IncrThread::~IncrThread()
{

}

void IncrThread::run()
{
    for(int i=0;i<mLoop;i++)
    {
        *pCounter+=1,0;
    }
}

double IncrThread::getCounter()
{
    return *pCounter;
}