#pragma once
#define choiceString cout << "Wyb¢r: "
#define cls system("cls")

#include <vector>
#include "Team.h"
#include "Match.h"
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

class App
{
private:
    friend class boost::serialization::access;
    Match match;

    // choices
    void simulateMatchChoice();
    void teamsChoice();
    void settingsChoice();

    // match
    void choiceTeams();
    void choiceShowResults();

    // team editor
    enum class OperationType
    {
        Edit,
        Delete
    };
    const Team askForTeam();
    int askForTeamIndex(const OperationType &type);
    void addTeam(const Team &team);
    void editTeam(const Team &team, const int &n);
    void deleteTeam(const int &n);

    std::vector<Team> teams;
    void sortTeams();
    bool loadTeams();
    bool saveTeams();
    void showTeams();

    bool isAutoTeamSorting;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version)
    {
        ar & isAutoTeamSorting;
        ar & match;
    }

    //config.cfg
    void saveConfig();
    void loadConfig();
    bool isConfigFileEmpty();

public:
    App();
    void start();
};