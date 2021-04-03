/**
 * @file main_td1c.cpp
 * @author your name (you@domain.com)
 * @brief verify the accuracy of a timer
 * @version 0.1
 * @date 2021-04-02
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "TimeUtils.h"

int main(int argc, char* argv[])
{
    if(argc!=2) // if input parameters are not suitable
    {
        cerr<<"1 extra parameter is expected"<<endl;
        return -1;
    }
    unsigned int nLoops = stoi(argv[1]); 
    double counter=0.0;
    timespec start=timespec_now(); // start recording the running time
    incr(nLoops,&counter);
    timespec end=timespec_now();
    timespec duration=end-start;
    cout<<"final value:"<<counter<<endl;
    cout<<"running time is "<<timespec_to_ms(duration)/1000.0<<endl;
    return 0;
}

