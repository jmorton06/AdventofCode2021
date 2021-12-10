#include "Day2.h"

int RunDay2(const std::string& dataPath)
{
    
    std::string dataString = StringUtilities::ReadFileIntoString(dataPath);
   
    std::vector<std::string> lines = StringUtilities::GetLines(dataString);
    
    int depth = 0;
    int hPosition = 0;
    int aim = 0;
    
    for(size_t i = 0; i < lines.size(); i++)
    {
        std::vector<std::string> lineData = StringUtilities::SplitString(lines[i], " ");
        if(lineData[0] == "forward")
        {
            int value = std::stoi(lineData[1]);
            hPosition += value;
            depth += aim * value;
        }
        else if(lineData[0] == "up")
            aim -= std::stoi(lineData[1]);
        else if(lineData[0] == "down")
            aim += std::stoi(lineData[1]);
        else
            std::cout << "Error" << std::endl;
    }

    return depth * hPosition;
}
