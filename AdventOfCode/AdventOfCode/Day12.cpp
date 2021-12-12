#include "Day12.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include "StringUtilities.h"
#include <unordered_map>
#include <cmath>
#include <algorithm>

struct Node
{
    std::string Name;
    bool Start = false;
    bool End = false;
    bool SmallCave = false;
    
    std::vector<Node*> Links;
};

bool IsUppercase(const std::string& str)
{
    return std::all_of(str.begin(), str.end(), [](unsigned char c){ return std::isupper(c); });
}

int NodeCount = 0;
Node NodePool[1000];
Node* StartNode;
std::unordered_map<std::string, Node*> NodeMap;

void ParseData(const std::vector<std::string>& lines)
{
    for(const auto& line : lines)
    {
        auto link = StringUtilities::SplitString(line, "-");
        Node* nodeA;
        Node* nodeB;

        std::unordered_map<std::string, Node*>::const_iterator link0 = NodeMap.find (link[0]);
        if(link0 == NodeMap.end())
        {
            auto& node = NodePool[NodeCount];
            node.Name = link[0];
            node.End = node.Name == "end";
            node.Start = node.Name == "start";
            node.SmallCave = !IsUppercase(node.Name);
            NodeMap[node.Name] = &node;
            nodeA = &node;
            NodeCount++;
            
            if(node.Start)
                StartNode = nodeA;
        }
        else
        {
            nodeA = link0->second;
        }
        
        std::unordered_map<std::string, Node*>::const_iterator link1 = NodeMap.find (link[1]);
        if(link1 == NodeMap.end())
        {
            auto& node = NodePool[NodeCount];
            node.Name = link[1];
            node.End = node.Name == "end";
            node.Start = node.Name == "start";
            node.SmallCave = !IsUppercase(node.Name);
            NodeMap[node.Name] = &node;
            nodeB = &node;
            NodeCount++;
            
            if(node.Start)
                StartNode = nodeB;
        }
        else
        {
            nodeB = link1->second;
        }
        
        nodeA->Links.push_back(nodeB);
        nodeB->Links.push_back(nodeA);
    }
}

void FindPath(Node* currentNode, std::vector<Node*> path, int& pathCount, bool visitedSmallCave = true)
{
    path.push_back(currentNode);
    
    for(auto node : currentNode->Links)
    {
        bool currentPathVisitedSmallCave = visitedSmallCave;
        if(node->SmallCave)
        {
            if(visitedSmallCave == true && std::find(path.begin(), path.end(), node) != path.end())
                continue;
            
            if(!visitedSmallCave)
            {
                int count = std::count (path.begin(), path.end(), node);
                if(count == 2)
                    continue;
                
                if(count == 1)
                    currentPathVisitedSmallCave = true;
            }
        }
        
        if(node->Start)
            continue;
        
        if(node->End)
        {
            pathCount++;
            continue;
        }
        
        FindPath(node, path, pathCount, currentPathVisitedSmallCave);
    }
}
                       
int Day12Part1(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    ParseData(lines);
    
    int pathCount = 0;
    std::vector<Node*> startPath;
    FindPath(StartNode, startPath, pathCount);

    return pathCount;
}

uint64_t Day12Part2(const std::string& dataPath)
{
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
        
    ParseData(lines);
    
    int pathCount = 0;
    std::vector<Node*> startPath;
    FindPath(StartNode, startPath, pathCount, false);

    return pathCount;
}

uint64_t RunDay12(const std::string& filePath)
{
    return Day12Part2(filePath);
}
