/**
 * @file JetonThread.h
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef JETONTHREAD_H_INCLUDED_2021_04_03
#define JETONTHREAD_H_INCLUDED_2021_04_03

#include "Thread.h"
#include "Semaphore.h"

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
     * @param semaphore semaphore to take jeton
     */
    Consumer(Semaphore *semaphore);

    /**
     * @brief Destroy the Consumer object
     * 
     */
    ~Consumer();

    /**
     * @brief Get the Counter object
     * 
     * @return unsigned mCounter
     */
    unsigned getCounter();

protected:
    /**
     * @brief callback function of this thread
     * 
     */
    void run() override;

private:
    Semaphore *pSemaphore; ///< semaphore to take jetons
    unsigned mCounter; ///< number of jetons that have been taken

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
     * @param semaphore semaphore to take jeton
     * @param maxCount maximum number of jetons to produce
     */
    Producer(Semaphore *semaphore, unsigned maxCount);

    /**
     * @brief Destroy the Producer object
     * 
     */
    ~Producer();

    /**
     * @brief Get the Counter object
     * 
     * @return unsigned mCounter
     */
    unsigned getCounter();

protected:
    /**
     * @brief callback function of this thread
     * 
     */
    void run() override;

private:
    Semaphore *pSemaphore; ///< semaphore to give jetons
    unsigned mCounter; ///< number of jetons that have been produced
    unsigned mMaxCount; ///< maximum number of jetons can be produced
};

#endif