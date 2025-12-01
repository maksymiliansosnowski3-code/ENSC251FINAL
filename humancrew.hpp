#ifndef HUMANCREW_HPP
#define HUMANCREW_HPP

#include "crewmember.hpp"

class HumanCrew : public CrewMember {
public:
    // default constructor
    HumanCrew() = default;

    // constructor for initialziing parameters 
    HumanCrew(std::string fn, std::string ln,
              float ts, int apt, unsigned int id,
              std::string sector);

    // getter and setter for home sector
    std::string getHomeSector() const { return home_sector; }
    void setHomeSector(const std::string& sec);

    // overload the output operator
    friend std::ostream& operator<<(std::ostream& os, const HumanCrew& h);

private:
    std::string home_sector = "Unknown";
};

#endif
