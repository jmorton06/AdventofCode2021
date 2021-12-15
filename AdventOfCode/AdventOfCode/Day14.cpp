#include "Day14.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>
                  
int Day14Part1(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);

    std::string polymerTemplate = lines[0];
    
    std::unordered_map<std::string, char> InsertionPairs;
    for(auto& line : lines)
    {
        if(StringUtilities::StringContains(line, "->"))
        {
            auto data = StringUtilities::SplitString(line, " -> ");
            InsertionPairs[data[0]] = data[1][0];
        }
    }
    
    
    //10 steps
    for(int i = 0; i < 10; i++)
    {
        std::vector<std::pair<int, char>> charactersToInsert;
        
        for(int j = 0; j < polymerTemplate.length() - 1; j++)
        {
            auto pair = polymerTemplate.substr(j, 2);
            
            auto find = InsertionPairs.find(pair);
            if(find != InsertionPairs.end())
            {
                charactersToInsert.emplace_back(j + 1, find->second);
            }
        }
        
        int insertCount = 0;
        
        for(auto& chars : charactersToInsert)
        {
            polymerTemplate.insert(chars.first + insertCount,1, chars.second);
            insertCount++;
        }
    }
    
    std::unordered_map<char, int> charCount;
    
    for(int i = 0; i < polymerTemplate.length(); i++)
    {
        auto find = charCount.find(polymerTemplate[i]);
        if(find == charCount.end())
            charCount[polymerTemplate[i]] = 0;
            
        charCount[polymerTemplate[i]]++;
    }
    
    int maxCount = INT_MIN;
    int minCount = INT_MAX;
    
    std::for_each(charCount.begin(), charCount.end() , [&](std::pair<char, int > element){
        std::cout << element.first << "," << element.second << std::endl;

        maxCount = std::max(maxCount, element.second);
        minCount = std::min(minCount, element.second);
                    });
    
    return maxCount - minCount;
}

uint64_t Day14Part2(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);

    std::string polymerTemplate = lines[0];
    
    std::unordered_map<std::string, char> InsertionPairs;
    for(auto& line : lines)
    {
        if(StringUtilities::StringContains(line, "->"))
        {
            auto data = StringUtilities::SplitString(line, " -> ");
            InsertionPairs[data[0]] = data[1][0];
        }
    }
    
    const int steps = 40;
    
    std::map<std::string, uint64_t> pairCount;
    std::map<char, uint64_t> charCount;
    char lastChar;

    for(int j = 0; j < polymerTemplate.length() - 1; j++)
    {
        auto pair = polymerTemplate.substr(j, 2);
        if(pairCount.find(pair) == pairCount.end())
            pairCount[pair] = 0;
        pairCount[pair]++;
        
        if(j == polymerTemplate.length() - 2)
            lastChar = polymerTemplate[j + 1];
    }
    

    //40 steps
    for(int i = 0; i < steps; i++)
    {
        std::cout << "Step " << i << std::endl;
        std::map<std::string, uint64_t> newPairCount;

        int index = 0;
        std::for_each(pairCount.begin(), pairCount.end() , [&](std::pair<std::string, uint64_t > element)
        {
            std::string newPairs[2];
            char insertChar = InsertionPairs[element.first];
            
            newPairs[0] = std::string(1, element.first[0]) + std::string(1, insertChar);
            newPairs[1] = std::string(1, insertChar) + std::string(1, element.first[1]);
            
            if(newPairCount.find(newPairs[0]) == newPairCount.end())
                newPairCount[newPairs[0]] = 0;
            if(newPairCount.find(newPairs[1]) == newPairCount.end())
                newPairCount[newPairs[1]] = 0;
            
            newPairCount[newPairs[0]] += element.second;
            newPairCount[newPairs[1]] += element.second;
            
            if(i == steps -1)
            {
                if(charCount.find(newPairs[0][0]) == charCount.end())
                    charCount[newPairs[0][0]] = 0;
                if(charCount.find(newPairs[0][1]) == charCount.end())
                    charCount[newPairs[0][1]] = 0;
                if(charCount.find(newPairs[1][1]) == charCount.end())
                    charCount[newPairs[1][1]] = 0;
                
                charCount[newPairs[0][0]] += element.second;
                charCount[newPairs[0][1]] += element.second;
                
                if(index == pairCount.size() - 1)
                    charCount[lastChar] += 1;
                
                index++;
            }
        });
        
        pairCount = newPairCount;
    }
    
    uint64_t maxCount = 0;
    uint64_t minCount = UINT64_MAX;
    
    std::for_each(charCount.begin(), charCount.end() , [&](std::pair<char, uint64_t > element){
        std::cout << element.first << "," << element.second << std::endl;
        maxCount = std::max(maxCount, element.second);
        minCount = std::min(minCount, element.second);
        std::cout << minCount << "," << maxCount << std::endl;

                    });
    
    return maxCount - minCount;
}

uint64_t RunDay14(const std::string& filePath)
{
    return Day14Part2(filePath);
}
