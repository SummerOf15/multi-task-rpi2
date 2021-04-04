/**
 * @file main_td5.cpp
 * @author zk
 * @brief test safe of inverse priority 
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "Thread.h"
#include "CpuLoopMutex.h"
#include "TimeUtils.h"
#include <iostream>

int main()
{
    cpu_set_t  cpuset; ///< a set of CPU
    CPU_ZERO(&cpuset); ///< Clears set, so that it contains no CPUs.
    CPU_SET(0, &cpuset); ///< assign an id to cpuset 
    sched_setaffinity(0, sizeof(cpu_set_t), &cpuset); ///<If pid is zero, then the calling thread is used

    //defining mutex with control on the inversion
    Mutex mutex(1);	

    //setting policy and priority
    int policy = SCHED_RR;
    // set priorityA > priorityB > priorityC
    int priorityA = 33;
    int priorityB = 22;
    int priorityC = 11;

    Calibrator calibrator(100,20); ///< 1 hz 5 samples
    CpuLoop loopA(calibrator);
    CpuLoop loopB(calibrator);
    CpuLoop loopC(calibrator);

    //create thread, assume each time unit is 100ms
    // A starts at t=30, demande the mutex 10 units later, release the mutex 10 later, the total execute time is 40 units,
    CpuLoopMutex threadA(&loopA, policy, priorityA, &mutex, 3000.0, 4000.0, 1000.0, 1000.0);
    CpuLoopMutex threadB(&loopB, policy, priorityB, &mutex, 3000, 1000, -1, -1); ///< no mutex
    CpuLoopMutex threadC(&loopC, policy, priorityC, &mutex, 0, 5000, 2000, 2000);
    
    Chrono chrono;
    
    threadA.start();
    threadB.start();
    threadC.start();

    threadA.join();
    threadB.join();
    threadC.join();

    chrono.stop();
    // Measure the total running time.
    

    cout<<"total running time "<<chrono.lap()<<"ms"<<endl;
    cout<<"thread A took "<<threadA.execTime_ms()<<"ms"<<endl;
    cout<<"thread B took "<<threadB.execTime_ms()<<"ms"<<endl;
    cout<<"thread C took "<<threadC.execTime_ms()<<"ms"<<endl;
    return 0;
}