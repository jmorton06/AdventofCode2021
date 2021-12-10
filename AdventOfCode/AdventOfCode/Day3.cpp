//
//  Day3.cpp
//  AdventOfCode
//
//  Created by Joseph Morton on 07/12/2021.
//

#include "Day3.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"

std::vector<std::string> FilterOutByBit(bool greater, int pos, const std::vector<std::string>& data)
{
    int count = 0;

    for(auto& line : data)
    {
        int binaryNumber[12];
        
        int i = pos;
        {
            char character = line[i];
            binaryNumber[i] =  character - '0';
            
            if(binaryNumber[i] > 0)
                count++;
            else
                count--;
        }
    }
    
    std::vector<std::string> filtered;
    int keepbit = 0;
    
    if(count >= 0)
        keepbit = greater ? 1 : 0;
    else if(count < 0)
        keepbit = greater ? 0 : 1;
    
    for(int i = 0; i < data.size(); i++)
    {
        int bit = data[i][pos] - '0';
        
        if(bit == keepbit)
            filtered.push_back(data[i]);
    }
    
    return filtered;
}

int RunDay3(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
   
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    int gamma = 0;
    int epsilon  = 0;
    int count[12] = { 0 };
    for(auto& line : lines)
    {
        int binaryNumber[12];
        
        for(int i = 0; i < 12; i++)
        {
            char character = line[i];
            binaryNumber[i] =  character - '0';
            
            if(binaryNumber[i] > 0)
                count[i]++;
            else
                count[i]--;
        }
    }
    
    std::stringstream gammaBinary, epsilonBinary;
    
    for(int i = 0; i < 12; i++)
    {
        if(count[i] > 0)
        {
            gammaBinary << "1";
            epsilonBinary << "0";
        }
        else
        {
            gammaBinary << "0";
            epsilonBinary << "1";
        }
    }
    
    gamma = std::stoi(gammaBinary.str(), nullptr, 2);
    epsilon = std::stoi(epsilonBinary.str(), nullptr, 2);
    
    
    //part 2
    auto data = lines;
    
    int bitPos = 0;
    
    while(data.size() > 1)
    {
        data = FilterOutByBit(true, bitPos, data);
        bitPos++;
    }
    
    int oxygenRating = std::stoi(data.front(), nullptr, 2);
    
    data = lines;
    bitPos = 0;
    
    while(data.size() > 1)
    {
        data = FilterOutByBit(false, bitPos, data);
        bitPos++;
    }
    
    int c02Rating = std::stoi(data.front(), nullptr, 2);


    return oxygenRating * c02Rating;
}
