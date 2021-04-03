/**
 * @file main_td3a.cpp
 * @author ZHANG kai
 * @brief Chrono function test
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Chrono.h"

#include <cstdlib>
#include <iostream>
#include <unistd.h>


int main(int argc, char* argv[])
{
    unsigned int waitTime_s=1;
    if (argc>1)
    {
        waitTime_s=std::atoi(argv[1]);
    }
    std::cout<<"wait time "<<waitTime_s<<"s ..."<<std::endl;
    Chrono c;
    sleep(waitTime_s);
    c.stop();
    std::cout<<"done"<<std::endl;
    std::cout<<"duration "<<c.lap()/1000.0<<"s"<<std::endl;
    return 0;
}