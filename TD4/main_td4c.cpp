/**
 * @file main_td4c.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "TimeUtils.h"
#include "Semaphore.h"
#include "JetonThread.h"
#include <vector>
#include <iostream>


int main(int argc, char* argv[])
{
    if (argc!=3)
    {
        cout<<"2 parameters are expected but only get "<<argc-1<<endl; 
        return -1;
    }
    // input the number of consumers and producers
    unsigned nCons=atoi(argv[1]);
    unsigned nProd=atoi(argv[2]);

    unsigned initCount=0; ///< init number of jetons in semaphore
    unsigned maxCount=1000; ///< maximum number of jetons can be stored in a semaphore
    Semaphore s(initCount, maxCount);

    vector<Consumer> cons(nCons, Consumer(&s)); ///< consumer array
    vector<Producer> prod(nProd, Producer(&s, maxCount)); ///< producer array

    for(unsigned i=0;i<nProd;i++)
    {
        prod[i].start();
    }

    for(unsigned i=0; i<nCons; i++)
    {
        cons[i].start();
    }

    unsigned totalProduction=0;
    for(unsigned i=0;i<nProd;i++)
    {
        prod[i].join();
        cout<<"producer "<<i<<" finished work after "<<prod[i].execTime_ms()<<"ms"<<endl;
        totalProduction+=prod[i].getCounter();
    }

    unsigned totalConsumption=0;
    for(unsigned i=0;i<nCons;i++)
    {
        cons[i].join();
        cout<<"consumer "<<i<<" finished work after "<<prod[i].execTime_ms()<<"ms"<<endl;
        totalConsumption+=cons[i].getCounter();
    }
    cout<<"total consumption is "<<totalConsumption<<endl;
    cout<<"total production is "<<totalProduction<<endl;
    cout<<"the difference is "<<totalProduction-totalConsumption<<endl;
    
    return 0;
}