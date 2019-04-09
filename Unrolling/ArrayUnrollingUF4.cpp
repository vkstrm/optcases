#include <iostream>
#include <fstream>
#include "../Timer/Timer.h"

int main()
{
    int array[1024];
    int temp = 0, i = 0;
    std::ifstream file;
    file.open("data.txt");
    while(file >> temp) 
    {
        array[i++] = temp;
    }

    int sum = 0;
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