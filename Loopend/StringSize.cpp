#include <string>
#include <iostream>

#include "../Timer/Timer.h"

int main()
{
    std::string str("Hello world");
    Timer timer;
    for(size_t i = 0; i < str.size(); i++) 
    {
        if(str[i] == ' ')
        {
            str[i] = '*';
        }
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " << str << "\n";
}