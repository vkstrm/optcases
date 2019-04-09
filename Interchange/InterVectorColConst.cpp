#include <iostream>
#include <vector>
#include <fstream>

#include "../Timer/Timer.h"

int main()
{
    const size_t rows = 112;
    const size_t cols = 1024;

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
    for(size_t j = 0; j < cols; j++)
    {
        for(size_t i = 0; i < rows; i++)
        {
            sum += vec[i][j];
        }
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " << sum << "\n";
}