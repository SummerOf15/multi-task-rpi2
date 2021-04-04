/**
 * @file Chrono.cpp
 * @author ZHANG kai
 * @brief 
 * @version 0.1
 * @date 2021-04-03
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Chrono.h"
#include "TimeUtils.h"

Chrono::Chrono()
{
    restart();
}

Chrono::~Chrono()
{

}

void Chrono::restart()
{
    m_startTime=timespec_now();
    m_stopTime=m_startTime;
}

bool Chrono::isActive()
{
    return m_startTime==m_stopTime;
}

void Chrono::stop()
{
    m_stopTime=timespec_now();
}

double Chrono::startTime()
{
    return timespec_to_ms(m_startTime);
}

double Chrono::stopTime()
{
    return timespec_to_ms(m_stopTime);
}

double Chrono::lap()
{
    return timespec_to_ms((isActive()? timespec_now():m_stopTime)-m_startTime);
}