//
//  Day10.cpp
//  AdventOfCode
//
//  Created by Joseph Morton on 10/12/2021.
//

#include "Day10.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>

int Day10Part1(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    
    for(const auto& line : lines)
    {

    }
    
    return 0;
}

int Day10Part2(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    return 0;
}

int RunDay10(const std::string& filePath)
{
    return Day10Part1(filePath);
}
