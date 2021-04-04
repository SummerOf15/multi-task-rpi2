/**
 * @file main_td4a.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "IncrThread.h"
#include "Thread.h"
#include <iostream>
#include <vector>
using namespace std;



int main(int argc, char* argv[])
{
    if (argc!=3)
    {
        cout<<"only "<<argc-1<<" parameters are provided"<<endl; 
        return -1;
    }
    unsigned nLoops=atoi(argv[1]);
    unsigned nTasks=atoi(argv[2]);

    double count=0.0;

    vector<IncrThread> incrThread(nTasks);
    for(unsigned i=0;i<nTasks;i++)
    {
        int priority=rand()%99+1;
        incrThread[i]=IncrThread(nLoops,&count,priority, SCHED_RR);
        incrThread[i].start();
    }

    for(unsigned i=0;i<nTasks;i++)
    {
        incrThread[i].join();
        cout<<"thread "<<i<<" time is "<<incrThread[i].execTime_ms()<<endl;
    }
    cout<<"counter value: "<<incrThread[0].getCounter()<<endl;
    
}