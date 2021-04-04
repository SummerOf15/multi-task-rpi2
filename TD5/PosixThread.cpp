/**
 * @file PosixThread.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "PosixThread.h"
#include "TimeUtils.h"
#include <iostream>

using namespace std;

PosixThread::PosixThread()
{
    isActive=false;
    posixId=0; ///< define default posix id
    pthread_attr_init(&posixAttr);
    pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);
    pthread_attr_setschedpolicy(&posixAttr, SCHED_OTHER); 
    sched_param schedParam;
    schedParam.sched_priority = 0;
    pthread_attr_setschedparam(&posixAttr, &schedParam);
}

PosixThread::PosixThread(pthread_t posixIdc)
{
    posixId = posixIdc; ///< set the existing thread id
    isActive = true;
    pthread_attr_init(&posixAttr);
    pthread_attr_setinheritsched(&posixAttr, PTHREAD_EXPLICIT_SCHED);
    sched_param schedParam;
    int policy;
    // get the scheduling policy and parameters of the thread thread
    int param = pthread_getschedparam(posixId, &policy, &schedParam);
    if(param == ESRCH) 
    {
        cerr << "Does not have appropriate privileges to set the specified scheduling policy and parameters.\n";
        throw PosixThread::Exception();
    }
    // assign the obtained policy and parameters
    pthread_attr_setschedpolicy(&posixAttr, policy);
    pthread_attr_setschedparam(&posixAttr, &schedParam);

}

PosixThread::~PosixThread()
{
    pthread_attr_destroy(&posixAttr);
}

void PosixThread::start(void*(*threadFunc)(void*), void* threadArg)
{
    // create a thread using the id and attribute
    pthread_create(&posixId, &posixAttr, threadFunc, threadArg);
    isActive = true;
}

void PosixThread::join()
{
    pthread_join(posixId, nullptr);
}

bool PosixThread::join(double timeout_ms)
{
    timespec t(timespec_from_ms(timeout_ms));
    // On success, return 0; on error, return an error number.
    bool isTerminated=(bool) pthread_timedjoin_np(posixId, NULL, &t);
    return ! isTerminated;
}

bool PosixThread::setScheduling(int schedPolicy, int priority)
{
   
    sched_param schedParam;
    schedParam.sched_priority = priority; 
    if(isActive)
    {
        pthread_setschedparam(posixId, schedPolicy, &schedParam);
        return true;
    }
    else
    {
        pthread_attr_setschedpolicy(&posixAttr, schedPolicy);
        pthread_attr_setschedparam(&posixAttr, &schedParam);
        return false;
    }
}

bool PosixThread::getScheduling(int* pSchedPolicy, int* pPriority)
{
    sched_param schedParam;
    if(isActive)
    {
        pthread_getschedparam(posixId, pSchedPolicy, &schedParam);
        *pPriority = schedParam.sched_priority;
        return true;
    }
    else
    {
        pthread_attr_getschedpolicy(&posixAttr, pSchedPolicy);
        pthread_attr_getschedparam(&posixAttr, &schedParam);
        *pPriority = schedParam.sched_priority;
        return false;
    }
}