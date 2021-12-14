#include "Day13.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>
                  
int Day13Part1(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    std::vector<std::pair<int, int>> data;
    int width = 0;
    int height = 0;
    
    int lineIndex = 0;
    std::string& line = lines[lineIndex];
    while(line != "" && !StringUtilities::StringContains(line, "fold"))
    {
        auto numbers = StringUtilities::SplitString(line, ",");
                
        int x = std::stoi(numbers[0]);
        int y = std::stoi(numbers[1]);
        
        width = std::max(width, x + 1);
        height = std::max(height, y + 1);

        data.emplace_back(x,y);
        lineIndex++;
        line = lines[lineIndex];
    }
    
    bool** dots = new bool*[width];
    
    for(int i = 0; i < width; i++)
    {
        dots[i] = new bool[height];
        
        for(int j = 0; j < height; j++)
        {
            dots[i][j] = false;
        }
    }
    
    std::vector<std::pair<char, int>> folds;
    
    //lineIndex = start of fold commands
    for(int i = lineIndex; i < lines.size(); i++)
    {
        auto foldCommand = StringUtilities::SplitString(StringUtilities::RemoveString(lines[i],"fold along "), "=");
        folds.emplace_back(foldCommand[0][0], std::stoi(foldCommand[1]));
    }
    
    for(auto& pair : data)
    {
        dots[pair.first][pair.second] = true;
    }
    
    //Fold onces
    char axis = folds[0].first;
    int foldValue = folds[0].second;
    
    if(axis == 'x')
    {
        for(int i = foldValue + 1; i < width; i++)
        {
            for(int j = 0; j < height; j++)
            {
                if(dots[i][j])
                {
                    int distanceFromFold = i - foldValue;
                    int index = foldValue - distanceFromFold;
                    
                    if(index >= 0 && index < width)
                        dots[index][j] = true;

                }
            }
        }
        
        width = foldValue;
    }
    else if(axis == 'y')
    {
        for(int i = 0; i < width; i++)
        {
            for(int j = foldValue + 1; j < height; j++)
            {
                if(dots[i][j])
                {
                    int distanceFromFold = j - foldValue;
                    int index = foldValue - distanceFromFold;
                    
                    if(index >= 0 && index < width)
                        dots[i][index] = true;

                }
            }
        }
        height = foldValue;
    }
    
    
    int dotCount = 0;
    
    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            if(dots[i][j])
                dotCount++;
        }
    }
    
    return dotCount;
}

uint64_t Day13Part2(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    std::vector<std::pair<int, int>> data;
    int width = 0;
    int height = 0;
    
    int lineIndex = 0;
    std::string& line = lines[lineIndex];
    while(line != "" && !StringUtilities::StringContains(line, "fold"))
    {
        auto numbers = StringUtilities::SplitString(line, ",");
                
        int x = std::stoi(numbers[0]);
        int y = std::stoi(numbers[1]);
        
        width = std::max(width, x + 1);
        height = std::max(height, y + 1);

        data.emplace_back(x,y);
        lineIndex++;
        line = lines[lineIndex];
    }
    
    bool** dots = new bool*[width];
    
    for(int i = 0; i < width; i++)
    {
        dots[i] = new bool[height];
        
        for(int j = 0; j < height; j++)
        {
            dots[i][j] = false;
        }
    }
    
    std::vector<std::pair<char, int>> folds;
    
    //lineIndex = start of fold commands
    for(int i = lineIndex; i < lines.size(); i++)
    {
        auto foldCommand = StringUtilities::SplitString(StringUtilities::RemoveString(lines[i],"fold along "), "=");
        folds.emplace_back(foldCommand[0][0], std::stoi(foldCommand[1]));
    }
    
    for(auto& pair : data)
    {
        dots[pair.first][pair.second] = true;
    }
        
    for(auto& fold : folds)
    {
        char axis = fold.first;
        int foldValue = fold.second;
        
        if(axis == 'x')
        {
            for(int i = foldValue + 1; i < width; i++)
            {
                for(int j = 0; j < height; j++)
                {
                    if(dots[i][j])
                    {
                        int distanceFromFold = i - foldValue;
                        int index = foldValue - distanceFromFold;
                        
                        if(index >= 0 && index < width)
                            dots[index][j] = true;

                    }
                }
            }
            
            width = foldValue;
        }
        else if(axis == 'y')
        {
            for(int i = 0; i < width; i++)
            {
                for(int j = foldValue + 1; j < height; j++)
                {
                    if(dots[i][j])
                    {
                        int distanceFromFold = j - foldValue;
                        int index = foldValue - distanceFromFold;
                        
                        if(index >= 0 && index < height)
                            dots[i][index] = true;

                    }
                }
            }
            height = foldValue;
        }
    }
    
    
    int dotCount = 0;
    
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(dots[j][i])
                std::cout << " # ";
            else
                std::cout << " . ";

        }
        std::cout << std::endl;
    }
    
    return dotCount;
}

uint64_t RunDay13(const std::string& filePath)
{
    return Day13Part2(filePath);
}
