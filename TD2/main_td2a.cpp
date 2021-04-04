/**
 * @file main_td2a.cpp
 * @author ZHANG kai
 * @brief execute multi-tasks without lock
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <pthread.h>
#include <iostream>
#include <vector>
using namespace std;


/**
 * @brief thread data structure
 * 
 */
struct Data{
    unsigned loop; ///< the number of loops
    double counter; ///< counter
};

/**
 * @brief increase the count
 * 
 * @param nLoops number of loops 
 * @param pCounter counter
 */
void incr(unsigned int nLoops, double* pCounter)
{
    for(unsigned i=0;i<nLoops;i++)
    {
        *pCounter+=1.0;
    }
}

/**
 * @brief callback function
 * 
 * @param v_data input data
 * @return void* 
 */
void* call_incr(void* v_data)
{
    Data* pData=(Data*) v_data;
    incr(pData->loop, &(pData->counter));
    return v_data;
}


int main(int argc, char* argv[])
{
    if (argc!=3)
    {
        cout<<"only "<<argc-1<<" parameters are provided"<<endl; 
        return -1;
    }
    unsigned nLoops=atoi(argv[1]);
    unsigned nTasks=atoi(argv[2]);

    Data data;
    data.counter=0.0;
    data.loop=nLoops;

    vector<pthread_t> incrThread(nTasks);
    for(unsigned i=0;i<nTasks;i++)
    {
        pthread_create(&incrThread[i], nullptr, call_incr, &data);
    }

    for(unsigned i=0;i<nTasks;i++)
    {
        pthread_join(incrThread[i], nullptr);
    }
    cout<<"counter value: "<<data.counter<<endl;
}