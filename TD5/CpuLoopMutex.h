/**
 * @file CpuLoopMutex.h
 * @author zk
 * @brief CpuLoop with mutex
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CPULOOPMUTEX_H_INCLUDED_2021_04_04
#define CPULOOPMUTEX_H_INCLUDED_2021_04_04

#include "CpuLoop.h"
#include "Thread.h"
#include "Mutex.h"

class CpuLoopMutex:public Thread
{
public:
    /**
     * @brief Construct a new Cpu Loop Mutex object
     * 
     */
    CpuLoopMutex();

    /**
     * @brief Construct a new Cpu Loop Mutex object with specific cpuloop, schedule policy and priority and mutex.
     * 
     * @param cpuLoop cpu thread
     * @param schedPolicy schedule policy
     * @param schedPriority schedule priority
     * @param mutex mutex
     * @param startTime task start time
     * @param executiontime execution time required for this task
     * @param getMutexTime time to get mutex after starting the task
     * @param holdMutexTime time to hold the mutex 
     */
    CpuLoopMutex(CpuLoop *cpuLoop, int schedPolicy, int schedPriority, Mutex *mutex, double startTime, double executiontime, double getMutexTime, double holdMutexTime);
    
    /**
     * @brief Destroy the Cpu Loop Mutex object
     * 
     */
    ~CpuLoopMutex();

protected:
    
    /**
     * @brief callback function of this thread
     * 
     */
    void run() override;

private:
    Mutex *pMutex;
    CpuLoop *pCpuLoop;
    double startTime;
    double executionTime;
    double getMutexTime;
    double holdMutexTime;
    int priority;
};


#endif