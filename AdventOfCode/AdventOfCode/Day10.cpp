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
    
    int points = 0;
    for(const auto& line : lines)
    {
        std::vector<char> expected;
        /*
         ): 3 points.
         ]: 57 points.
         }: 1197 points.
         >: 25137 points.
         */
        
        for(size_t i = 0; i < line.length(); i++)
        {
            char current = line[i];
            bool failed = false;
            switch (current) {
                case '{':
                    expected.push_back('}');
                    break;
                case '}':
                    if(expected.back() == '}')
                    {
                        expected.pop_back();
                    }
                    else
                    {
                        points += 1197;
                        failed = true;
                    }
                  
                    break;
                case '(':
                    expected.push_back(')');
                    break;
                case ')':
                    if(expected.back() == ')')
                    {
                        expected.pop_back();
                    }
                    else
                    {
                        points += 3;
                        failed = true;
                    }
                    break;
                case '<':
                    expected.push_back('>');
                    break;
                case '>':
                    
                    if(expected.back() == '>')
                    {
                        expected.pop_back();
                    }
                    else
                    {
                        points += 25137;
                        failed = true;
                    }
                    break;
                case '[':
                    expected.push_back(']');
                    break;
                case ']':
                    if(expected.back() == ']')
                    {
                        expected.pop_back();
                    }
                    else
                    {
                        points += 57;
                        failed = true;
                    }
                    break;
                default:
                    break;
            }
            
            if(failed)
                break;
        }
    }
    
    return points;
}

uint64_t Day10Part2(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    uint64_t points = 0;
    std::vector<uint64_t> scores;
    for(const auto& line : lines)
    {
        std::vector<char> expected;
        /*
         ): 3 points.
         ]: 57 points.
         }: 1197 points.
         >: 25137 points.
         */
        bool failed = false;

        for(size_t i = 0; i < line.length(); i++)
        {
            char current = line[i];
            switch (current)
            {
                case '{':
                    expected.push_back('}');
                    break;
                case '}':
                    if(expected.back() == '}')
                    {
                        expected.pop_back();
                    }
                    else
                    {
                        failed = true;
                    }
                    break;
                case '(':
                    expected.push_back(')');
                    break;
                case ')':
                    if(expected.back() == ')')
                    {
                        expected.pop_back();
                    }
                    else
                    {
                        failed = true;
                    }
                    break;
                case '<':
                    expected.push_back('>');
                    break;
                case '>':
                    if(expected.back() == '>')
                    {
                        expected.pop_back();
                    }
                    else
                    {
                        failed = true;
                    }
                    break;
                case '[':
                    expected.push_back(']');
                    break;
                case ']':
                    if(expected.back() == ']')
                    {
                        expected.pop_back();
                    }
                    else
                    {
                        failed = true;
                    }
                    break;
                default:
                    break;
            }
            
            if(failed)
                break;
        }
        
        if(failed)
            continue;
    
        /*
         ): 1 point.
         ]: 2 points.
         }: 3 points.
         >: 4 points.
         */
        std::reverse(expected.begin(), expected.end());

        uint64_t score = 0;
        for(char close : expected)
        {
            switch(close)
            {
                case ')' :
                    score = score * 5 + 1;
                    break;
                case ']' :
                    score = score * 5 + 2;
                    break;
                case '}' :
                    score = score * 5 + 3;
                    break;
                case '>' :
                    score = score * 5 + 4;
                    break;
                default:
                    break;
            }
        }
        scores.push_back(score);

    }
    
    std::sort(scores.begin(), scores.end());
    points = scores[scores.size() / 2];
    return points;
}

uint64_t RunDay10(const std::string& filePath)
{
    return Day10Part2(filePath);
}
