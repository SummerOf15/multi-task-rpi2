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
void calib(double* a, double* b, vector<unsigned> samples, double samplingPeriod_ms)
{
    double s_y=0.0;
    unsigned nSamples=samples.size();
    double s_x=nSamples * (nSamples + 1) / 2 * samplingPeriod_ms;

    // calculate the sum of loop number and time
    for(unsigned i=0;i<nSamples;i++)
    {
        s_y+=samples[i];
    }

    double s_xx=nSamples * (nSamples + 1) * (2 * nSamples + 1) / 6 * samplingPeriod_ms * samplingPeriod_ms;
    double s_xy=0;
    for(unsigned i=0;i<nSamples;i++)
    {
        s_xy+=(i+1)*samplingPeriod_ms*samples[i];
    }
    
    *a = (nSamples * s_xy - s_x * s_y) / (nSamples * s_xx - s_x * s_x+1e-9);
    *b=s_y/nSamples-*a*s_x/nSamples;
}

int main()
{
    vector<unsigned> n,t;
    double a,b;
    timespec start,end;
    itimerspec its;
    
    its.it_interval.tv_sec=0; //iterate
    its.it_interval.tv_nsec=0;
    
    int numSamples=5;
    double samplePeriod=1000;
    for(int i=0;i<numSamples;i++)
    {
        cout<<"test "<<(i+1)*samplePeriod<<"ms"<<endl;
        its.it_value=timespec_from_ms((i+1)*samplePeriod);
        n.push_back(incr(its));
    }

    calib(&a,&b,n,samplePeriod);
    cout<<"a="<<a<<",b="<<b<<endl;

    its.it_value=timespec_from_ms(3000); //test using 3 s
    start=timespec_now();
    unsigned count_3=incr(its);
    end=timespec_now(); 
    double duration_3s=timespec_to_ms(end-start);
    double expectedLoops=(double)(a*duration_3s+b);
    cout<<"the expected number of loops is "<<(unsigned)expectedLoops<<endl;
    cout<<"the actual number of loops is "<<count_3<<endl;
    cout<<"the difference is "<<abs((int)count_3-(int)expectedLoops)<<endl;
    cout<<"the error is "<<(abs((int)count_3-(int)expectedLoops)*100.0)/count_3<<"%"<<endl;

    return 0;
}