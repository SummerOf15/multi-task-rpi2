/**
 * @file main_td4d.cpp
 * @author ck
 * @brief test the consumer and producer in one fifo
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Fifo.hpp"
#include "ConProdFifo.h"
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

    Fifo<int> fifo;

    // maximum items to produce for each producer
    unsigned maxProdItems=1000; 
    vector<Consumer> cons(nCons, Consumer(&fifo)); ///< consumer array
    vector<Producer> prod(nProd, Producer(&fifo, maxProdItems)); ///< producer array

    // start the producer
    for(int i=0;i<nProd;i++)
    {
        prod[i].start();
    }

    // start the consumer
    for(int i=0; i<nCons; i++)
    {
        cons[i].start();
    }

    unsigned totalProduction=0;
    for(int i=0;i<nProd;i++)
    {
        prod[i].join();
        cout<<"producer "<<i<<" finished work after "<<prod[i].execTime_ms()<<"ms"<<endl;
        totalProduction+=prod[i].getCounter();
    }

    unsigned totalConsumption=0;
    for(int i=0;i<nCons;i++)
    {
        cons[i].join(); ///< pop elements until it's empty
        cout<<"consumer "<<i<<" finished work after "<<prod[i].execTime_ms()<<"ms"<<endl;
        totalConsumption+=cons[i].getCounter();
    }
    cout<<"total consumption is "<<totalConsumption<<endl;
    cout<<"total production is "<<totalProduction<<endl;
    cout<<"the difference is "<<totalProduction-totalConsumption<<endl;
    
    return 0;
}
