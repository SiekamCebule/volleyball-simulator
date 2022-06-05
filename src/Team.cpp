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