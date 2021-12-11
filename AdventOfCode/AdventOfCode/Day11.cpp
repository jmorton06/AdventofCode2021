#include "Day11.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>

std::pair<int,int> neighbours[8] = { {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1,1}, {1, 0}, { 1, -1} , {0, -1}};

bool InBounds(int x, int y, int width, int height)
{
    if(0 <= x && x < width && 0 <= y && y < height)
        return true;
    
    return false;
}

void Flash(int x, int y, int data[10][10], uint32_t& flashes)
{
    if(data[x][y] == 0)
        return;
    
    flashes++;
    data[x][y] = 0;

    for(auto neighbour : neighbours)
    {
        int posX = x + neighbour.first;
        int posY = y + neighbour.second;

        if(InBounds(posX, posY, 10, 10) && data[posX][posY] > 0)
        {
            data[posX][posY]++;
            if(data[posX][posY] > 9)
                Flash(posX, posY, data, flashes);
        }
    }
    
}

int Day11Part1(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
        
    int energyLevels[10][10] = {0};
    uint32_t flashes = 0;
    
    int lineIndex = 0;
    for(const auto& line : lines)
    {
        for(size_t i = 0; i < 10; i++)
        {
            energyLevels[i][lineIndex] = line[i] - '0';
        }
        
        lineIndex++;
    }
    
    const int steps = 100;
    
    for( int i = 0; i < steps; i++)
    {
        std::vector<std::pair<int,int>> toFlash;
        
        for(int x = 0; x < 10; x++)
        {
            for(int y = 0; y < 10; y++)
            {
                energyLevels[x][y]++;
                if(energyLevels[x][y] > 9)
                    toFlash.emplace_back(std::pair(x,y));
            }
        }
        
        for(auto pair : toFlash)
        {
            Flash(pair.first, pair.second, energyLevels, flashes);
        }
    }
    
    return flashes;
}

uint64_t Day11Part2(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
        
    int energyLevels[10][10] = {0};
    uint32_t flashes = 0;
    
    int lineIndex = 0;
    for(const auto& line : lines)
    {
        for(size_t i = 0; i < 10; i++)
        {
            energyLevels[i][lineIndex] = line[i] - '0';
        }
        
        lineIndex++;
    }
        
    int stepCount = 0;
    //for( int i = 0; i < steps; i++)
    while(flashes < 100)
    {
        flashes = 0;
        std::vector<std::pair<int,int>> toFlash;
        
        for(int x = 0; x < 10; x++)
        {
            for(int y = 0; y < 10; y++)
            {
                energyLevels[x][y]++;
                if(energyLevels[x][y] > 9)
                    toFlash.emplace_back(std::pair(x,y));
            }
        }
        
        for(auto pair : toFlash)
        {
            Flash(pair.first, pair.second, energyLevels, flashes);
        }
        
        stepCount++;
    }
    
    return stepCount;
}

uint64_t RunDay11(const std::string& filePath)
{
    return Day11Part2(filePath);
}
