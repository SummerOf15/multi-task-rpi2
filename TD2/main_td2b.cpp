/**
 * @file main_td2b.cpp
 * @author ZHANG kai
 * @brief measure execution time
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "TimeUtils.h"
#include <pthread.h>
#include <iostream>
#include <vector>
using namespace std;


/**
 * @brief thread data structure
 * 
 */
struct Data{
    unsigned loop; ///< the number of loops
    double counter;///< counter
};


/**
 * @brief callback function
 * 
 * @param v_data input data
 * @return void* 
 */
void* call_incr(void* v_data)
{
    Data* pData=(Data*) v_data;
    incr(pData->loop, &(pData->counter));
    return v_data;
}


int main(int argc, char* argv[])
{
    if(argc!=4)
    {
        cerr<<"only "<<argc-1<<" but expect 3 parameters are provided"<<endl; 
        return -1;
    }
    unsigned nLoops=atoi(argv[1]);
    unsigned nTasks=atoi(argv[2]);
    string sched=argv[3];
    int schedPolicy;

    if (sched.compare("SCHED_RR")==0)
    {
        schedPolicy=SCHED_RR;
    }
    else if (sched.compare("SCHED_FIFO")==0)
    {
        schedPolicy=SCHED_FIFO;
    }
    else if(sched.compare("SCHED_OTHER")==0)
    {
        schedPolicy=SCHED_OTHER;
    }
    else
    {
        cerr<<"unknown sched policy"<<endl;
        return -1;
    }

    // set main function with the highest priority 
    struct sched_param schedParamMain;
    schedParamMain.sched_priority = sched_get_priority_max(schedPolicy);
    pthread_setschedparam(pthread_self(), schedPolicy, &schedParamMain);

    // sched parameters of the thread
    sched_param schedParamThread;
    pthread_attr_t attr;

    int priority = rand()%99 + 1;
    schedParamThread.sched_priority = (schedPolicy == SCHED_OTHER) ? 0 : priority;

    pthread_attr_init(&attr);
    pthread_attr_setinheritsched(&attr, schedPolicy);
    pthread_attr_setschedparam(&attr, &schedParamThread);

    Data data;
    data.counter=0.0;
    data.loop=nLoops;

    vector<pthread_t> incrThread(nTasks);

    timespec start, end;
    start=timespec_now();
    for(unsigned i=0;i<nTasks;i++)
    {
        
        pthread_create(&incrThread[i], &attr, call_incr, &data);
    }

    pthread_attr_destroy(&attr);

    for(unsigned i=0;i<nTasks;i++)
    {
        pthread_join(incrThread[i], nullptr);
    }
    end=timespec_now();
    cout<<"counter value: "<<data.counter<<endl;
    cout<<"duration: "<<timespec_to_ms(end-start)<<"ms"<<endl;
    return 0;
}