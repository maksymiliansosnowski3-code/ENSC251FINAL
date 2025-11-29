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
              TelepathicLinkTest t); //full constructor

    std::string getHomeworld() const { return homeworld; } //observer
    void setHomeworld(const std::string& w); //sets after checking non-empty

    TelepathicLinkTest getTelepathicLinkTest() const { return ttest; } //observer 
    void setTelepathicLinkTest(const TelepathicLinkTest& t) { ttest = t; } //set 
    friend std::ostream& operator<<(std::ostream& os, const AlienCrew& a);

private:
    std::string homeworld = "Unknown"; //data
    TelepathicLinkTest ttest; //telepathic results for this alien
};

#endif
