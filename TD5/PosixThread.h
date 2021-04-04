/**
 * @file PosixThread.h
 * @author ZK
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef POSIXTHREAD_H_INCLUDED_2021_04_03
#define POSIXTHREAD_H_INCLUDED_2021_04_03

#include <pthread.h>
#include <exception>
using namespace std;


class PosixThread
{
public:

    /**
     * @brief Construct a new Posix Thread object
     * 
     */
    PosixThread();

    /**
     * @brief Construct a new Posix Thread object
     * 
     * @param posixId thread id
     */
    PosixThread(pthread_t posixId);

    /**
     * @brief Destroy the Posix Thread object
     * 
     */
    ~PosixThread();

    /**
     * @brief start the thread
     * 
     * @param threadFunc handler function of the thread
     * @param threadArg arguments
     */
    void start(void*(*threadFunc)(void*), void* threadArg);

    /**
     * @brief wait the thread stops
     * 
     */
    void join();
    
    /**
     * @brief stop the thread after time interval
     * 
     * @param timeout_ms time interval
     * @return true successfully stop
     * @return false failed
     */
    bool join(double timeout_ms);

    /**
     * @brief Set the Scheduling object
     * 
     * @param schedPolicy schedule policy
     * @param priority priority of current thread
     * @return true set successfully
     * @return false failed
     */
    bool setScheduling(int schedPolicy, int priority);

    /**
     * @brief Get the Scheduling object
     * 
     * @param pSchedPolicy schedule policy pointer
     * @param pPriority priority of current thread pointer
     * @return true get successfully
     * @return false failed
     */
    bool getScheduling(int* pSchedPolicy, int* pPriority);

public:
    class Exception:exception
    {
    public:
        /**
         * @brief define an exception when launching the thread
         * 
         * @return const char* 
         */
        const char* threadException() const noexcept;
    };

private:
    pthread_t posixId; ///< thread id
    pthread_attr_t posixAttr; ///< attributes of the thread

protected:
    bool isActive; ///< thread flag: active or inactive
};

#endif