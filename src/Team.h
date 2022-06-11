#pragma once
#include <string>
#include <iostream>
#include <vector>

class Team
{
private:
    std::string name;
    short skill;

    short points;
    short sets;

    std::vector<int> pointsData;

public:
    Team(const std::string &name_ = "", const short &skill_ = 0);
    ~Team();

    std::string getName() const { return name; }
    short getSkill() const { return skill; }
    short getPoints() const { return points; }
    short getSets() const { return sets; }
    const std::vector<int> &getPointsData() { return pointsData; }

    void addPoint() { points++; }
    void addSet() {sets++;}
    void setSkill(const int &arg);
    void setPoints(const int &arg);
    void updatePointsData(const int & set);

    friend std::ostream &operator<<(std::ostream &os, const Team &team);
    inline bool operator>(const Team &team) const { return skill > team.skill; }
};