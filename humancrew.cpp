#include "humancrew.hpp"

HumanCrew::HumanCrew(std::string fn, std::string ln,
                     float ts, int apt, unsigned int id,
                     std::string sector)
    : CrewMember(fn, ln, ts, apt, id), home_sector(sector) {}

void HumanCrew::setHomeSector(const std::string& sec) {
    if (sec.empty()) throw std::invalid_argument("Home sector cannot be empty.");
    home_sector = sec;
}

std::ostream& operator<<(std::ostream& os, const HumanCrew& h) {
    os << h.getFirstName() << " " << h.getLastName()
       << " | Sector: " << h.home_sector
       << " | Training: " << h.getTrainingScore()
       << " | Aptitude: " << h.getMissionAptitude();
    return os;
}
