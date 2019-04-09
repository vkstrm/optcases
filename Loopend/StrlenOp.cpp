#include <string>
#include <string.h>
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

    char* cstr = new char[str.length() + 1];
    strcpy(cstr, str.c_str());

    Timer timer;
    size_t len = strlen(cstr);
    for(size_t i = 0; i < len; i++)
    {
        if(cstr[i] == ' ')
        {
            cstr[i] = '*';
        }
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " << str.size() << "\n";
    delete cstr;
}