#include <x86intrin.h>
#include <cpuid.h>

// from Optimizing C++, Agner Fog

long long readTSC() //Returns time stamp counter
{
    int dummy[4];                                       //For unused returns
    volatile int dontSkip;                              //Volatile to prevent optimization
    long long clock;                                    //Time
    __cpuid(0, dummy[0], dummy[1], dummy[2], dummy[3]); //Serialize
    dontSkip = dummy[0];                                //Prevent optimizing away cpuid
    clock = __rdtsc();                                  //Read time
    return clock;
}