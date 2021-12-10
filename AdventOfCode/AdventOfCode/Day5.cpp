//
//  Day5.cpp
//  AdventOfCode
//
//  Created by Joseph Morton on 08/12/2021.
//

#include "Day5.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>

int GridData[1000][1000] = {0};
std::vector<std::pair<int, int>> intersectedPoints;
const double pi = std::acos(-1.0);

float GetAngleXAxis(int x, int y)
{
    return 180 * atan2(x, y) / pi;
}

int RunDay5(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    for(auto& line : lines)
    {
        auto points = StringUtilities::SplitString(line, " -> ");
        auto PointA = StringUtilities::SplitString(points[0], ",");
        auto PointB = StringUtilities::SplitString(points[1], ",");
        
        int PointAX = std::stoi(PointA[0]);
        int PointAY = std::stoi(PointA[1]);

        int PointBX = std::stoi(PointB[0]);
        int PointBY = std::stoi(PointB[1]);
        
        if(PointAX == PointBX)
        {
            int min = PointAY < PointBY ? PointAY : PointBY;
            int max = PointAY < PointBY ? PointBY : PointAY;

            for(int i = min; i < max + 1; i++)
            {
                GridData[PointAX][i]++;
                
                if(GridData[PointAX][i] == 2)
                {
                    intersectedPoints.emplace_back(PointAX, i);
                }
            }
        }
        else if(PointAY == PointBY)
        {
            int min = PointAX < PointBX ? PointAX : PointBX;
            int max = PointAX < PointBX ? PointBX : PointAX;

            for(int i = min; i < max + 1; i++)
            {
                GridData[i][PointAY]++;
                
                if(GridData[i][PointAY] == 2)
                {
                    intersectedPoints.emplace_back(i, PointAY);
                }
            }
        }
        
        else if(PointAX - PointAY == PointBX - PointBY  )
        {
            auto min = std::min(PointAX, PointBX);
            auto max = std::max(PointAX, PointBX);
            auto yIndex = std::min(PointAY, PointBY);
            for(int i = min; i < max + 1; i++)
            {
                GridData[i][yIndex]++;

                if(GridData[i][yIndex] == 2)
                {
                    intersectedPoints.emplace_back(i, yIndex);
                }

                yIndex++;// += yIncrease;
            }
        }
        
        else if(PointAX + PointAY == PointBX + PointBY  )
        {
                            //int min = PointAX < PointBX ? PointAX : PointBX;
                            //int max = PointAX < PointBX ? PointBX : PointAX;
            
              auto min = std::min(PointAX, PointBX);
              auto max = std::max(PointAX, PointBX);
              auto yIndex = std::max(PointAY, PointBY);
            
            for(int i = min; i < max + 1; i++)
            {
                GridData[i][yIndex]++;

                if(GridData[i][yIndex] == 2)
                {
                    intersectedPoints.emplace_back(i, yIndex);
                }

                yIndex--;// += yIncrease;
            }
        }
        
//        else
//        {
//            //Check if line is 45 degrees
//
//            int directionX = PointBX - PointAX;
//            int directionY = PointBY - PointAY;
//
//            int angle = int(GetAngleXAxis(directionY, directionX));
//
//            if( angle == 45)
//            {
//                int min = PointAX < PointBX ? PointAX : PointBX;
//                int max = PointAX < PointBX ? PointBX : PointAX;
//
//                int yIncrease = PointAY < PointBY ? 1 : -1;
//                int yIndex = PointAY;// < PointBY ? PointAY : PointBY;
//                for(int i = min; i < max + 1; i++)
//                {
//                    GridData[i][yIndex]++;
//
//                    if(GridData[i][yIndex] == 2)
//                    {
//                        intersectedPoints.emplace_back(i, yIndex);
//                    }
//
//                    if(i == max )
//                        if(yIndex != PointBY)
//                        std::cout << "Error" << std::endl;
//
//
//                    yIndex++;// += yIncrease;
//                }
//            }
            
            

       // }
    }
    
    return int(intersectedPoints.size());
}
