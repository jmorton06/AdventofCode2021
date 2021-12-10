//
//  Day7.cpp
//  AdventOfCode
//
//  Created by Joseph Morton on 09/12/2021.
//

#include "Day7.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>

int RunDay7(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> data = StringUtilities::SplitString(dataString, ",");
        
    std::vector<int> hPositions;
    
    int max = 0;
    
    for(const auto& pos : data)
    {
        hPositions.emplace_back(std::stoi(pos));
        
        if(hPositions.back() > max)
            max = hPositions.back();
    }
    
    int currentBest = INT_MAX;
    for(int i = 0; i < max; i++)
    {
        
        int currentPetrolCost = 0;
        for(auto pos : hPositions)
        {
            int min = std::min(pos, i);
            int max = std::max(pos, i);
            
            int currentStep = 1;
            
            for(int i = min; i < max; i ++)
            {
                currentPetrolCost += currentStep;
                currentStep++;

            }
        }
        
        if(currentPetrolCost < currentBest)
            currentBest = currentPetrolCost;
        
    }
    
    return currentBest;
}
