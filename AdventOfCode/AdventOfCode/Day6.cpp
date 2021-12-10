//
//  Day6.cpp
//  AdventOfCode
//
//  Created by Joseph Morton on 08/12/2021.
//

#include "Day6.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>

uint64_t RunDay6(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> data = StringUtilities::SplitString(dataString, ",");
        
    uint64_t fishCount[9] = {0};
    
    for(const auto& entry : data)
    {
        fishCount[std::stoi(entry)]++;
    }
    
    for(int day = 0; day < 256; day++)
    {
        
        uint64_t newFishCount = fishCount[0];
        uint64_t fishCountCopy[9] = {0};
        
        for(int i = 0; i < 9; i++)
        {
            fishCountCopy[i] = fishCount[i];
        }
        
        
        for(int i = 8; i >= 0; i--)
        {
            if(i > 0)
                fishCount[i - 1] = fishCountCopy[i];
            else
            {
                fishCount[6] += fishCountCopy[0];
                fishCount[8] = newFishCount;
            }
        }
    }
    
    uint64_t totalFish = 0;
    
    for(int i = 0; i < 9; i++)
    {
        totalFish += fishCount[i];
    }
    
    return totalFish;
}
