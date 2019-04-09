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
    for(size_t i = 0; i < str.size(); i++) 
    {
        if(str[i] == ' ')
        {
            str[i] = '*';
        }
    }

    timer.stopAndPrint(std::cout);
    std::cout << " " << str.size() << "\n";
}