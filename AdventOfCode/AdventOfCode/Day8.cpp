//
//  Day8.cpp
//  AdventOfCode
//
//  Created by Joseph Morton on 09/12/2021.
//

#include "Day8.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>


int Day8Part1(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    int numberCount = 0;

    for(const auto& line : lines)
    {
        auto data = StringUtilities::SplitString(line, "|");
        auto numbers = StringUtilities::SplitString(data[1], " ");
        
        for(const auto& number : numbers)
        {
            int stringLength = number.length();
            
            if(stringLength == 2 || stringLength == 3 || stringLength == 4 || stringLength == 7 )
            {
                numberCount++;
            }
        }
    }
    return numberCount;
}

int Day8Part2(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    int numberCount = 0;

    for(const auto& line : lines)
    {
        auto data = StringUtilities::SplitString(line, "|");
        auto signals = StringUtilities::SplitString(data[0], " ");
        auto numbers = StringUtilities::SplitString(data[1], " ");
        
        std::string values[10];

        for(auto& number : signals)
        {
            std::sort(number.begin(), number.end());
        }
        
        for(auto& number : numbers)
        {
            std::sort(number.begin(), number.end());
        }

        for(const auto& number : signals)
        {
            int stringLength = int(number.length());
            
            if(stringLength == 2)
            {
                values[1] = number;
            }
            else if(stringLength == 3)
            {
                values[7] = number;
            }
            else if(stringLength == 4)
            {
                values[4] = number;
            }
            else if(stringLength == 7 )
            {
                values[8] = number;
            }
        }
        
        std::string Top = StringUtilities::RemoveCharacters(values[7], values[1]);
        std::string LeftMiddle = StringUtilities::RemoveCharacters(values[4], values[1]);

        for(const auto& number : signals)
        {
            int stringLength = int(number.length());

            if(stringLength == 6)
            {
                //0 6 or 9
                
                if(!StringUtilities::StringContainsChars(number, LeftMiddle))
                    values[0] = number;
                else if(!StringUtilities::StringContainsChars(number, values[1]))
                    values[6] = number;
                else
                    values[9] = number;

            }
            else if(stringLength == 5)
            {
                //2 3 or 5
                
                if(StringUtilities::StringContainsChars(number, values[1]))
                    values[3] = number;
                else if(StringUtilities::StringContainsChars(number, LeftMiddle))
                    values[5] = number;
                else
                    values[2] = number;
            }
        }
        
        std::stringstream value;
        for(const auto& number : numbers)
        {
            for(int i = 0; i < 10; i++)
            {
                if(number == values[i])
                    value << i;
            }
        }
        
        numberCount += std::stoi(value.str());
    }
    return numberCount;
}

int RunDay8(const std::string& filePath)
{
    return Day8Part2(filePath);
}
