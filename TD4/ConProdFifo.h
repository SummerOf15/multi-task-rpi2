/**
 * @file ConProdFifo.h
 * @author zk
 * @brief define the consumer and producer for the fifo
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CONPRODFIFO_H_INCLUDED_2021_04_04
#define CONPRODFIFO_H_INCLUDED_2021_04_04

#include "Fifo.hpp"
#include "Thread.h"
#include "Mutex.h"

class Consumer:public Thread
{
public:
    /**
     * @brief Construct a new Consumer object
     * 
     */
    Consumer();

    /**
     * @brief Construct a new Consumer object
     * 
     * @param fifo fifo object to consume
     */
    Consumer(Fifo<int> *fifo);

    /**
     * @brief Destroy the Consumer object
     * 
     */
    ~Consumer();

    /**
     * @brief remove element from fifo
     * 
     */
    void run() override;

    /**
     * @brief Get the Counter object
     * 
     * @return unsigned the number of consumed elements.
     */
    unsigned getCounter();

private:
    Fifo<int> *pFifo; ///< the fifo object to be consumed
    unsigned mCounter; ///< the number of consumed elements.

};


class Producer:public Thread
{
public:
    /**
     * @brief Construct a new Producer object
     * 
     */
    Producer();

    /**
     * @brief Construct a new Producer object
     * 
     * @param fifo Fifo object to put element
     * @param maxCount the maximum number of produced production
     */
    Producer(Fifo<int> *fifo, unsigned maxCount);

    /**
     * @brief Destroy the Producer object
     * 
     */
    ~Producer();

    /**
     * @brief produce elements and put them in the Fifo
     * 
     */
    void run();

    /**
     * @brief Get the Counter object
     * 
     * @return unsigned the number of produced elements.
     */
    unsigned getCounter();

private:
    Fifo<int> *pFifo; ///< the fifo to put elements
    unsigned mCounter; ///< the number of produced elements
    unsigned mMaxCounter; ///< the maximum number of elements to produce
};


#endif