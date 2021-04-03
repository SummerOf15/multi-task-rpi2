/**
 * @file Thread.h
 * @author zk
 * @brief thread class
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef THREAD_H_INCLUDED_2021_04_03
#define THREAD_H_INCLUDED_2021_04_03

#include "PosixThread.h"
#include "Chrono.h"

class Thread:public PosixThread
{
public:
    /**
     * @brief Construct a new Thread object
     * 
     */
    Thread();

    /**
     * @brief Destroy the Thread object
     * 
     */
    ~Thread();

    /**
     * @brief start the thread
     * 
     * @return true start successfully
     * @return false already started
     */
    bool start();

protected:
    /**
     * @brief A pure virtual function defines the activity of the thread
     * 
     */
    virtual void run()=0;

private:
    /**
     * @brief call run function
     * 
     * @param v_thread thread pointer
     * @return void* 
     */
    static void * call_run(void* v_thread);

public:
    /**
     * @brief sleep for a while
     * 
     * @param delay_ms time to sleep
     */
    static void sleep_ms(double delay_ms);

    /**
     * @brief get start time
     * 
     * @return double start time (ms)
     */
    double startTime_ms();

    /**
     * @brief get stop time
     * 
     * @return double stop time (ms)
     */
    double stopTime_ms();

    /**
     * @brief get execution time
     * 
     * @return double execution time (ms)
     */
    double execTime_ms();

private:
    bool started; ///< flag to show if the thread is active
    Chrono mChrono; ///< a chronometer
};

#endif