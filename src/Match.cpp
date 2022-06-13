#include "Match.h"
#include "Random.h"
#include <conio.h>
#include <Windows.h>
#include "date/date.h"
#include <fstream>
using std::cout;
using std::string;

Match::Match()
{
    set = 1;
    isShowResults = true;
}

Match::Match(const Team &tm1 = Team(), const Team &tm2 = Team())
{
    teams[0] = tm1;
    teams[1] = tm2;

    set = 1;
    isShowResults = true;
}

Match::~Match()
{
}

void Match::startMatch()
{
    set = 1;
    while (!isMatchWinner())
    {
        for (auto &team : teams)
        {
            team.setPoints(0);
            for (auto &team : teams)
                team.setSkill(randomInt(team.getSkill() - 1, team.getSkill() + 1));
        }

        if (isShowResults)
        {
            while (!isSetWinner())
            {
                showTeamsHeader();

                Team *winner;
                winner = simulatePoint();
                showPointWinner(winner);

                for (auto &team : teams)
                    team.updatePointsData(set);
                showActualResults();

                getch();
                Sleep(150);
                system("cls");
            }

            cout << "Koniec setu nr " << set << ".\n";
            if (!isMatchWinner())
            {
                set++;
                cout << "Zaczynam set nr " << set << ".\n";
            }
        }
        else
        {
            while (!isSetWinner())
            {
                simulatePoint();
                for (auto &team : teams)
                    team.updatePointsData(set);
            }
            if (!isMatchWinner())
                set++;
        }

        if (isMatchWinner())
        {
            system("cls");
            cout << "Koniec meczu! Wygrywa dru¾yna --> " << matchWinner()->getName() << "\n";
            showActualResults();
            cout << "\n\nWci˜nij dowolny przycisk aby przej˜† do menu: ";
            if (isSaveMatches)
                saveMatchResultsToFile();
            getch();
            system("cls");
        }
    }
}

void Match::setTeam(const Team &team, const int &n)
{
    teams[n] = team;
}

bool Match::isSetWinner()
{
    int pointsToWin;
    Team *opposite = &teams[1];

    if (set != 5)
        pointsToWin = 25;
    else
        pointsToWin = 15;

    if ((teams[0].getPoints() >= pointsToWin) && ((teams[0].getPoints() - 1) > opposite->getPoints()))
    {
        teams[0].addSet();
        return true;
    }
    else if ((opposite->getPoints() >= pointsToWin) && ((opposite->getPoints() - 1) > teams[0].getPoints()))
    {
        opposite->addSet();
        return true;
    }
    else
        return false;
}

bool Match::isMatchWinner()
{
    if (teams[0].getSets() == 3 || teams[1].getSets() == 3)
        return true;
    else
        return false;
}

void Match::showTeamsHeader()
{
    cout << teams[0].getName() << "  (" << teams[0].getPoints() << ")  -  ";
    cout << "(" << teams[1].getPoints() << ")  " << teams[1].getName() << " (Set " << set << ")"
         << "\n\n";
}

void Match::showPointWinner(Team *winner)
{
    cout << "[" << winner->getName() << "] Zdobyto punkt!\n\n\n";
}

void Match::showActualResults()
{
    for (int i = 0; i < 2; i++)
    {
        cout << teams[i].getName() << ": |";
        for (int ii = 0; ii < teams[i].getPointsData().size(); ii++)
        {
            cout << teams[i].getPointsData()[ii] << "|";
        }
        cout << "  Sety: " << teams[i].getSets() << "|";
        cout << "\n";
    }
}

Team *Match::simulatePoint()
{
    int rd = 0;
    int skillSum = 0;
    for (const auto &team : teams)
        skillSum += team.getSkill();

    Team *winner;

    rd = randomInt(0, skillSum);

    if (rd <= teams[0].getSkill())
    {
        winner = &teams[0];
    }
    else
    {
        winner = &teams[1];
    }
    winner->addPoint();
    return winner;
}

const Team *Match::matchWinner()
{
    if (teams[0].getSets() > teams[1].getSets())
        return &teams[0];
    else
        return &teams[1];
}

void Match::saveMatchResultsToFile()
{
    string filename = "results/";

    string temp = "";
    for (int i = 0; i < 2; i++)
    {
        int len = getTeam(i).getName().length();
        if (len >= 3)
            temp += getTeam(i).getName().substr(0, 3);
        else
            temp += getTeam(i).getName().substr(0, len);
        temp += "-";
    }

    auto now = date::floor<std::chrono::minutes>(std::chrono::system_clock::now());
    auto dp = date::floor<date::days>(now);
    auto time = date::make_time(now - dp);
    int hours = time.hours().count();
    int minutes = time.minutes().count();

    temp += std::to_string(hours + 3) + "-";
    temp += std::to_string(minutes);

    filename += temp + ".txt";

    std::ofstream ofs;
    ofs.open(filename);

    for (const auto &team : teams)
    {
        ofs << team.getName() << ": |";
        for (int ii = 0; ii < team.getPointsData().size(); ii++)
        {
            ofs << team.getPointsData()[ii] << "|";
        }
        ofs << "  Sety: " << team.getSets() << "|";
        ofs << "\n";
    }
}