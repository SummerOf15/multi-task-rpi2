/**
 * @file CpuLoop.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "CpuLoop.h"


/**
 * @brief Construct a new Cpu Loop:: Cpu Loop object
 * 
 * @param calibrator 
 */
CpuLoop::CpuLoop(Calibrator& calibrator)
{
    p_calibrator=&calibrator;
}

/**
 * @brief run calibrator for duration_ms ms
 * 
 * @param duration_ms running time
 */
void CpuLoop::runTime(double duration_ms)
{
    runLoop((p_calibrator->nLoops(duration_ms)));
}