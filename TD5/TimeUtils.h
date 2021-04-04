/**
 * @file TimeUtils.h
 * @author ZHANG kai
 * @brief a tool file for timespec operation
 * @version 0.1
 * @date 2021-04-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef TimeUtils_h_INCLUDED
#define TimeUtils_h_INCLUDED

#include <time.h>
#include <iostream>
#include <unistd.h>
#include <signal.h>
using namespace std;


/**
 * @brief convert from timespec to ms
 * 
 * @param time_ts timespec data to convert
 * @return double convertion result in ms unit
 */
double timespec_to_ms(const timespec& time_ts);

/**
 * @brief convert from ms to timespec
 * 
 * @param time_ms ms data to convert
 * @return timespec  convertion result in timespec format.
 */
timespec timespec_from_ms(double time_ms);

/**
 * @brief obtain current time
 * 
 * @return timespec current time in timespec format
 */
timespec timespec_now();

/**
 * @brief opposite time
 * 
 * @param time_ts input time
 * @return timespec output opposite time
 */
timespec timespec_negate(const timespec& time_ts);

/**
 * @brief add two timespec data
 * 
 * @param time1_ts data 1
 * @param time2_ts data 2
 * @return timespec add result
 */
timespec timespec_add(const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief substract two timespec data
 * 
 * @param time1_ts left number
 * @param time2_ts right number
 * @return timespec substraction result
 */
timespec timespec_substract(const timespec& time1_ts, const timespec& time2_ts);

/**
 * @brief wait for several time
 * 
 * @param delay_ts the duration of waiting
 * @return timespec new time after waiting
 */
timespec timespec_wait(const timespec& delay_ts);

// timespec operators
/**
 * @brief operation negative
 * 
 * @param time_ts input data
 * @return timespec output result
 */
timespec operator- (const timespec& time_ts);
/**
 * @brief add operation +
 * 
 * @param time1_ts data 1
 * @param time2_ts data 2
 * @return timespec add result
 */
timespec  operator+ (const timespec& time1_ts, const timespec& time2_ts);
/**
 * @brief substraction operation -
 * 
 * @param time1_ts data 1
 * @param time2_ts data 2
 * @return timespec results
 */
timespec  operator- (const timespec& time1_ts, const timespec& time2_ts);
/**
 * @brief add a delay in time_ts
 * 
 * @param time_ts to be added
 * @param delay_ts duration
 * @return timespec& the address of time_ts
 */
timespec& operator+= (timespec& time_ts, const timespec& delay_ts);
/**
 * @brief substract a delay in time_ts
 * 
 * @param time_ts to be substracted
 * @param delay_ts duration
 * @return timespec& the address of time_ts
 */
timespec& operator-= (timespec& time_ts, const timespec& delay_ts);
/**
 * @brief judge whether two timespec are equal
 * 
 * @param time1_ts time 1
 * @param time2_ts time 2
 * @return true time1==time2
 * @return false time1!=time2
 */
bool operator== (const timespec& time1_ts, const timespec& time2_ts);
/**
 * @brief judge whether two timespec are not equal
 * 
 * @param time1_ts time 1
 * @param time2_ts time 2
 * @return true time1 is not equal to time2
 * @return false time1 is equal to time2
 */
bool operator!= (const timespec& time1_ts, const timespec& time2_ts);
/**
 * @brief judge whether time1_ts is less than time2_ts
 * 
 * @param time1_ts time 1
 * @param time2_ts time 2
 * @return true time1_ts is less than time2_ts
 * @return false time1_ts is greater than time2_ts
 */
bool operator< (const timespec& time1_ts, const timespec& time2_ts);
/**
 * @brief judge whether time1_ts is greater than time2_ts
 * 
 * @param time1_ts time 1
 * @param time2_ts time 2
 * @return true time1_ts is greater than time2_ts
 * @return false time1_ts is less than time2_ts
 */
bool operator> (const timespec& time1_ts, const timespec& time2_ts);

// timer
/**
 * @brief generate a timer
 * 
 * @param hz frequence of the timer
 * @param iteration number of iterations of counting
 * @param pCounter a count number that increases in each interval
 */
void generate_timer(int hz, int iteration,double* pCounter);

// increment loop
/**
 * @brief run nLoops and increase pCounter
 * 
 * @param nLoops number of running loops
 * @param pCounter count number
 */
void incr(unsigned int nLoops, double* pCounter);
/**
 * @brief incr function with stop flag
 * 
 * @param nLoops number of loops
 * @param pCounter counter variable
 * @param pStop stop flag. True->stop
 * @return unsigned count number when it stops
 */
unsigned incr(unsigned int nLoops, double* pCounter, bool* pStop);

/**
 * @brief calculate the a and b in function l=at+b
 * 
 * @param a coefficients
 * @param b coefficients
 * @param n1 number of loops
 * @param n2 number of loops
 * @param t1 time for n1 loops
 * @param t2 time for n2 loops
 */
void calib(double* a, double* b, double n1, double n2, double t1, double t2);
#endif