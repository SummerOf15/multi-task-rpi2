/**
 * @file main_td4b.cpp
 * @author zk and cy
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <iostream>
#include <pthread.h>
#include <vector>
#include "TimeUtils.h"
#include "IncrMutex.h"

using namespace std;



int main(int argc, char* argv[])
{
    if (argc!=3)
    {
        cout<<"2 parameters are expected but only get "<<argc-1<<endl; 
        return -1;
    }
    unsigned nLoops=atoi(argv[1]);
    unsigned nTasks=atoi(argv[2]);

    double counter = 0.0;
    Mutex mutex;

    vector<IncrMutex> incrThread(nTasks);
    for(int i=0;i<nTasks;i++)
    {
        int priority=rand()%99+1;
        incrThread[i]=IncrMutex(nLoops,&counter,priority, SCHED_RR, &mutex);
        incrThread[i].start();
    }

    for(int i=0;i<nTasks;i++)
    {
        incrThread[i].join();
        cout<<"thread "<<i<<" time is "<<incrThread[i].execTime_ms()<<endl;
    }
    cout<<"counter value: "<<incrThread[0].getCounter()<<endl;
}
