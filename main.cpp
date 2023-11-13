#include <iostream>
#include <random>
#include "io.h"

// randInt selects a random number from a range
int randInt()
{
    std::random_device rd;
    std::seed_seq ss{ rd(), rd(), rd(), rd(), rd(), rd(), rd(), rd() };
    std::mt19937 mt{ ss };
    std::uniform_int_distribution<int> range{ 1, 2 };

    return range(mt);
}

// selectWinner selects the winner of the match
std::string selectWinner(std::string team1, std::string team2)
{
    std::vector<std::string> teams{ team1, team2 };
    std::random_device rd; 
    std::mt19937 mt(rd());
    std::uniform_int_distribution<> distr(0, teams.size() - 1);

    return teams[distr(mt)];
}

// playMatch
std::vector<std::string> playMatch(std::vector<std::string> teams, int count)
{
    std::vector<std::string> winners;
    for (int i = 0; i < count; i+=2)
    {
        std::cout << " " << teams[i] << " -- VS -- " << teams[i+1] << '\n';
        std::string winner{ selectWinner(teams[i], teams[i+1]) };
        winners.push_back(winner);
    }
    return winners;
}

// printWinner prints elements from the winners vector
void printWinner(std::vector<std::string> winners)
{
    std::cout << " Winners:" << '\n';
    for (auto& team: winners)
        std::cout << " " << team << '\n';
    std::cout << '\n';
}

int main()
{
    std::vector<std::string> group1{ openFile("group1.txt") };
    std::vector<std::string> group2{ openFile("group2.txt") };

    std::cout << '\n';
    std::cout << " Round Of Sixteen:" << '\n';
    std::vector<std::string> playMatchOfSixteen1{ playMatch(group1, 16) };
    std::vector<std::string> playMatchOfSixteen2{ playMatch(group2, 16) };

    std::cout << '\n';
    printWinner(playMatchOfSixteen1);
    
    std::cout << " Semi Final:" << '\n';
    std::vector<std::string> semiFinal1{ playMatch(playMatchOfSixteen1, 8) };
    std::vector<std::string> semiFinal2{ playMatch(playMatchOfSixteen2, 8) };

    std::cout << '\n';
    printWinner(semiFinal1);
    printWinner(semiFinal2);

    std::cout << " Quarter Final:" << '\n';
    std::vector<std::string> quarterFinal1{ playMatch(semiFinal1, 4) };
    std::vector<std::string> quarterFinal2{ playMatch(semiFinal2, 4) };

    std::cout << '\n';
    printWinner(quarterFinal1);
    printWinner(quarterFinal2);

    std::cout << " Finals:" << '\n';
    std::vector<std::string> final1{ playMatch(quarterFinal1, 2) };
    std::vector<std::string> final2{ playMatch(quarterFinal2, 2) };

    std::cout << '\n';
    printWinner(final1);
    printWinner(final2);

    std::cout << " World Champion:" << '\n';
    std::string champ1 = final1[0];
    std::string champ2 = final2[0];

    std::string champion{ selectWinner(champ1, champ2) };
    std::cout << " " << champion << '\n';

    return 0;
}
