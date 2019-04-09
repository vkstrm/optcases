#include "Timer.h"
#include "IntrinTimer.h"

Timer::Timer()
{
    #if defined CHRONO
        chronoBegin = clock_type::now();
    #elif defined CTIME
        ctimeBegin = clock();
    #elif defined INTRIN
        intrinBegin = readTSC();
    #endif
}

void Timer::stopAndPrint(std::ostream& out)
{
    #if defined CHRONO
        out << std::chrono::duration_cast<measure_micro>(clock_type::now() - chronoBegin).count();    
    #elif defined CTIME
        out << clock() - ctimeBegin;
    #elif defined INTRIN
        out << readTSC() - intrinBegin;
    #endif
}