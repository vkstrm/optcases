#include <iostream>
#include <fstream>

#include "../Timer/Timer.h"
#include "../Vector/Vector.h"

int main()
{
    Vector<float> array;
    float temp = 0;
    std::ifstream file;
    file.open("floatdata.txt");
    while(file >> temp) 
    {
        array.push_back(temp);
    }
    file.close();

    float sum = 0;
    Timer timer;
    for(auto it = array.begin(); it != array.end(); it++)
    {   
        sum += *it;
    }   
    
    timer.stopAndPrint(std::cout);
    std::cout << " " <<  sum << "\n";
}