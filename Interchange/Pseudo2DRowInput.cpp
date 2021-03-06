#include <iostream>
#include <fstream>

#include "../Timer/Timer.h"

//Pass 112 and 1024 for rows and cols, or whatever you want i guess.
int main(int argc, char* argv[])
{
    int rows, cols;
    rows = std::stoi(argv[1]);
    cols = std::stoi(argv[2]);
    int* array = new int[cols * rows];
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
            array[i * 1024 + j] = filearray[j];
        }
    }  

    int sum = 0;
    Timer timer;
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            sum += array[i * cols + j];
        }
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " << sum << "\n";
}