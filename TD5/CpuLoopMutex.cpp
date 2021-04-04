/**
 * @file CpuLoopMutex.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "CpuLoopMutex.h"
#include "TimeUtils.h"


CpuLoopMutex::CpuLoopMutex()
{

}

CpuLoopMutex::CpuLoopMutex(CpuLoop *cpuLoop, int schedPolicy, int schedPriority, Mutex *mutex, double startTime, double executionTime, double getMutexTime, double holdMutexTime)
{
    pMutex=mutex;
    pCpuLoop=cpuLoop;
    priority=schedPriority;
    setScheduling(schedPolicy, schedPriority);
    startTime=startTime;
    executionTime=executionTime;
    getMutexTime=getMutexTime;
    holdMutexTime=holdMutexTime;
}

CpuLoopMutex::~CpuLoopMutex()
{

}

void CpuLoopMutex::run()
{  
    sleep_ms(startTime);
    if(holdMutexTime!=-1) ///< when there is no mutex
    {
        ///< wait for the start of task
        cout<< "priority "<<priority<<" starts thread"<<endl;
        pCpuLoop->runTime(getMutexTime); ///< run task until demande the mutex
        cout<<"priority "<<priority<<" asks for mutex"<<endl;
        Mutex::Lock lock(*pMutex, holdMutexTime); ///< lock mutex and unlock after holdMutexTime 
        pCpuLoop->runTime(holdMutexTime); ///< read and write the resource
        lock.~Lock();  ///< unlock
        cout<<"priority "<<priority<<" releases mutex"<<endl;
        pCpuLoop->runTime(executionTime-getMutexTime-holdMutexTime); ///< after unlock the mutex, keep running.
        cout<<"priority "<<priority<<" terminates"<<endl;
    }
    else ///< when there is a mutex
    {
        sleep_ms(startTime); ///< wait for the start of task
        cout<< "priority "<<priority<<" starts thread"<<endl;
        pCpuLoop->runTime(executionTime);
        cout<<"priority "<<priority<<" terminates"<<endl;
    }
}