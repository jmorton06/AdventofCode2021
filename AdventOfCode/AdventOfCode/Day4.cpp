//
//  Day4.cpp
//  AdventOfCode
//
//  Created by Joseph Morton on 07/12/2021.
//

#include "Day4.hpp"


#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"

struct BingoBoard
{
    int rowTotal[5] = {0};
    int columnTotal[5] = {0};
    int data[5][5] = {0};
    bool stamped[5][5] = {false};
};

int RunDay4(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    std::vector<int> drawNumbers;
   
    {
        auto numbers = StringUtilities::SplitString(lines.front(), ",");
        for(auto& c : numbers)
        {
            drawNumbers.emplace_back(std::stoi(c));
        }
    }
    
    std::vector<BingoBoard> boards;
    for(size_t i = 1; i < lines.size(); i+=5)
    {
        BingoBoard board;
        for(int j = 0; j < 5; j++)
        {
            for(int k = 0; k < 5; k++)
            {
                auto numbers = StringUtilities::SplitString(lines[i + j], " ");
                board.data[j][k] = std::stoi(numbers[k]);
            }
        }
        
        boards.push_back(board);
    }
    
    int currentBestBoard = -1;
    int currentBestBoardTime = 0;
    int bestBoardLastCalled = 0;
    
    int currentBestAnswer = 0;
    
    for(auto& board : boards)
    {
        int drawNumbersIndex = 0;
        bool boardWon = false;
        for(auto draw : drawNumbers)
        {
            //if(drawNumbersIndex > currentBestBoardTime)
             //   break;
            
            if(boardWon)
                break;
            
            for(int j = 0; j < 5; j++)
            {
                for(int k = 0; k < 5; k++)
                {
                    if(board.data[j][k] == draw)
                    {
                        board.stamped[j][k] = true;
                        
                        bool rowFailed = false;
                        bool columnFailed = false;
                        
                        for(int i = 0; i < 5; i++)
                        {
                            if(!rowFailed && !board.stamped[j][i])
                                rowFailed = true;
                            
                            if(!columnFailed && !board.stamped[i][k])
                                columnFailed = true;
                        }
                        
                        //Check Win
                        if(!columnFailed || !rowFailed)
                        {
                            bestBoardLastCalled = draw;
                            
                            int sum = 0;
                            for(int j = 0; j < 5; j++)
                            {
                                for(int k = 0; k < 5; k++)
                                {
                                    if(!board.stamped[j][k])
                                        sum += board.data[j][k];
                                }
                            }
                            
                            boardWon = true;
                            
                            if(drawNumbersIndex >= currentBestBoardTime)
                            {
                                currentBestBoardTime = drawNumbersIndex;
                                currentBestAnswer = sum * draw;
                            }
                      
                        }
                    }
                }
                
            }
            drawNumbersIndex++;

        }
    }
    
    return currentBestAnswer;
}
