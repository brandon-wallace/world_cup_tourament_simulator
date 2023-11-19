#include <iostream>
#include <fstream>
#include <vector>
#include <map>

// openFile opens a text file and stores the contents in a vector (arrary)
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
            // std::cout << team << " " << weight << '\n';
            teamData.insert(std::make_pair(team, weight));
        }
        while (filename);
    }
    filename.close();

    return teamData;
}
