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
    for(int i = 0; i < 1024; i += 16) 
    {
        sum += (array[i] * 0.5);
        sum += (array[i + 1] * 0.5);
        sum += (array[i + 2] * 0.5);
        sum += (array[i + 3] * 0.5);
        sum += (array[i + 4] * 0.5);
        sum += (array[i + 5] * 0.5);
        sum += (array[i + 6] * 0.5);
        sum += (array[i + 7] * 0.5);
        sum += (array[i + 8] * 0.5);
        sum += (array[i + 9] * 0.5);
        sum += (array[i + 10] * 0.5);
        sum += (array[i + 11] * 0.5);
        sum += (array[i + 12] * 0.5);
        sum += (array[i + 13] * 0.5);
        sum += (array[i + 14] * 0.5);
        sum += (array[i + 15] * 0.5);
    }

    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}