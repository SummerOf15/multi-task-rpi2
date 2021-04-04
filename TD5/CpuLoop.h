/**
 * @file CpuLoop.h
 * @author ZHANG kai
 * @brief 
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef CPULOOP_H_INCLUDED_2021_03_26_22_43
#define CPULOOP_H_INCLUDED_2021_03_26_22_43

#include "Calibrator.h"
#include "Looper.h"

class CpuLoop:public Looper
{
public:
    /**
     * @brief Construct a new Cpu Loop object
     * 
     * @param calibrator a calibrator to calibrate cpu loops
     */
    CpuLoop(Calibrator& calibrator);
    /**
     * @brief run calibrator for duration_ms ms
     * 
     * @param duration_ms running time
     */
    void runTime(double duration_ms);

private:
    Calibrator* p_calibrator; ///< calibrator

};

#endif