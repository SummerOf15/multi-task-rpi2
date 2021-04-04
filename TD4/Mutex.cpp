/**
 * @file Mutex.cpp
 * @author zk and cy
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Mutex.h"
#include "TimeUtils.h"

Mutex::Mutex()
{
    pthread_mutex_init(&posixId, nullptr);
    pthread_cond_init(&posixCondId, nullptr);
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&posixId);
    pthread_cond_destroy(&posixCondId);
}

void Mutex::lock()
{
    pthread_mutex_lock(&posixId);
}

bool Mutex::lock(double timeout_ms)
{
    timespec timeout = timespec_from_ms(timeout_ms) + timespec_now();
    bool ret = pthread_mutex_timedlock(&posixId, &timeout);
    return !(bool) ret;
}

bool Mutex::trylock()
{
    return (bool) pthread_mutex_trylock(&posixId);
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&posixId);
}

Mutex::Monitor::Monitor(Mutex &m) : mMutex(m)
{
    
}

void Mutex::Monitor::wait()
{
    pthread_cond_wait(&mMutex.posixCondId, &mMutex.posixId);
}

bool Mutex::Monitor::wait(double timeout_ms)
{
    timespec timeout = timespec_from_ms(timeout_ms) + timespec_now();
    bool out = pthread_cond_timedwait(&mMutex.posixCondId, &mMutex.posixId, &timeout);
    return (bool) out;
}

void Mutex::Monitor::notify()
{
    pthread_cond_signal(&mMutex.posixCondId);
}

void Mutex::Monitor::notifyAll()
{
    pthread_cond_broadcast(&mMutex.posixCondId);
}

Mutex::Lock::Lock(Mutex &m) : Mutex::Monitor::Monitor(m)
{
    m.lock();
}

Mutex::Lock::Lock(Mutex &m, double timeout_ms) : Mutex::Monitor::Monitor(m)
{
     int ret = m.lock(timeout_ms);
     if (ret != false) 
     {
        throw Mutex::Monitor::TimeoutException();
     }
}

Mutex::Lock::~Lock()
{
    mMutex.unlock();
}


Mutex::TryLock::TryLock(Mutex &m) : Mutex::Monitor::Monitor(m)
{
    int ret=m.trylock();
    if (ret != false) 
    {
        throw Mutex::Monitor::TimeoutException();
    }
}

Mutex::TryLock::~TryLock()
{
    mMutex.unlock();
}