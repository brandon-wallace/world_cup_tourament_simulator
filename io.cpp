#include <iostream>
#include <fstream>
#include <vector>

// openFile opens a text file and stores the contents in a vector (arrary)
std::vector<std::string> openFile(std::string textfile)
{
    std::ifstream filename (textfile);
    std::vector<std::string> teams{};
    std::string team{};

    if (filename.is_open())
    {
        while (std::getline(filename, team))
        {
            filename >> team;
            teams.push_back(team);
        }
        filename.close();
    }

    return teams;
}
