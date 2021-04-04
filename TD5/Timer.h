/**
 * @file Timer.h
 * @author ZHANG kai
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef TIMER_H_INCLUDED_2021_03_10
#define TIMER_H_INCLUDED_2021_03_10

#include <time.h>
#include <signal.h>

/**
 * @brief define a one-time timer
 * 
 */
class Timer
{
public:
    /**
     * @brief Construct a new Timer object
     * 
     */
    Timer();
    /**
     * @brief Destroy the Timer object
     * 
     */
    ~Timer();
    /**
     * @brief start the timer
     * 
     * @param duration_ms time interval of the timer
     */
    virtual void start(double duration_ms);
    /**
     * @brief stop the timer
     * 
     */
    void stop();

protected:
    /**
     * @brief callback function when time runs out
     * 
     */
    virtual void callback() = 0;

private:
    /**
     * @brief call callback function
     * 
     * @param si data
     */
    static void call_callback(int , siginfo_t* si, void* );

protected:
    timer_t tid; ///< timer id
    itimerspec its; ///< time
    
private:
    struct sigaction sa; ///< signal action
    struct sigevent sev; ///< signal event
};

/**
 * @brief define a periodic timer
 * 
 */
class PeriodicTimer:public Timer
{
public:
    /**
     * @brief Construct a new Periodic Timer object
     * 
     */
    PeriodicTimer():Timer(){};
    /**
     * @brief start the periodic timer
     * 
     * @param duration_ms the time interval 
     */
    virtual void start(double duration_ms);
};

/**
 * @brief count down class to count the loops
 * 
 */
class CountDown:public PeriodicTimer
{
public:
    /**
     * @brief Construct a new Count Down object
     * 
     * @param n start number
     */
    CountDown(int n);
    /**
     * @brief Get the Count object
     * 
     * @return int mCount
     */
    int getCount();
protected:
    void callback() override; ///< override function of the Timer 

private:
    int mCount; ///< number that will decrease until zero
};

#endif