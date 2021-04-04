/**
 * @file Looper.cpp
 * @author ZHANG kai
 * @brief Looper class to run loops
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>

#include "Looper.h"

/**
 * @brief execute loops
 * 
 * @param nLoops number of loops needed to run
 * @return double actually executed loops
 */
double Looper::runLoop(double nLoops)
{
    doStop=false;
    iLoop=0;
    for(int i=0;i<nLoops;i++)
    {
        iLoop++;
        if(doStop)
        {
            break;
        }
    }
    return iLoop;
}

/**
 * @brief get the number of executed loops 
 * 
 * @return double the number of loops
 */
double Looper::getSample()
{
    return iLoop;
}

/**
 * @brief stop the loop by setting doStop=true
 * 
 * @return double the number of current loops
 */
double Looper::stopLoop()
{
    doStop=true;
    return iLoop;
}