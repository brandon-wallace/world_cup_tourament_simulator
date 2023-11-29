#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <map>
#include <string>

void printHeader()
{
    std::cout << 
R"(
 ┬ ┬┌─┐┬─┐┬  ┌┬┐  ┌─┐┬ ┬┌─┐      
 ││││ │├┬┘│   ││  │  │ │├─┘      
 └┴┘└─┘┴└─┴─┘─┴┘  └─┘└─┘┴        
 ┌┬┐┌─┐┬ ┬┬─┐┌┐┌┌─┐┌┬┐┌─┐┌┐┌┌┬┐  
  │ │ ││ │├┬┘│││├─┤│││├┤ │││ │   
  ┴ └─┘└─┘┴└─┘└┘┴ ┴┴ ┴└─┘┘└┘ ┴   
 ┌─┐┬┌┬┐┬ ┬┬  ┌─┐┌┬┐┌─┐┬─┐       
 └─┐│││││ ││  ├─┤ │ │ │├┬┘       
 └─┘┴┴ ┴└─┘┴─┘┴ ┴ ┴ └─┘┴└─
 )";
}

// openFile opens a text file and stores the contents in a vector (array)
std::map<std::string, double> openFile(std::string textfile)
{
    std::ifstream filename (textfile);
    std::map<std::string, double> teamData;
    std::string team = "";
    double weight = 0.0;

    if (filename.is_open())
    {
        do
        {
            filename >> team >> weight;
            teamData.insert(std::make_pair(team, weight));
        }
        while (filename);
    }
    filename.close();

    return teamData;
}

// printFillChar replaces space characters with another character
std::string printFillChar(std::string str, const std::string& from, const std::string& to)
{
    size_t startPos{0};
    while((startPos = str.find(from, startPos)) != std::string::npos)
    {
        str.replace(startPos, from.length(), to);
        startPos += to.length();
    }

    return str;
}

// printBracket prints ascii characters to show which team played against each other
void printBracket(std::string t1, std::string t2)
{
    t1.resize(12, ' ');
    t2.resize(12, ' ');
    std::string spaceChar = " ";
    std::string lineChar = "─";
    std::cout << "\n " << std::left << std::setw(12) << printFillChar(t1, spaceChar, lineChar) << "──┐" << '\n';
    std::cout << " " << std::cout.fill(' ') << std::right << std::setw(20) << "├─ " << t1 << '\n';
    std::cout << " " << std::left << std::setw(12) << printFillChar(t2, spaceChar, lineChar) << "──┘" << '\n';
}

