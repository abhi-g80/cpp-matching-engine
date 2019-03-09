#ifndef TIMER_TIME_H
#define TIMER_TIME_H

#include <chrono>
#include <cstdint>

namespace TimeStamper
{

class Timer {
    std::chrono::high_resolution_clock m_clock;

public:
    uint64_t milliseconds();
    uint64_t microseconds();
    uint64_t nanoseconds();
};

uint64_t Timer::milliseconds() 
{
    return std::chrono::duration_cast<std::chrono::milliseconds>
              (m_clock.now().time_since_epoch()).count();
}

uint64_t Timer::microseconds() 
{
    return std::chrono::duration_cast<std::chrono::microseconds>
              (m_clock.now().time_since_epoch()).count();
}

uint64_t Timer::nanoseconds()
{
    return std::chrono::duration_cast<std::chrono::nanoseconds>
              (m_clock.now().time_since_epoch()).count();
}    

}
#endif  /* TIMER_TIME_H */