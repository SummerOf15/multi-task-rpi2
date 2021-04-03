/**
 * @file Calibrator.cpp
 * @author ZHANG kai
 * @brief Calibrator class
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Calibrator.h"
#include <numeric>


Calibrator::Calibrator(double samplingPeriod_ms, unsigned nSamples)
{
    m_counter=nSamples; 
    start(samplingPeriod_ms);
    m_looper.runLoop();
    calcParam(samplingPeriod_ms,nSamples);
    std::cout<<"a= "<<a<<",b= "<<b<<std::endl;
}


double Calibrator::nLoops(double duration_ms)
{
    return a*duration_ms+b;
}


void Calibrator::callback()
{
    m_counter--;
    if(m_counter>0)
    {
        samples.push_back(m_looper.getSample()); ///< add the number of loops executed during an interval
    }
    else if(m_counter==0) ///< run out of time
    {
        samples.push_back(m_looper.stopLoop()); ///< add samples when stoping the looper
        std::cout<<"----------stop-----------"<<std::endl;
        return;
    }
}


void Calibrator::calcParam(double samplingPeriod_ms, unsigned nSamples )
{
    double s_y=0.0;
    double s_x=0.0;
    int numSamples=samples.size();

    // calculate the sum of loop number and time
    for(int i=0;i<numSamples;i++)
    {
        s_y+=samples[i];
        s_x+=samplingPeriod_ms;
    }

    double s_xx, s_xy;
    for(int i=0;i<numSamples;i++)
    {
        s_xx+=samplingPeriod_ms*samplingPeriod_ms;
        s_xy+=samplingPeriod_ms*samples[i];
    }
    
    a = (nSamples * s_xy - s_x * s_y) / (nSamples * s_xx - s_x * s_x+1e-9);
    b=s_y-a*s_x;
}
