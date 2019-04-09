#ifndef TIMER_H
#define TIMER_H

#include <iostream>
#include <chrono>
#include <ctime>


// #define CTIME
// #define CHRONO
#define INTRIN

class Timer {
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> chronoBegin;
    clock_t ctimeBegin;
    long long intrinBegin;

    using measure_nano = std::chrono::nanoseconds;
    using measure_micro = std::chrono::microseconds;
    using measure_milli = std::chrono::milliseconds;

    using clock_type = std::chrono::high_resolution_clock;

public:
    Timer();
    void stopAndPrint(std::ostream& out);
};

#endif