/**
 * @file Calibrator.h
 * @author ZHANG kai
 * @brief Calibrator class for estimating the number of loops executed during certain time interval
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CALIBRATOR_H_INCLUDED_2021_03_27_21_00
#define CALIBRATOR_H_INCLUDED_2021_03_27_21_00

#include "Looper.h"
#include "Timer.h"
#include <vector>
#include <iostream>

/**
 * @brief Estimate the number of loops executed during certain time interval
 * 
 */
class Calibrator:public PeriodicTimer
{
public:

    /**
     * @brief Construct a new Calibrator:: Calibrator object
     * 
     * 
     * @param samplingPeriod_ms time interval 
     * @param nSamples the number of test samples
     */
    Calibrator(double samplingPeriod_ms, unsigned nSamples);

    /**
     * @brief calculate the number of loops executed in time duration_ms
     * 
     * @param duration_ms timer interval
     * @return double the number of loops
     */
    double nLoops(double duration_ms);

    /**
     * @brief regress a and b using linear regression
     * 
     * @param samplingPeriod_ms  x
     * @param nSamples the number of samples
     */
    void calcParam(double samplingPeriod_ms, unsigned nSamples );

protected:

    /**
     * @brief callback function to get the number of samples in each time interval
     * 
     */
    void callback() override;

private:
    double a; ///< parameter of l(t)=axt+b
    double b; ///< parameter of l(t)=axt+b

    double m_counter; ///< count the number of samples
    Looper m_looper;

    std::vector<double> samples;

};

#endif