#include <iostream>
#include <random>
#include <map>
#include "io.h"

int winnerIndex(const std::vector<double> weights)
{
    double sum = {0.0};
    for (const auto& w: weights)
        sum += w;

    double r{ static_cast<float>(rand()) / RAND_MAX * sum };
    for (size_t i = 0; i < weights.size(); i++)
    {
        r -= weights[i];
        if (r < 0) 
        {
            return static_cast<int>(i);
        }
    }

    return static_cast<int>(weights.size() - 1);
}

// playMatch iterates through a map of teams and weights, selects a random winner, and returns a map
std::map<std::string, double> playMatch(const std::map<std::string, double> teamMap, int count)
{
    std::map<std::string, double> winners;
    auto it = teamMap.begin();

    for (int i = 0; i < count; i+=2)
    {
        std::string t1 = it->first;
        double w1 = it->second;
        it++;
        std::string t2 = it->first;
        double w2 = it->second;
        ++it;
        std::cout << " " << t1 << " vs " << t2 << '\n';
        std::vector<double> match{w1, w2};
        int index = { winnerIndex(match) };
        if (index == 0) 
        {
            std::cout << " ---- Winner: " << t1 << '\n';
            winners.insert(std::make_pair(t1, w1));
        }
        else
        {
            std::cout << " ---- Winner: " << t2 << '\n';
            winners.insert(std::make_pair(t2, w2));
        }
    }

    return winners;
}

// printWinner prints elements from the winners vector
void printWinner(const std::vector<std::string> winners)
{
    std::cout << " Winners:" << '\n';
    for (auto& team: winners)
        std::cout << " " << team << '\n';
    std::cout << '\n';
}

int main()
{
    std::map<std::string, double> group1 = openFile("group1.txt");
    std::map<std::string, double> group2 = openFile("group2.txt");

    std::cout << '\n';
    std::cout << " Round Of Sixteen:" << '\n';
    std::map<std::string, double> roundOfSixteen1{ playMatch(group1, 16) };
    std::map<std::string, double> roundOfSixteen2{ playMatch(group2, 16) };
    std::cout << '\n';

    std::cout << " Semi Finals:" << '\n';
    std::map<std::string, double> semiFinal1{ playMatch(roundOfSixteen1, 8) };
    std::map<std::string, double> semiFinal2{ playMatch(roundOfSixteen2, 8) };
    std::cout << '\n';

    std::cout << " Quarter Finals:" << '\n';
    std::map<std::string, double> quarterFinal1{ playMatch(semiFinal1, 4) };
    std::map<std::string, double> quarterFinal2{ playMatch(semiFinal2, 4) };
    std::cout << '\n';

    std::cout << " Finals:" << '\n';
    std::map<std::string, double> final1{ playMatch(quarterFinal1, 2) };
    std::map<std::string, double> final2{ playMatch(quarterFinal2, 2) };
    std::cout << '\n';

    std::map<std::string, double> champions;
    auto it = final1.begin();
    std::cout << " " << it->first << '\n';
    champions.insert(std::make_pair(it->first, it->second));

    it = final2.begin();
    std::cout << " " << it->first << '\n';
    std::cout << '\n';
    champions.insert(std::make_pair(it->first, it->second));

    std::cout << " World Championship:" << '\n';
    std::map<std::string, double> champion{ playMatch(champions, 1) };
    std::cout << '\n';

    return 0;
}
