#include <iostream>
#include <random>
#include <map>
#include "io.h"

// winnerIndex returns the index of the weight in the vector
int winnerIndex(const std::vector<double> weights)
{
    double sum = {0.0};
    for (const auto& w: weights)
        sum += w;

    srand(static_cast<unsigned>(time(nullptr)));
    double r{ static_cast<double>(rand()) / RAND_MAX * sum };
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
        std::vector<double> match{w1, w2};
        int index = { winnerIndex(match) };
        std::string winner = "";
        std::string loser = "";
        if (index == 0) 
        {
            winner = t1;
            loser = t2;
            winners.insert(std::make_pair(t1, w1));
        }
        else
        {
            winner = t2;
            loser = t1;
            winners.insert(std::make_pair(t2, w2));
        }
        printBracket(winner, loser);
    }

    return winners;
}

int main()
{
    printHeader();
    std::map<std::string, double> group1 = openFile("group1.txt");
    std::map<std::string, double> group2 = openFile("group2.txt");

    std::cout << '\n';
    std::cout << " ROUND OF SIXTEEN:" << '\n';
    std::map<std::string, double> roundOfSixteen1{ playMatch(group1, 16) };
    std::map<std::string, double> roundOfSixteen2{ playMatch(group2, 16) };
    std::cout << '\n';

    std::cout << " SEMI FINALS:" << '\n';
    std::map<std::string, double> semiFinal1{ playMatch(roundOfSixteen1, 8) };
    std::map<std::string, double> semiFinal2{ playMatch(roundOfSixteen2, 8) };
    std::cout << '\n';

    std::cout << " QUARTER FINALS:" << '\n';
    std::map<std::string, double> quarterFinal1{ playMatch(semiFinal1, 4) };
    std::map<std::string, double> quarterFinal2{ playMatch(semiFinal2, 4) };
    std::cout << '\n';

    std::cout << " FINALS:" << '\n';
    std::map<std::string, double> final1{ playMatch(quarterFinal1, 2) };
    std::map<std::string, double> final2{ playMatch(quarterFinal2, 2) };
    std::cout << '\n';

    std::vector<std::string> finalFour = {};
    std::string t1 = {};
    std::string t2 = {};
    std::string t3 = {};
    std::string t4 = {};

    std::cout << '\n';

    std::map<std::string, double> champions;
    auto it = final1.begin();
    t1 = it->first;
    champions.insert(std::make_pair(it->first, it->second));
    it = final2.begin();
    t2 = it->first;

    std::vector<std::string> thirdPlace = {};
    auto it3 = quarterFinal1.begin();
    if (it3->first != t1)
    {
        t3 = it3->first;
        thirdPlace.push_back(t3);
    }
    else
    {
        it3++;
        t3 = it3->first;
        thirdPlace.push_back(t3);
    }

    auto it4 = quarterFinal2.begin();
    if (it4->first != t2)
    {
        t4 = it4->first;
        thirdPlace.push_back(t4);
    }
    else
    {
        it4++;
        t4 = it4->first;
        thirdPlace.push_back(t4);
    }

    srand(static_cast<unsigned>(time(nullptr)));
    int index = rand() % 2;
    std::cout << " THIRD PLACE:" << '\n' << " " << thirdPlace[index] << '\n';

    champions.insert(std::make_pair(it->first, it->second));

    std::cout << '\n' << " WORLD CHAMPIONSHIP:" << '\n';
    std::map<std::string, double> champion{ playMatch(champions, 1) };
    std::cout << '\n';

    return 0;
}
