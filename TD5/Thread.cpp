/**
 * @file Thread.cpp
 * @author zk
 * @brief Thread functions
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Thread.h"
#include "TimeUtils.h"

Thread::Thread()
{
    started=false;
    mChrono=Chrono();
}

Thread::~Thread()
{

}

bool Thread::start()
{
    if(!started)
    {
        started = true;
        
        PosixThread::start(call_run, (void*)this);
    }
    return started;
}

void* Thread::call_run(void* v_thread)
{
    Thread* thread = (Thread*) v_thread;
    thread->mChrono.restart();
	thread->run();
    thread->mChrono.stop();
    thread->started = false;
    return (void*) thread;
}

void Thread::sleep_ms(double delay_ms)
{
    timespec_wait(timespec_from_ms(delay_ms));
}

double Thread::startTime_ms()
{
    return mChrono.startTime();
}

double Thread::stopTime_ms()
{
    return mChrono.stopTime();
}

double Thread::execTime_ms()
{
    return mChrono.lap();
}