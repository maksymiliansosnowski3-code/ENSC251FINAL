#ifndef HUMANCREW_HPP
#define HUMANCREW_HPP

#include "crewmember.hpp"

class HumanCrew : public CrewMember {
public:
    HumanCrew() = default; //default object

    HumanCrew(std::string fn, std::string ln,
              float ts, int apt, unsigned int id,
              std::string sector); //full constructor

    std::string getHomeSector() const { return home_sector; } //observer
    void setHomeSector(const std::string& sec); //sets after checking non-empty

    friend std::ostream& operator<<(std::ostream& os, const HumanCrew& h) {
}

private:
    std::string home_sector = "Unknown"; //data
};

#endif
