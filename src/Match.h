#pragma once
#include <array>
#include <vector>
#include "Team.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class Match
{
private:
    friend class boost::serialization::access;
    std::array<Team, 2> teams;

    Team *simulatePoint();
    const Team *matchWinner();
    bool isSetWinner();
    bool isMatchWinner();
    void showTeamsHeader();
    void showPointWinner(Team *winner);
    void showActualResults();
    int set;
    bool isShowResults;
    bool isSaveMatches;

    void saveMatchResultsToFile();

    template <class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar &isSaveMatches;
    }

public:
    Match();
    Match(const Team &tm1, const Team &tm2);
    ~Match();

    const Team &getTeam(const int &n) const { return teams[n]; }
    const std::array<Team, 2> &getTeamsArray() const { return teams; }
    bool getIsSaveMatches() const { return isSaveMatches; }
    void setIsSaveMatches(const bool &arg) { isSaveMatches = arg; }

    void setTeam(const Team &team, const int &n);
    void setIsShowResults(const bool &arg) { isShowResults = arg; }
    void startMatch();
};