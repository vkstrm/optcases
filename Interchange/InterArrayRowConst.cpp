#include <iostream>
#include <fstream>

#include "../Timer/Timer.h"

int main()
{
    int rows = 112;
    int cols = 1024;
    int array[rows][cols];
    int filearray[1024];
    int temp = 0, i = 0;
    std::ifstream file;
    file.open("data.txt");
    while(file >> temp) 
    {
        filearray[i++] = temp;
    }
    file.close();

    for(int i = 0; i < 112; i++)
    {    
        for(int j = 0; j < 1024; j++) 
        {   
            array[i][j] = filearray[j];
        }
    } 

    int sum = 0;
    Timer timer;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            sum += array[i][j];
        }
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " << sum << "\n";
}