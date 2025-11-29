#ifndef HUMANCREW_HPP
#define HUMANCREW_HPP

#include "crewmember.hpp"

class HumanCrew : public CrewMember {
public:
    HumanCrew() = default;

    HumanCrew(std::string fn, std::string ln,
              float ts, int apt, unsigned int id,
              std::string sector);

    std::string getHomeSector() const { return home_sector; }
    void setHomeSector(const std::string& sec);

    friend std::ostream& operator<<(std::ostream& os, const HumanCrew& h);

private:
    std::string home_sector = "Unknown";
};

#endif
