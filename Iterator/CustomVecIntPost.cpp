#include <iostream>
#include <fstream>

#include "../Timer/Timer.h"
#include "../Vector/Vector.h"

int main()
{
    Vector<int> array;
    array.reserve(1024);
    int temp = 0;
    std::ifstream file;
    file.open("data.txt");
    while(file >> temp) 
    {
        array.push_back(temp);
    }
    file.close();

    int sum = 0;
    Timer timer;
    for(auto it = array.begin(); it != array.end(); it++)
    {   
        sum += *it;
    }   
    
    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}