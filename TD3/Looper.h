/**
 * @file Looper.h
 * @author ZHANG kai
 * @brief Looper class to run loops
 * @version 0.1
 * @date 2021-03-27
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LOOPER_H_INCLUDED_2021_03_27_21_06
#define LOOPER_H_INCLUDED_2021_03_27_21_06


class Looper
{
public:

    double runLoop(double nLoops=__DBL_MAX__);
    double getSample();
    double stopLoop();

private:
    volatile bool doStop; ///< flag parameter: true->stop, false->run
    double iLoop; ///< number of loops
};

#endif