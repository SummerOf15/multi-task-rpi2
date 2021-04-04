/**
 * @file main_td2c.cpp
 * @author ZHANG kai
 * @brief execute multi-tasks with lock
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <pthread.h>
#include <iostream>
#include <vector>
#include "TimeUtils.h"
using namespace std;


/**
 * @brief thread data structure
 * 
 */
struct Data{
    unsigned loop; ///< the number of loops
    double counter;  ///<counter
    pthread_mutex_t mutex;  ///< lock
    bool useMutex;  ///< whether use the mutex
};


/**
 * @brief callback function
 * 
 * @param v_data data of the thread
 * @return void* 
 */
void* call_incr(void* v_data)
{
    Data* pData=(Data*) v_data;
    if(pData->useMutex) ///< if use the mutex
        for(unsigned i=0;i<pData->loop;i++)
        {
            pthread_mutex_lock(&(pData->mutex)); ///< open the lock
            pData->counter+=1.0;  ///< change the counter value
            pthread_mutex_unlock(&(pData->mutex)); ///< unlock
        }
    else
    {
        incr(pData->loop, &(pData->counter));
    }
    return (void*) pData;
}

/**
 * @brief the main function to test multiple tasks
 * 
 * @param argc 
 * @param argv 
 * @return int 
 */
int main(int argc, char* argv[])
{
    if (argc!=4)
    {
        cerr<<"only "<<argc-1<<" parameters are provided"<<endl; 
        return -1;
    }
    unsigned nLoops=atoi(argv[1]);
    unsigned nTasks=atoi(argv[2]);
    string protect=argv[3];

    Data data;
    data.counter=0.0;
    data.loop=nLoops;
    data.useMutex=false;
    if(protect.compare("protected")==0)
    {
        // use mutex for protection
        data.useMutex=true;
        pthread_mutex_init(&data.mutex, nullptr);
    }
    else
    {
        cout<<"no protection"<<endl;
    }
    
    timespec start, end, duration;
    start=timespec_now();
    vector<pthread_t> incrThread(nTasks);
    for(unsigned i=0;i<nTasks;i++)
    {
        pthread_create(&incrThread[i], nullptr, call_incr, &data);
    }

    for(unsigned i=0;i<nTasks;i++)
    {
        pthread_join(incrThread[i], nullptr);
    }
    end=timespec_now();
    duration=end-start;
    cout<<"counter value: "<<data.counter<<endl;
    cout<<"time (ms) "<<timespec_to_ms(duration)<<endl;
    
    if(data.useMutex)
        pthread_mutex_destroy(&data.mutex);
}