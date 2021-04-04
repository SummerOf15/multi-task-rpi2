/**
 * @file Timer.cpp
 * @author zhang kai
 * @brief  Timer class including derived class PeriodTimer and CountDown
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Timer.h"
#include "TimeUtils.h"


/**
 * @brief Construct a new Timer:: Timer object
 * 
 */
Timer::Timer()
{
    sa.sa_flags=SA_SIGINFO; 
    sa.sa_sigaction=call_callback; //callback function
    sigemptyset(&sa.sa_mask); //no signal will be blocked
    sigaction(SIGRTMIN,&sa,nullptr);

    sev.sigev_notify=SIGEV_SIGNAL;
    sev.sigev_signo=SIGRTMIN;
    sev.sigev_value.sival_ptr=(void*) this; //pass the data to handler

    timer_create(CLOCK_REALTIME, &sev, &tid); // create the timer
}
/**
 * @brief Destroy the Timer:: Timer object
 * 
 */
Timer::~Timer()
{
    timer_delete(tid);
}

/**
 * @brief start a one-time timer
 * 
 * @param duration_ms time interval
 */
void Timer::start(double duration_ms)
{  
    // default setting it exoires just once
    its.it_value=timespec_from_ms(duration_ms);
    its.it_interval=timespec_from_ms(0);
    timer_settime(tid,0,&its,nullptr);
}

/**
 * @brief stop the timer
 * 
 */
void Timer::stop()
{
    its.it_value=timespec_from_ms(0);
    its.it_interval=timespec_from_ms(0);
    timer_settime(tid,0,&its,nullptr);
    return;
}

/**
 * @brief To call the callback function.
 * 
 * @param si struct siginfo which contains the parameter.
 */
void Timer::call_callback(int, siginfo_t* si, void*)
{
    Timer* pTimer=(Timer*) si->si_value.sival_ptr;
    pTimer->callback();
}

/**
 * @brief start a periodic timer
 * 
 * @param duration_ms timer interval
 */
void PeriodicTimer::start(double duration_ms)
{
    its.it_value=timespec_from_ms(duration_ms);
    its.it_interval=timespec_from_ms(duration_ms);
    timer_settime(tid,0,&its,nullptr);
}

/**
 * @brief Construct a new Count Down:: Count Down object
 * 
 * @param n a number that will decrease until zero
 */
CountDown::CountDown(int n)
{
    mCount=n;
}

/**
 * @brief start counting
 * 
 */
void CountDown::callback()
{
    mCount--;
    cout<<"timer: "<<mCount<<endl;
}

/**
 * @brief get mCount value
 * 
 * @return int mCount value
 */
int CountDown::getCount()
{
    return mCount;
}