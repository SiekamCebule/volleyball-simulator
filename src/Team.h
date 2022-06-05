#pragma once
#include <string>
#include <iostream>

class Team
{
private:
    std::string name;
    short skill;

    short points;
    short sets;

public:
    Team(const std::string &name_ = "", const short &skill_ = 0);
    ~Team();

    std::string getName() const { return name; }
    short getSkill() const { return skill; }
    short getPoints() const { return points; }
    short getSets() const { return sets; }
    void addPoint() { points++; }

    friend std::ostream &operator<<(std::ostream &os, const Team &team);
    inline bool operator>(const Team &team) const { return skill > team.skill; }
};