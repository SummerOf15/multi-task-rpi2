/**
 * @file main_td1d.cpp
 * @author ZHANG kai
 * @brief 
 * @version 0.1
 * @date 2021-04-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "TimeUtils.h"
#include <iostream>

/**
 * @brief timer callback function, to set stop flag as true when time runs out
 * 
 * @param si siginfo
 */
void incr_handler(int , siginfo_t* si, void* )
{
    bool* pStop=(bool*)(si->si_value.sival_ptr);
    *pStop=true;
}


/**
 * @brief generate a timer with time parameter
 * 
 * @param its time interval of the timer
 * @return unsigned The number of loops it runs when it stops
 */
unsigned incr(itimerspec its)
{
    bool stop=false;
    double counter=0.0;
    unsigned int nLoops=UINT32_MAX;
    struct sigaction sa; //action when the timer pauses
    sa.sa_flags=SA_SIGINFO; //
    sa.sa_sigaction=incr_handler; //callback function
    sigemptyset(&sa.sa_mask); //no signal will be blocked
    sigaction(SIGRTMIN,&sa,nullptr);

    struct sigevent sev;
    sev.sigev_notify=SIGEV_SIGNAL;
    sev.sigev_signo=SIGRTMIN;
    sev.sigev_value.sival_ptr=(void*) &stop; //pass the data to handler

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid); // create the timer
    timer_settime(tid,0,&its,nullptr);

    unsigned realCount = incr(nLoops,&counter,&stop);
    timer_delete(tid);
    return realCount;
}


int main()
{
    timespec start,end;
    double duration_4s, duration_6s, duration_5s;
    // 4s
    itimerspec its;
    its.it_value.tv_sec=4; // set 4 second
    its.it_value.tv_nsec=0;
    its.it_interval.tv_sec=0; //iterate
    its.it_interval.tv_nsec=0;
    start=timespec_now();
    unsigned count_4=incr(its);
    end=timespec_now();
    duration_4s=timespec_to_ms(end-start)/1000.0;

    // 6s
    its.it_value.tv_sec=6; // set 1 second
    its.it_value.tv_nsec=0;
    its.it_interval.tv_sec=0; //iterate
    its.it_interval.tv_nsec=0;
    start=timespec_now();
    unsigned count_6=incr(its);
    end=timespec_now();
    duration_6s=timespec_to_ms(end-start)/1000.0;

    // calibrate
    double a,b;
    calib(&a,&b,count_4,count_6,duration_4s,duration_6s);
    cout<<"a="<<a<<",b="<<b<<endl;

    // verify by 5s
    its.it_value=timespec_from_ms(5000);
    start=timespec_now();
    unsigned count_5=incr(its);
    end=timespec_now();
    duration_5s=timespec_to_ms(end-start)/1000.0;

    unsigned expectedLoops=(unsigned)(a*duration_5s+b);
    cout<<"the expected number of loops is "<<expectedLoops<<endl;
    cout<<"the actual number of loops is "<<count_5<<endl;
    cout<<"the difference is "<<abs((int)count_5-(int)expectedLoops)<<endl;
    cout<<"the error is "<<abs((int)count_5-(int)expectedLoops)*100.0/count_5<<"%"<<endl;
    return 0;
}