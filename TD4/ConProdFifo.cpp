/**
 * @file ConProdFifo.cpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "ConProdFifo.h"
#include <iostream>


Consumer::Consumer()
{
    mCounter = 0;
}

Consumer::Consumer(Fifo<int> *fifo) : pFifo(fifo)
{
    mCounter = 0;
}

Consumer::~Consumer()
{

}

void Consumer::run()
{
    try
    {
        while(true) ///< pop elements until it's empty
        {
            pFifo->pop(1000);///< pop element every second
            mCounter++;
        }
            
    }
    catch(const Fifo<int>::EmptyException& e)
    {
        std::cerr << e.emptyException() << '\n';
    }
}

unsigned Consumer::getCounter()
{
    return mCounter;
}

Producer::Producer()
{
    mCounter=0;
}

Producer::Producer(Fifo<int> *fifo, unsigned maxCount):pFifo(fifo)
{
    mCounter=0;
    mMaxCounter=maxCount;
}

Producer::~Producer()
{

}

void Producer::run()
{
    for(int i=0; i<mMaxCounter; i++)
    {
        pFifo->push(i);
        mCounter++;
    }
}

unsigned Producer::getCounter()
{
    return mCounter;
}