#include <iostream>
#include <fstream>
#include <vector>

#include "../Timer/Timer.h"


int main()
{
    std::vector<int> array;
    array.reserve(1024);
    int temp = 0;
    std::ifstream file;
    file.open("data.txt");
    while(file >> temp) 
    {
        array.push_back(temp);
    }

    int sum = 0;
    Timer timer;
    for(int i = 0; i < 1024; i++) 
    {
        sum += array[i] * 0.5;
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}