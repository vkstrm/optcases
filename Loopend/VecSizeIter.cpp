#include <iostream>
#include <fstream>
#include <vector>

#include "../Timer/Timer.h"


int main()
{
    std::vector<int> array;
    int temp = 0;
    std::ifstream file;
    file.open("data.txt");
    while(file >> temp) 
    {
        array.push_back(temp);
    }

    int sum = 0;
    Timer timer;
    for(auto it = array.begin(); it != array.end(); ++it) 
    {
        sum += *it;
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}