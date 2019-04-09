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
    Timer timer;
    for(int i = 0; i < 1024; i += 16) 
    {
        sum += array[i];
        sum += array[i + 1];
        sum += array[i + 2];
        sum += array[i + 3];
        sum += array[i + 4];
        sum += array[i + 5];
        sum += array[i + 6];
        sum += array[i + 7];
        sum += array[i + 8];
        sum += array[i + 9];
        sum += array[i + 10];
        sum += array[i + 11];
        sum += array[i + 12];
        sum += array[i + 13];
        sum += array[i + 14];
        sum += array[i + 15];
    }

    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}