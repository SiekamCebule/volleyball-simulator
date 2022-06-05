#pragma once
#include <array>
#include <vector>
#include "Team.h"

class Match
{
private:
    std::array<Team, 2> teams;

    void simulatePoint();
    bool isWinner();
    int set;

public:
    Match();
    Match(const Team &tm1, const Team &tm2);
    ~Match();

    const Team &getTeam(const int &n) const { return teams[n]; }

    void setTeam(const Team &team, const int &n);
    void startMatch();
};