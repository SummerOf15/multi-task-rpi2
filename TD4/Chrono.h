/**
 * @file Chrono.h
 * @author ZHANG kai
 * @brief Chrono header file includes different functions about Chrono
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#ifndef CHRONO_H_INCLUDED_2021_03_10
#define CHRONO_H_INCLUDED_2021_03_10

#include <time.h>

class Chrono
{
public:
    /**
     * @brief Construct a new Chrono object
     * 
     */
    Chrono();
    /**
     * @brief Destroy the Chrono object
     * 
     */
    ~Chrono();

    /**
     * @brief stop the thread
     * 
     */
    void stop();
    /**
     * @brief restart the thread
     * 
     */
    void restart();
    /**
     * @brief judge whether it's active
     * 
     * @return true active
     * @return false inactive
     */
    bool isActive();
    /**
     * @brief get start time
     * 
     * @return double start time
     */
    double startTime();
    /**
     * @brief get stop time
     * 
     * @return double stop time
     */
    double stopTime();
    /**
     * @brief running time
     * 
     * @return double running time. The maximum time is stopTime-startTime
     */
    double lap();

private:
    timespec m_startTime; ///< start time
    timespec m_stopTime;  ///< stop time

};

#endif