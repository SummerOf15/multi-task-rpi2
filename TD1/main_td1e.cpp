/**
 * @file main_td1e.cpp
 * @author ZHANG kai
 * @brief multiple measures
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "TimeUtils.h"
#include <vector>

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

/**
 * @brief calculate the coefficients through multiple measurements.
 * 
 * @param a coefficients a
 * @param b coefficients b
 * @param n y vector array (the number of loops)
 * @param t x vector array (time)
 */
void calib(double* a, double* b, vector<unsigned> n, vector<unsigned> t)
{
    double s_y=0.0;
    double s_x=0.0;
    int numSamples=n.size();

    // calculate the mean value of loop number and time
    for(int i=0;i<numSamples;i++)
    {
        s_y+=n[i];
        s_x+=t[i];
    }

    double s_xx, s_xy;
    for(int i=0;i<numSamples;i++)
    {
        s_xx+=t[i]*t[i];
        s_xy+=t[i]*n[i];
    }

    *a = (numSamples * s_xy - s_x * s_y) / (numSamples * s_xx - s_x * s_x);
    *b=s_y-*a*s_x;
}

int main()
{
    vector<unsigned> n,t;
    double a,b;
    timespec start,end;
    itimerspec its;
    its.it_value.tv_nsec=0;
    its.it_interval.tv_sec=0; //iterate
    its.it_interval.tv_nsec=0;
    
    int numSamples=5;
    for(int i=0;i<numSamples;i++)
    {
        cout<<"test "<<i+1<<"s"<<endl;
        its.it_value.tv_sec=(i+1);
        start=timespec_now();
        n.push_back(incr(its));
        end=timespec_now();
        t.push_back(timespec_to_ms(end-start)/1000.0);
    }

    calib(&a,&b,n,t);
    cout<<"a="<<a<<",b="<<b<<endl;

    its.it_value.tv_sec=5; //test using 4 s
    start=timespec_now();
    unsigned count_5=incr(its);
    end=timespec_now(); 
    double duration_5s=timespec_to_ms(end-start)/1000.0;
    unsigned expectedLoops=(unsigned)(a*duration_5s+b);
    cout<<"the expected number of loops is "<<expectedLoops<<endl;
    cout<<"the actual number of loops is "<<count_5<<endl;
    cout<<"the difference is "<<count_5-expectedLoops<<endl;
    cout<<"the error is +-"<<(count_5-expectedLoops)*100.0/count_5<<"%"<<endl;

    return 0;
}