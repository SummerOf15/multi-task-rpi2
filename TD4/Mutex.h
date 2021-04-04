/**
 * @file Mutex.h
 * @author zk and cy
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef MUTEX_H_INCLUDED_2021_04_03
#define MUTEX_H_INCLUDED_2021_04_03

#include <pthread.h>
#include <exception>

class Mutex
{
public:
    /**
     * @brief Construct a new Mutex object
     * 
     */
    Mutex();

    /**
     * @brief Destroy the Mutex object
     * 
     */
    ~Mutex();

private:
    /**
     * @brief lock the mutex
     * 
     */
    void lock();

    /**
     * @brief lock the mutex for a while
     * 
     * @param timeout_ms time to lock
     * @return true successfully
     * @return false failed
     */
    bool lock(double timeout_ms);

    /**
     * @brief try to lock the mutex
     * 
     * @return true successfully
     * @return false failed
     */
    bool trylock();

    /**
     * @brief unlock the mutex
     * 
     */
    void unlock();

public:
    /**
     * @brief class to lock the mutex
     * 
     */
    class Lock;
    /**
     * @brief class to try lock the mutex
     * 
     */
    class TryLock;
    /**
     * @brief class to monitor the mutex
     * 
     */
    class Monitor;

private:
    pthread_mutex_t posixId;  ///< mutex id
    pthread_cond_t posixCondId; ///< mutex condition id

};


class Mutex:: Monitor
{
protected:
    /**
     * @brief Construct a new Monitor object
     * 
     * @param m mutex
     */
    Monitor(Mutex &m);

public:
    /**
     * @brief wait until condition is satisfied
     * 
     */
    void wait();

    /**
     * @brief wait for a while
     * 
     * @param timeout_ms time to wait
     * @return true successfully
     * @return false failed
     */
    bool wait(double timeout_ms);

    /**
     * @brief unblock threads blocked on a condition variable
     * 
     */
    void notify();

    /**
     * @brief unblock all threads blocked on a condition variable
     * 
     */
    void notifyAll();

public:
    Mutex &mMutex; ///< mutex
    class TimeoutException : std::exception
    {
        public:
            const char* launchingException() const noexcept;
    };
};


class Mutex::Lock : public Monitor
{
public:
    /**
     * @brief Construct a new Lock object
     * 
     * @param m mutex m
     */
    Lock(Mutex &m);

    /**
     * @brief Construct a new Lock object
     * 
     * @param m mutex
     * @param timeout_ms time
     */
    Lock(Mutex &m, double timeout_ms);

    /**
     * @brief Destroy the Lock object
     * 
     */
    ~Lock();
};


class Mutex::TryLock : public Monitor
{
public:
    /**
     * @brief Construct a new Try Lock object
     * 
     * @param m mutex m
     */
    TryLock(Mutex &m);

    /**
     * @brief Destroy the Try Lock object
     * 
     */
    ~TryLock();
};


#endif