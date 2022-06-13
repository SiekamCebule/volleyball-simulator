#include "App.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include <conio.h>
#include <algorithm>

using std::cin;
using std::cout;
using std::getline;
using std::string;

App::App()
{
    loadConfig();
}

void App::start()
{
    if (!loadTeams())
        exit(0);
    while (true)
    {
        int choice = 0;
        while (!(choice >= 1 && choice <= 3))
        {
            cout << "Witaj w symulatorze siatk¢wki! Wybierz jedn¥ z opcji:\n";
            cout << "1. Symuluj mecz\n2. Dru¾yny\n3. Ustawienia\n";
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
            teamsChoice();
            break;
        case 3:
            settingsChoice();
            break;
        }
    }
}

void App::simulateMatchChoice()
{
    choiceTeams();
    choiceShowResults();
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

void App::teamsChoice()
{
    char ch;
    showTeams();
    cout << "\nCo chcesz zrobi†?\n1. Dodaj dru¾yn©\n2. Edytuj dru¾yn©\n3. Usuä dru¾yn©\n4. Wr¢†\n";
    ch = getch() - '0';
    switch (ch)
    {
    case 1:
        addTeam(askForTeam());
        break;
    case 2:
        editTeam(askForTeam(), askForTeamIndex(OperationType::Edit) - 1);
        break;
    case 3:
        deleteTeam(askForTeamIndex(OperationType::Delete) - 1);
        break;
    case 4:
        break;
    default:
        break;
    }
    saveTeams();
    sortTeams();
    Sleep(1050);
    system("cls");
}

void App::settingsChoice()
{
    char ch;
    cout << "Ustawienia: (1 = tak)\n\n";
    cout << "\nZapisywanie wynik¢w mecz¢w: " << match.getIsSaveMatches();
    cout << "\nAutomatyczne sortowanie dru¾yn: " << isAutoTeamSorting;

    cout << "\n1. Wˆ¥cz/Wyˆ¥cz zapisywanie wynik¢w mecz¢w\n";
    cout << "2. Wˆ¥cz/Wyˆ¥cz automatyczne sortowanie dru¾yn\n";
    cout << "3. Wczytaj dru¾yny z pliku\n";
    cout << "4. Wr¢†\n";

    cout << "\n";
    choiceString;
    ch = getch() - '0';

    switch (ch)
    {
    case 1:
        if (!match.getIsSaveMatches())
        {
            match.setIsSaveMatches(true);
            cout << "\nWˆ¥czono zapisywanie wynik¢w mecz¢w.\n";
        }
        else
        {
            match.setIsSaveMatches(false);
            cout << "\nWyˆ¥czono zapisywanie wynik¢w mecz¢w.\n";
        }
        break;
    case 2:
        if (!isAutoTeamSorting)
        {
            isAutoTeamSorting = true;
            cout << "Wˆ¥czono automatyczne sortowanie dru¾yn.\n";
        }
        else
        {
            isAutoTeamSorting = false;
            cout << "Wyˆ¥czono automatyczne sortowanie dru¾yn.\n";
        }
    case 3:
        if (loadTeams())
            cout << "Wczytano dru¾yny!";
        break;
    case 4:
        break;
    }
    saveConfig();
    Sleep(500);
    system("cls");
}

void App::choiceShowResults()
{
    int res;
    cout << "Czy pokazywa† wyniki? Je˜li nie, wpisz 0. W przeciwnym wypadku kliknij dowolny przycisk";
    res = getch() - '0';

    if (res == 0)
        match.setIsShowResults(res);
    else
        match.setIsShowResults(true);

    cout << "\nOK.\n";
    Sleep(200);
    system("cls");
}

const Team App::askForTeam()
{
    string name;
    string skill;
    cin.ignore();
    cin.sync();

    cout << "Podaj nazw© dru¾yny: ";
    getline(cin, name);
    cout << "Podaj umiej©tno˜ci dru¾yny: ";
    getline(cin, skill);

    return Team(name, stoi(skill));
}

int App::askForTeamIndex(const OperationType &type)
{
    int n;
    if (type == OperationType::Delete)
        cout << "Kt¢r¥ dru¾yn© chcesz usun¥†?\n";
    else if (type == OperationType::Edit)
        cout << "Kt¢r¥ dru¾yn© chcesz edytowa†?\n";
    choiceString;
    cin >> n;

    return n;
}

void App::addTeam(const Team &team)
{
    teams.push_back(team);
    cout << "Dodano dru¾yn© " << team << ".\n";
}

void App::editTeam(const Team &team, const int &n)
{
    cout << "Edytowano dru¾yn© " << teams[n];
    teams[n] = team;
    cout << " na " << team << ".\n";
}

void App::deleteTeam(const int &n)
{
    cout << "Usuni©to dru¾yn© " << teams[n] << ".\n";
    teams.erase(teams.begin() + n);
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

void App::sortTeams()
{
    std::sort(teams.begin(), teams.end(), std::greater<Team>());
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
    teams.erase(teams.begin(), teams.end());
    while (getline(ifs, name, ','))
    {
        getline(ifs, skill);
        teams.push_back(Team(name, std::stoi(skill)));
    }
    ifs.close();
    if (isAutoTeamSorting)
        sortTeams();
    return true;
}

bool App::saveTeams()
{
    std::ofstream ofs;
    ofs.open("teams.csv");
    if (ofs.good() == false)
    {
        cout << "Nie mo¾na zapisa† danych w pliku teams.csv!\n";
        return false;
    }
    for (const auto &team : teams)
    {
        ofs << team.getName() << "," << team.getSkill() << "\n";
    }
    ofs.close();
    return true;
}

void App::saveConfig()
{
    std::ofstream ofs("config.cfg");
    boost::archive::text_oarchive oa(ofs);
    oa << *this;
}

void App::loadConfig()
{
    if (!isConfigFileEmpty())
    {
        std::ifstream ifs("config.cfg");
        boost::archive::text_iarchive ia(ifs);
        ia >> *this;
    }
}

bool App::isConfigFileEmpty()
{
    std::ifstream ifs("config.cfg");
    return ifs.peek() == std::ifstream::traits_type::eof();
}