#include <string>
#include <iostream>
#include <fstream>

#include "../Timer/Timer.h"

//bara kollar om const gör någon skillnad på len, men det gör det inte.
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
    const size_t len = str.size();
    for(size_t i = 0; i < len; i++) 
    {
        if(str[i] == ' ')
        {
            str[i] = '*';
        }
    }

    timer.stopAndPrint(std::cout);
    std::cout << " " << str.size() << "\n";

}