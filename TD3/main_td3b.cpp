/**
 * @file main_td3b.cpp
 * @author ZHANG kai (kaizhangpostbox@foxmail.com)
 * @brief tf3b test count timer
 * @version 0.1
 * @date 2021-03-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "TimeUtils.h"
#include "Timer.h"


int main()
{
    int n=10;
    CountDown count(n);
    count.start(1000); ///< start counting with interval of 1s

    while(true)
    {
        if(count.getCount()<=0)
        {
            cout<<"--------stop------"<<endl;
            count.stop();
            break;
        }
    }
    return 0;
}


