#include <string>
#include <iostream>
#include <fstream>

#include "../Timer/Timer.h"

int main()
{
    std::string str;
    std::string line;
    std::ifstream fstream;
    fstream.open("bible.txt");
    while(getline(fstream, line))
    {
        str.append(line);
    }

    Timer timer;
    auto end = str.end();
    for(auto it = str.begin(); it != end; ++it) 
    {
        if(*it == ' ')
        {
            *it = '*';
        }
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " << str.size() << "\n";
}