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
    set = 1;
    while (!isMatchWinner())
    {
        for (auto &team : teams)
        {
            team.setPoints(0);
            for (auto &team : teams)
                team.setSkill(randomInt(team.getSkill() - 1, team.getSkill() + 1));
        }

        while (!isSetWinner())
        {
            const Team *winner;
            cout << teams[0].getName() << "  (" << teams[0].getPoints() << ")  -  ";
            cout << "(" << teams[1].getPoints() << ")  " << teams[1].getName() << " (Set " << set << ")"
                 << "\n\n";

            winner = simulatePoint();
            cout << "[" << winner->getName() << "] Zdobyto punkt!\n\n\n";

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
        if (isMatchWinner())
        {
            system("cls");
            cout << "Koniec meczu! Wygrywa dru¾yna --> " << matchWinner()->getName() << "\n";
            showActualResults();
            cout << "\n\nWci˜nij dowolny przycisk aby przej˜† do menu: ";
            getch();
            system("cls");
        }
    }
}

void Match::setTeam(const Team &team, const int &n)
{
    teams[n] = team;
}

// kiedy wygrywa druzyna 2, wywala bˆ¥d
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

const Team *Match::simulatePoint()
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