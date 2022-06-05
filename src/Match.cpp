#include "Match.h"
#include "Random.h"
#include <conio.h>
#include <Windows.h>
using std::cout;

Match::Match()
{
    set = 1;
}

Match::Match(const Team &tm1 = Team(), const Team &tm2 = Team())
{
    teams[0] = tm1;
    teams[1] = tm2;

    set = 1;
}

Match::~Match()
{
}

void Match::startMatch()
{
    while (!isWinner())
    {
        cout << teams[0].getName() << "  (" << teams[0].getPoints() << ")  -  ";
        cout << "(" << teams[1].getPoints() << ")  " << teams[1].getName() << "\n";

        simulatePoint();
        cout << "\nSet " << set << "\n";
        getch();
        Sleep(150);
        system("cls");
    }
}

void Match::setTeam(const Team &team, const int &n)
{
    teams[n] = team;
}

// kiedy wygrywa druzyna 2, wywala bˆ¥d
bool Match::isWinner()
{
    int pointsToWin;
    Team *opposite = &teams[1];

    if (set != 5)
        pointsToWin = 25;
    else
        pointsToWin = 15;

    if ((teams[0].getPoints() == 25) && ((teams[0].getPoints() - 1) > opposite->getPoints()))
        return true;
    else if ((opposite->getPoints() == 25) && ((opposite->getPoints() - 1) > teams[0].getPoints()))
        return true;
    else
        return false;
}

void Match::simulatePoint()
{
    int rd = 0;
    int skillSum = 0;
    for (const auto &team : teams)
        skillSum += team.getSkill();

    rd = randomInt(0, skillSum);

    if (rd <= teams[0].getSkill())
    {
        teams[0].addPoint();
        cout << "[" << teams[0].getName() << "] Zdobyto punkt!\n";
    }
    else
    {
        teams[1].addPoint();
        cout << "[" << teams[1].getName() << "] Zdobyto punkt!\n";
    }

    // cout << teams[0].getName()<<" "<<teams[0].getPoints()<<"\n";
    // cout << teams[1].getName() << " " << teams[1].getPoints() << "\n";
}