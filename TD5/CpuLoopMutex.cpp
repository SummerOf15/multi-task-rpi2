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


CpuLoopMutex::CpuLoopMutex(CpuLoop *cpuLoop, int schedPolicy, int schedPriority, Mutex *mutex, double startTime, double executionTime, double getMutexTime, double holdMutexTime)
{
    pMutex=mutex;
    pCpuLoop=cpuLoop;
    priority=schedPriority;
    setScheduling(schedPolicy, schedPriority);
    mStartTime=startTime;
    mExecutionTime=executionTime;
    mGetMutexTime=getMutexTime;
    mHoldMutexTime=holdMutexTime;
}

CpuLoopMutex::~CpuLoopMutex()
{

}

void CpuLoopMutex::run()
{  
    
    if(mHoldMutexTime!=-1) ///< when there is no mutex
    {
        sleep_ms(mStartTime);
        ///< wait for the start of task
        cout<< "priority "<<priority<<" starts thread"<<endl;
        pCpuLoop->runTime(mGetMutexTime); ///< run task until demande the mutex
        cout<<"priority "<<priority<<" asks for mutex"<<endl;
        Mutex::Lock lock(*pMutex, mHoldMutexTime); ///< lock mutex and unlock after holdMutexTime 
        pCpuLoop->runTime(mHoldMutexTime); ///< read and write the resource
        lock.~Lock();  ///< unlock
        cout<<"priority "<<priority<<" releases mutex"<<endl;
        pCpuLoop->runTime(mExecutionTime-mGetMutexTime-mHoldMutexTime); ///< after unlock the mutex, keep running.
        cout<<"priority "<<priority<<" terminates"<<endl;
    }
    else ///< when there is a mutex
    {
        sleep_ms(mStartTime); ///< wait for the start of task
        cout<< "priority "<<priority<<" starts thread"<<endl;
        pCpuLoop->runTime(mExecutionTime);
        cout<<"priority "<<priority<<" terminates"<<endl;
    }
}