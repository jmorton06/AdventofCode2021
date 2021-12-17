#include "Day15.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>
#include <queue>

class Node
{
    public:
    Node* parent = nullptr;
    int fScore = 0;
    int gScore = 0;
    int x = 0;
    int y = 0;
    int value = 0;
};

struct CompareNodePtrs
{
    bool operator()(const Node* a, const Node* b) const
    {
        if (a == nullptr)
          // If b is also 0, then they are equal, hence a is not < than b
          return b != nullptr;
        else if (b == nullptr)
          return false;
        else
         return a->gScore > b->gScore;
    }
};

std::pair<int, int> nodeNeighbours[4] = { {1, 0} , {-1, 0} ,{0, 1} , {0, -1} };
                  
int Day15Part1(const std::string& dataPath)
{
#define USE_EXAMPLE_DATA 0
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);

    
#if USE_EXAMPLE_DATA
    std::vector<std::string> lines = { "1163751742",
        "1381373672",
        "2136511328",
        "3694931569",
        "7463417111",
        "1319128137",
        "1359912421",
        "3125421639",
        "1293138521",
        "2311944581"};
    const int width = 10;
    const int height = 10;
#else
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    const int width = 100;
    const int height = 100;
#endif
    
    //std::vector<Node*> OpenList;
    std::priority_queue<Node*, std::vector<Node*>, CompareNodePtrs> OpenList;

    std::vector<Node*> ClosedList;
    
    Node* NodeData[width][height];

    for(int x = 0; x < width; x++)
    {
        for(int y = 0; y < height; y++)
        {
            NodeData[x][y] = new Node();
            NodeData[x][y]->parent = nullptr;
            NodeData[x][y]->fScore = std::numeric_limits<int>::max();
            NodeData[x][y]->gScore = std::numeric_limits<int>::max();
            NodeData[x][y]->value = lines[y][x] - '0';
            NodeData[x][y]->x = x;
            NodeData[x][y]->y = y;
        }
    }
    
    //Add start node;
    NodeData[0][0]->value = 0;
    NodeData[0][0]->gScore = 0;
    NodeData[0][0]->fScore = 0;

    OpenList.push(NodeData[0][0]);
    
    bool success = false;

    while(!OpenList.empty())
    {
        Node* p = OpenList.top();
        OpenList.pop();
        ClosedList.push_back(p);
        
        if(p == NodeData[width - 1][height - 1])
        {
            success = true;
            break;
        }
        
        for(size_t i = 0; i < 4; i++)
        {
            int xIndex = p->x + nodeNeighbours[i].first;
            int yIndex = p->y + nodeNeighbours[i].second;
            
            if(xIndex < 0 || yIndex < 0 || xIndex >= width || yIndex >= height)
                continue;
                
            Node* neighbour = NodeData[xIndex][yIndex];
            
            // Calculate new scores
            float gScore = p->gScore + neighbour->value;
            float fScore = gScore;// + neighbour->HeuristicValue(*end);

            // Search for this node on open and closed lists
            auto closedIt = std::find(ClosedList.begin(), ClosedList.end(), neighbour);
            if(closedIt != ClosedList.end() || neighbour->gScore != std::numeric_limits<int>::max())
            {
               // Check if this path is more efficient that the previous best
               if(neighbour->gScore > gScore)
               {
                   neighbour->parent = p;
                   neighbour->gScore = gScore;
                   neighbour->fScore = fScore;
                   
                   if(OpenList.size() > 0) {
                       Node* back = OpenList.top();
                       OpenList.pop();
                       OpenList.push(back);
                   }
               }
            }
            else
            {
               // Add this path to the open list if it has yet to be considered
                neighbour->parent = p;
                neighbour->gScore = gScore;
                neighbour->fScore = fScore;
                OpenList.push(neighbour);
            }
        }
    }
    
    std::vector<Node*> Path;

    if(success)
    {
         // Add nodes to path
         Node* n = ClosedList.back();
         while(n)
         {
             Path.push_back(n);
             n = n->parent;
         }

         // Reverse path to be ordered start to end
         std::reverse(Path.begin(), Path.end());
    }
    
    //Draw Path
    {
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                Node* node = NodeData[x][y];
                if(std::find(Path.begin(), Path.end(), node) != Path.end())
                    std::cout << "-";
                else
                    std::cout << "#";
                
                delete NodeData[x][y];
            }
            
            std::cout << std::endl;
        }
    }

    return Path.back()->gScore;
}

uint64_t Day15Part2(const std::string& dataPath)
{
#define USE_EXAMPLE_DATA 0
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);

    
#if USE_EXAMPLE_DATA
    std::vector<std::string> lines = { "1163751742",
        "1381373672",
        "2136511328",
        "3694931569",
        "7463417111",
        "1319128137",
        "1359912421",
        "3125421639",
        "1293138521",
        "2311944581"};
    const int width = 10 * 5;
    const int height = 10 * 5;
#else
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    const int width = 100 * 5;
    const int height = 100 * 5;
#endif
    
    //std::vector<Node*> OpenList;
    std::priority_queue<Node*, std::vector<Node*>, CompareNodePtrs> OpenList;

    std::vector<Node*> ClosedList;
    
    Node* NodeData[width][height];

    for(int x = 0; x < width / 5; x++)
    {
        for(int y = 0; y < height / 5; y++)
        {
            NodeData[x][y] = new Node();
            NodeData[x][y]->parent = nullptr;
            NodeData[x][y]->fScore = std::numeric_limits<int>::max();
            NodeData[x][y]->gScore = std::numeric_limits<int>::max();
            NodeData[x][y]->value = lines[y][x] - '0';
            NodeData[x][y]->x = x;
            NodeData[x][y]->y = y;
        }
    }
    
    //Expand Data;
    
    for(int x = 0; x < width / 5; x++)
    {
        for(int y = 0; y < height / 5; y++)
        {
            for(int i = 0; i <  5; i++)
            {
                for(int j = 0; j < 5; j++)
                {
                    if( i == 0 && j == 0)
                        continue;
                    
                    int newX = x + i * width / 5;
                    int newY = y + j * height / 5;

                    NodeData[newX][newY] = new Node();
                    NodeData[newX][newY]->parent = nullptr;
                    NodeData[newX][newY]->fScore = std::numeric_limits<int>::max();
                    NodeData[newX][newY]->gScore = std::numeric_limits<int>::max();
                    
                    int value = NodeData[x][y]->value + i + j;
                    NodeData[newX][newY]->value = ((value - 1) % 9) + 1;
                    NodeData[newX][newY]->x = newX;
                    NodeData[newX][newY]->y = newY;
                }
            }
        }
    }
    
    //Add start node;
    NodeData[0][0]->value = 0;
    NodeData[0][0]->gScore = 0;
    NodeData[0][0]->fScore = 0;

    OpenList.push(NodeData[0][0]);
    
    bool success = false;

    while(!OpenList.empty())
    {
        Node* p = OpenList.top();
        OpenList.pop();
        ClosedList.push_back(p);
        
        if(p == NodeData[width - 1][height - 1])
        {
            success = true;
            break;
        }
        
        for(size_t i = 0; i < 4; i++)
        {
            int xIndex = p->x + nodeNeighbours[i].first;
            int yIndex = p->y + nodeNeighbours[i].second;
            
            if(xIndex < 0 || yIndex < 0 || xIndex >= width || yIndex >= height)
                continue;
                
            Node* neighbour = NodeData[xIndex][yIndex];
            
            // Calculate new scores
            float gScore = p->gScore + neighbour->value;
            float fScore = gScore;// + neighbour->HeuristicValue(*end);

            // Search for this node on open and closed lists
            auto closedIt = std::find(ClosedList.begin(), ClosedList.end(), neighbour);
            if(closedIt != ClosedList.end() || neighbour->gScore != std::numeric_limits<int>::max())
            {
               // Check if this path is more efficient that the previous best
               if(neighbour->gScore > gScore)
               {
                   neighbour->parent = p;
                   neighbour->gScore = gScore;
                   neighbour->fScore = fScore;
                   
                   if(OpenList.size() > 0) {
                       Node* back = OpenList.top();
                       OpenList.pop();
                       OpenList.push(back);
                   }
               }
            }
            else
            {
               // Add this path to the open list if it has yet to be considered
                neighbour->parent = p;
                neighbour->gScore = gScore;
                neighbour->fScore = fScore;
                OpenList.push(neighbour);
            }
        }
    }
    
    std::vector<Node*> Path;

    if(success)
    {
         // Add nodes to path
         Node* n = ClosedList.back();
         while(n)
         {
             Path.push_back(n);
             n = n->parent;
         }

         // Reverse path to be ordered start to end
         std::reverse(Path.begin(), Path.end());
    }
    
    //Draw Path
    {
        for(int y = 0; y < height; y++)
        {
            for(int x = 0; x < width; x++)
            {
                Node* node = NodeData[x][y];
                if(std::find(Path.begin(), Path.end(), node) != Path.end())
                    std::cout << "-";
                else
                    std::cout << "#";
                
                delete NodeData[x][y];
            }
            
            std::cout << std::endl;
        }
    }

    return Path.back()->gScore;
}

uint64_t RunDay15(const std::string& filePath)
{
    return Day15Part2(filePath);
}
