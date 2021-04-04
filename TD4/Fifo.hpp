/**
 * @file Fifo.hpp
 * @author zk
 * @brief 
 * @version 0.1
 * @date 2021-04-04
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef FIFO_HPP_INCLUDED_2021_04_04
#define FIFO_HPP_INCLUDED_2021_04_04

#include "Mutex.h"
#include <queue>
#include <exception>

/**
 * @brief template class Fifo to imitate the queue operation
 * 
 * @tparam T template type
 */
template <typename T> class Fifo
{
public:
    /**
     * @brief Construct a new Fifo object
     * 
     */
    Fifo();

    /**
     * @brief Destroy the Fifo object
     * 
     */
    ~Fifo();

    /**
     * @brief add an element to the queue
     * 
     * @param element T type element to be added
     */
    void push(T element);

    /**
     * @brief pop the last element of the queue
     * 
     * @return T last element
     */
    T pop();

    /**
     * @brief pop the last element of the queue after a while 
     * 
     * @param timeout_ms time to wait
     * @return T poped element
     */
    T pop(double timeout_ms);

public:
    /**
     * @brief when the queue is empty, throw empty exception
     * 
     */
    class EmptyException : public std::exception
    {
    public:
        const char* emptyException() const noexcept;
    };

private:
    
    std::queue<T> elements; ///< store the elements 
    Mutex mutex; ///< mutex
};

template <typename T> Fifo<T>::Fifo()
{

}

template <typename T> Fifo<T>::~Fifo()
{

}

template <typename T> void Fifo<T>::push(T element)
{
    Mutex::Lock lock(mutex);
    elements.push(element);
}

template <typename T> T Fifo<T>::pop()
{
    Mutex::Lock lock(mutex);
    while(elements.size() == 0)
    {
        lock.wait();
    }
    T popped = elements.front(); ///< the front element of the queue
    elements.pop(); ///< remove the first element

    return popped;
}

template <typename T> T Fifo<T>::pop(double timeout_ms)
{
    Mutex::Lock lock(mutex);
    if(elements.size() == 0)
    {
        lock.wait(timeout_ms);
    }
    if(elements.size() != 0) ///< after timeout, the queue is not empty
    {
        T popped = elements.front();
        elements.pop();
        return popped;
    }
    else   ///< still empty
    {
        throw Fifo<T>::EmptyException();
    }
}

template <typename T> const char *Fifo<T>::EmptyException::emptyException() const noexcept
{
    return "ERROR: The queue is empty!\n";
}

#endif