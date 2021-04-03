/**
 * @file main_td1b.cpp
 * @author ZHANG kai
 * @brief generate and test a timer function
 * @version 0.1
 * @date 2021-04-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "TimeUtils.h"


int main()
{
    double counter=0.0;
    timespec start=timespec_now();
    generate_timer(2,15,&counter);
    timespec end=timespec_now();
    timespec duration=end-start;
    cout<<timespec_to_ms(duration)/1000.0<<endl;
    return 0;
}