#include <iostream>
#include <vector>
#include <fstream>

#include "../Timer/Timer.h"

int main()
{
    std::vector<std::vector<int>> vec;
    std::vector<int> array;

    int temp = 0;
    std::ifstream file;
    file.open("data.txt");
    while(file >> temp) 
    {
        array.push_back(temp);
    }
    for(int i = 0; i < 112; i++)
    {    
        vec.push_back(array);
    }
    file.close();

    int sum = 0;
    Timer timer;
    for(size_t i = 0; i < vec.size(); i++)
    {
        for(size_t j = 0; j < vec[i].size(); j++)
        {
            sum += vec[i][j];
        }
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " << sum << "\n";
}