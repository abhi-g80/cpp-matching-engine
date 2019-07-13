#include <iostream>
#include "timer.hpp"

int main()
{
    TimeStamper::Timer t;

    std::cout << t.milliseconds() << std::endl;
    std::cout << t.microseconds() << std::endl;
    std::cout << t.nanoseconds() << std::endl;

    return 0;
}