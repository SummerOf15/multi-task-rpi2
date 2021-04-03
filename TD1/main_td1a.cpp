/**
 * @file main_td1a.cpp
 * @author ZHANG kai
 * @brief test the functions implemented in TimeUtils.cpp
 * @version 0.1
 * @date 2021-03-11
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <iostream>
#include <climits>
#include "TimeUtils.h"

using namespace std;

int main(int argc, char* argv[])
{
    timespec start, end, duration;
    const timespec delay{0,500000000l};

    // test the conversion between ms and timespec
    double delay_ms=timespec_to_ms(delay);
    timespec delay_spec=timespec_from_ms(delay_ms);
    cout<<"delay in ms: "<<delay_ms<<endl;
    cout<<"delay in timespec:"<<delay_spec.tv_sec<<"s,"<<delay_spec.tv_nsec<<"ns"<<endl;

    // test timespec_now
    start=timespec_now();

    // test timespec wait
    end=timespec_wait(delay);
    end=timespec_now();
    cout<<"start time "<<start.tv_sec<<","<<start.tv_nsec<<endl;
    cout<<"end time "<<end.tv_sec<<","<<end.tv_nsec<<endl;

    // test time_negate
    timespec negate_end=timespec_negate(end);
    cout<<"negative end time"<<negate_end.tv_sec<<"s,"<<negate_end.tv_nsec<<"ns"<<endl;
    negate_end=-end;
    cout<<"- end time"<<negate_end.tv_sec<<"s,"<<negate_end.tv_nsec<<"ns"<<endl;

    // test operation - 
    duration=end-start;
    cout<<"duration "<<duration.tv_sec<<","<<duration.tv_nsec<<endl;

    // test operation > < != ==
    if(end>start && start<end)
    {
        cout<<"end > start"<<endl;
    }
    if (end!=start)
    {
        cout<<"end != start"<<endl;
    }
    if (start+duration==end)
    {
        cout<<"start+duration=end"<<endl;
    }

    return 0;
}