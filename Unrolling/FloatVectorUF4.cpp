#include <iostream>
#include <fstream>
#include <vector>

#include "../Timer/Timer.h"


int main()
{
    std::vector<float> array;
    array.reserve(1024);
    float temp = 0;
    std::ifstream file;
    file.open("floatdata.txt");
    while(file >> temp) 
    {
        array.push_back(temp);
    }

    float sum = 0;
    Timer timer;
    for(int i = 0; i < 1024; i += 4) 
    {
        sum += array[i];
        sum += array[i + 1];
        sum += array[i + 2];
        sum += array[i + 3];
    }

    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}