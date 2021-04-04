#include "TimeUtils.h"


double timespec_to_ms(const timespec& time_ts)
{
    double time_ms=time_ts.tv_sec*1000+time_ts.tv_nsec*1e-6;
    return time_ms;
}

timespec timespec_from_ms(double time_ms)
{
    timespec time_ts;
    time_ts.tv_sec=(int)(time_ms/1000);
    time_ts.tv_nsec=(time_ms-time_ts.tv_sec*1000)*1e6;
    return time_ts;
}

timespec timespec_now()
{
    timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now;
}

timespec timespec_negate(const timespec& time_ts)
{
    timespec result;
    result.tv_sec=-time_ts.tv_sec+1;
    result.tv_nsec=1e9-time_ts.tv_nsec;
    return result;
}

timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts)
{
    timespec result;
    result.tv_sec=time1_ts.tv_sec+time2_ts.tv_sec;
    result.tv_nsec=time1_ts.tv_nsec+time2_ts.tv_nsec;
    if (result.tv_nsec>1e9)
    {
        result.tv_nsec-=1e9;
        result.tv_sec+=1;
    }
    return result;
}

timespec timespec_substract(const timespec& time1_ts, const timespec& time2_ts)
{
    timespec result;
    result.tv_sec=time1_ts.tv_sec-time2_ts.tv_sec;
    result.tv_nsec=time1_ts.tv_nsec-time2_ts.tv_nsec;
    if (result.tv_nsec<0)
    {
        result.tv_nsec+=1e9;
        result.tv_sec-=1;
    }
    return result;
}

timespec timespec_wait(const timespec& delay_ts)
{
    timespec rem;
    if(nanosleep(&delay_ts, &rem)<0)
    {
        cout<<"error"<<endl;
    }
    else
    {
        cout<<"successful"<<endl;
    }

    return rem;
}

timespec operator- (const timespec& time_ts)
{
    return timespec_negate(time_ts);
}

timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts)
{
    return timespec_add(time1_ts,time2_ts);
}

timespec  operator- (const timespec& time1_ts, const timespec& time2_ts)
{
    return timespec_substract(time1_ts,time2_ts);
}

timespec& operator+= (timespec& time_ts, const timespec& delay_ts)
{
    time_ts=timespec_add(time_ts,delay_ts);
    return time_ts;
}

timespec& operator-= (timespec& time_ts, const timespec& delay_ts)
{
    time_ts=timespec_substract(time_ts,delay_ts);
    return time_ts;
}

bool operator== (const timespec& time1_ts, const timespec& time2_ts)
{
    if(time1_ts.tv_nsec==time2_ts.tv_nsec && time1_ts.tv_sec==time1_ts.tv_sec)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator!= (const timespec& time1_ts, const timespec& time2_ts)
{
    if(time1_ts.tv_nsec==time2_ts.tv_nsec && time1_ts.tv_sec==time1_ts.tv_sec)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool operator< (const timespec& time1_ts, const timespec& time2_ts)
{
    if(time1_ts.tv_sec<time2_ts.tv_sec)
    {
        return true;
    }
    else if(time1_ts.tv_sec==time2_ts.tv_sec && time1_ts.tv_nsec<time2_ts.tv_nsec)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool operator> (const timespec& time1_ts, const timespec& time2_ts)
{
    if(time1_ts.tv_sec>time2_ts.tv_sec)
    {
        return true;
    }
    else if (time1_ts.tv_sec==time2_ts.tv_sec && time1_ts.tv_nsec>time2_ts.tv_nsec)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void handler(int , siginfo_t* si, void* )
{
    double* p_counter=static_cast<double*>(si->si_value.sival_ptr);
    *p_counter+=1.0;
    cout<<*p_counter<<endl;
}

void generate_timer(int hz, int iteration, double* pCounter)
{
    struct sigaction sa; //action when the timer pauses
    sa.sa_flags=SA_SIGINFO; //
    sa.sa_sigaction=handler; //callback function
    sigemptyset(&sa.sa_mask); //no signal will be blocked
    sigaction(SIGRTMIN,&sa,nullptr);

    struct sigevent sev;
    sev.sigev_notify=SIGEV_SIGNAL;
    sev.sigev_signo=SIGRTMIN;
    sev.sigev_value.sival_ptr=(void*) pCounter; //pass the data to handler

    timer_t tid;
    timer_create(CLOCK_REALTIME, &sev, &tid); // create the timer
    
    itimerspec its;
    its.it_value=timespec_from_ms(1.0/hz*1000);
    its.it_interval=timespec_from_ms(1.0/hz*1000);
    timer_settime(tid,0,&its,nullptr);

    while(1)
    {
        if(*pCounter>=iteration)
        {
            break;
        }
        continue;
    }
    timer_delete(tid);
}

void incr(unsigned int nLoops, double* pCounter)
{
    for(int i=0;i<nLoops;i++)
    {
        *pCounter+=1,0;
    }
}


unsigned incr(unsigned int nLoops, double* pCounter, bool* pStop)
{
    unsigned realLoops = 0;
    for(unsigned int iLoop=0; iLoop < nLoops; ++iLoop)
    {
        if(*pStop) break;
        *pCounter += 1.0;
        realLoops += 1; 
    }
    return realLoops;
}

void calib(double* a, double* b, double n1, double n2, double t1, double t2)
{
    *a=(n1-n2)/(t1-t2+1e-9); // in case that t1=t2
    *b=(n1-*a*t1);
}