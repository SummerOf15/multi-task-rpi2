/**
 * @file main_td3c.cpp
 * @author ZHANG kai
 * @brief test code for td3_c
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Calibrator.h"
#include "CpuLoop.h"
#include "Chrono.h"

#include <iostream>

int main()
{
    Calibrator calibrator(1000,20); ///< 1hz 20 samples
    std::cout<<"finished calibration"<<std::endl;
    CpuLoop cpuLoop(calibrator); ///< use cpuloop

    int t=1000; ///< running time
    Chrono chrono;
    cpuLoop.runTime(t);
    chrono.stop();
    std::cout<<"running time "<<chrono.lap()<<std::endl;

    unsigned realLoopNum=(unsigned) cpuLoop.getSample();
    unsigned estimatedLoopNum=(unsigned) calibrator.nLoops(t);

    
    std::cout<<"The real number of loop for"<<t<<"ms is "<<realLoopNum<<std::endl;
    std::cout<<"The estimated number of loop for"<<t<<"ms is "<<estimatedLoopNum<<std::endl;
    std::cout<<"The difference is "<<realLoopNum-estimatedLoopNum<<std::endl;
    return 0;
}