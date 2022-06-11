#include "App.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>

using std::cin;
using std::cout;
using std::getline;
using std::string;

App::App()
{
}

void App::start()
{
    while (true)
    {
        if (!loadTeams())
            break;
        int choice = 0;
        while (!(choice >= 1 && choice <= 3))
        {
            cout << "Witaj w symulatorze siatk¢wki! Wybierz jedn¥ z opcji:\n";
            cout << "1. Symuluj mecz\n2. Dru¾yny (niedost©pne)\n3. Ustawienia (niedost©pne)\n";
            choiceString;
            cin >> choice;
            cls;
        }

        switch (choice)
        {
        case 1:
            simulateMatchChoice();
            break;
        case 2:
            // teamsChoice();
            break;
        case 3:
            // saveLoadChoice();
            break;
        }
    }
    exit(0);
}

void App::simulateMatchChoice()
{
    choiceTeams();
    match.startMatch();
}

void App::choiceTeams()
{
    int n = 0;
    for (int i = 1; i <= 2; i++)
    {
        cout << "Wybierz dru¾yn© nr " << i << ":\n\n";
        showTeams();
        choiceString;
        cin >> n;
        match.setTeam(teams[n - 1], i - 1);
        cls;
    }

    cout << "Wybrane dru¾yny to " << match.getTeam(0).getName() << " i " << match.getTeam(1).getName() << "\n";
    Sleep(700);
    cls;
}

void App::showTeams()
{
    int i = 1;
    for (const auto &team : teams)
    {
        cout << i << ". " << team.getName() << " (" << team.getSkill() << ")\n";
        i++;
    }
}

bool App::loadTeams()
{
    string name;
    string skill;
    std::ifstream ifs;
    ifs.open("teams.csv");
    if (ifs.good() == false)
    {
        cout << "Nie mo¾na otworzy† pliku teams.csv!\n";
        Sleep(1400);
        return false;
    }
    while (getline(ifs, name, ','))
    {
        getline(ifs, skill);
        teams.push_back(Team(name, std::stoi(skill)));
    }
    return true;
}