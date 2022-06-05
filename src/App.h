#pragma once
#define choiceString cout << "Wyb¢r: "
#define cls system("cls")

#include <vector>
#include "Team.h"
#include "Match.h"

class App
{
private:
    Match match;

    // choices
    void simulateMatchChoice();
    void teamsChoice();
    void saveLoadChoice();

    // match
    void choiceTeams();

    std::vector<Team> teams;
    void loadTeams();
    void showTeams();

public:
    App();
    void start();
};