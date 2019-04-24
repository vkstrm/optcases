#include <iostream>
#include <fstream>

#include "../Timer/Timer.h"

int main()
{
    int array[1024];
    int temp, i = 0;
    std::ifstream file;
    file.open("data.txt");
    while(file >> temp) 
    {
        array[i++] = temp;
    }

    int sum = 0;
    int len = sizeof(array) / sizeof(int);
    Timer timer;
    for(int i = 0; i < len; i++) 
    {
        sum += array[i];
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}