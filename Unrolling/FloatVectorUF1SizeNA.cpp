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
    for(size_t i = 0; i < array.size(); i++) 
    {
        sum += array[i];
    }

    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}