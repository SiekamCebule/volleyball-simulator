#include "Team.h"

Team::Team(const std::string &name_, const short &skill_)
{
    name = name_;
    skill = skill_;
    points = 0;
}

Team::~Team()
{
}

std::ostream &operator<<(std::ostream &os, const Team &team)
{
    os << team.name << " (" << team.skill << ")";
    return os;
}

void Team::setSkill(const int &arg)
{
    skill = arg;
}

void Team::setPoints(const int &arg)
{
    points = arg;
}

void Team::updatePointsData(const int &set)
{

    if (pointsData.size() < set)
        pointsData.push_back(points);
    else
        pointsData[set - 1] = points;
}