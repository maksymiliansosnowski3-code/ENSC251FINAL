#ifndef ALIENCREW_HPP
#define ALIENCREW_HPP

#include "crewmember.hpp"
#include "telepathiclinktest.hpp"
#include <iostream>

class AlienCrew : public CrewMember {
public:
    AlienCrew() = default;

    AlienCrew(std::string fn, std::string ln,
              float ts, int apt, unsigned int id,
              std::string world,
              TelepathicLinkTest t);

    std::string getHomeworld() const { return homeworld; }
    void setHomeworld(const std::string& w);

    TelepathicLinkTest getTelepathicLinkTest() const { return ttest; }
    void setTelepathicLinkTest(const TelepathicLinkTest& t) { ttest = t; }

    friend std::ostream& operator<<(std::ostream& os, const AlienCrew& a);

private:
    std::string homeworld = "Unknown";
    TelepathicLinkTest ttest;
};

#endif
