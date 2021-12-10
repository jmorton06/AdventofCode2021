//
//  Day9.cpp
//  AdventOfCode
//
//  Created by Joseph Morton on 10/12/2021.
//

#include "Day9.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>

int width;
int height;

int** data;

int Day9Part1(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    width = int(lines.front().length());
    height = int(lines.size());
    
    data = new int*[width];
    
    for(int i = 0; i < width; i++)
    {
        data[i] = new int[height];
        
        for(int j = 0; j < height; j++)
        {
            data[i][j] = lines[j][i] - '0';
        }
        
    }
    
    int sum = 0;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            //Up
            if(j + 1 < height && data[i][j] >= data[i][j + 1])
                 continue;
            //Down
            if(j - 1 >= 0 && data[i][j] >= data[i][j - 1])
                continue;
            
            //Right
            if(i + 1 < width && data[i][j] >= data[i + 1][j])
                continue;
            
            //Left
            if(i - 1 >= 0 && data[i][j] >= data[i - 1][j])
                continue;
            
            sum += ((data[i][j]) + 1);
        }
    }
    
    for(int i = 0; i < width; i++)
    {
        delete[] data[i];
    }
    
    delete[] data;
    
    return sum;
}

void FindBasinSize(int x, int y, int& size)
{
    if(data[x][y] < 0)
        return;
    
    //Avoid repeats
    data[x][y]  = -1;
    
    //Up
    if(y + 1 < height && data[x][y + 1] != 9)
        FindBasinSize(x, y + 1, size);
    //Down
    if(y - 1 >= 0 && data[x][y - 1] != 9)
        FindBasinSize(x, y - 1, size);

    //Right
    if(x + 1 < width && data[x + 1][y] != 9)
        FindBasinSize(x + 1, y, size);

    //Left
    if(x - 1 >= 0 && data[x - 1][y] != 9)
        FindBasinSize(x - 1, y, size);
    
    size++;
}

int Day9Part2(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    width = int(lines.front().length());
    height = int(lines.size());
    
    data = new int*[width];
    
    for(int i = 0; i < width; i++)
    {
        data[i] = new int[height];
        
        for(int j = 0; j < height; j++)
        {
            data[i][j] = lines[j][i] - '0';
        }
        
    }
    
    int sum = 0;
    
    std::vector<int> basinSizes;

    for(int i = 0; i < width; i++)
    {
        for(int j = 0; j < height; j++)
        {
            //Up
            if(j + 1 < height && data[i][j] >= data[i][j + 1])
                 continue;
            //Down
            if(j - 1 >= 0 && data[i][j] >= data[i][j - 1])
                continue;
            
            //Right
            if(i + 1 < width && data[i][j] >= data[i + 1][j])
                continue;
            
            //Left
            if(i - 1 >= 0 && data[i][j] >= data[i - 1][j])
                continue;
            
            int size = 0;
            FindBasinSize(i, j, size);
            basinSizes.push_back(size);
        }
    }
    
    std::sort(basinSizes.begin(), basinSizes.end(), std::greater<>());
    
    sum = basinSizes[0] * basinSizes[1] * basinSizes[2];
    
    for(int i = 0; i < width; i++)
    {
        delete[] data[i];
    }
    
    delete[] data;
    
    return sum;
}

int RunDay9(const std::string& filePath)
{
    return Day9Part2(filePath);
}
