#include <string>
#include <iostream>

// #include "../Timer/Timer.h"

/**
 * Fifteen character string is the max for when a std::string is unrolled.
 * 16 characters and a normal loop is used instead.
 * This only happens when the loop condition wont change.
 * 
 * 
 * With the removal of the timers, the loop will be unrolled. With the timer however, not.
 */

int main()
{
    std::string str("Hello world Hel");
    // Timer timer;
    size_t len = str.size();
    for(size_t i = 0; i < len; i++) 
    {
        if(str[i] == ' ')
        {
            str[i] = '*';
        }
    }
    // timer.stopAndPrint(std::cout);
    std::cout << " " << str << "\n";
}