#include <iostream>
#include <fstream>

#include "../Timer/Timer.h"

int main()
{
    int array[1024 * 112];
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
    for(int j = 0; j < 1024; j++)
    {
        for(int i = 0; i < 112; i++)
        {
            sum += array[i * 1024 + j];
        }
    }
    timer.stopAndPrint(std::cout);
    std::cout << " " << sum << "\n";
}