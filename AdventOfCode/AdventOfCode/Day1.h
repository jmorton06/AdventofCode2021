#pragma once

#include <iostream>
#include <fstream>
#include <vector>

int RunDay1(const std::string& dataPath)
{
    std::ifstream dataFile(dataPath);
   
    //read file into array
    std::vector<int> numberArray;

    int previousValue = -1;
    int largerCount = 0;
    for( std::string line; getline( dataFile, line ); )
    {
        numberArray.push_back(stoi(line));
    }
    
    for(int i = 0; i < numberArray.size() - 2; i++)
    {
        int currentTotal = 0;
            currentTotal = numberArray[i] + numberArray[i + 1] + numberArray[i + 2];
       
        if(previousValue > 0 && currentTotal > previousValue)
            largerCount++;
        
        previousValue = currentTotal;
    }
    
    return largerCount;
}
