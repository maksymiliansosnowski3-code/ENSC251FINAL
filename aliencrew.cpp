#include "aliencrew.hpp"

AlienCrew::AlienCrew(std::string fn, std::string ln,
                     float ts, int apt, unsigned int id,
                     std::string world,
                     TelepathicLinkTest t)
    : CrewMember(fn, ln, ts, apt, id),
      homeworld(world), ttest(t) {}

void AlienCrew::setHomeworld(const std::string& w) {
    if (w.empty()) throw std::invalid_argument("Homeworld cannot be empty.");
    homeworld = w;
}

std::ostream& operator<<(std::ostream& os, const AlienCrew& a) {
    os << a.getFirstName() << " " << a.getLastName()
       << " | Homeworld: " << a.homeworld
       << " | Training: " << a.getTrainingScore()
       << " | Aptitude: " << a.getMissionAptitude()
       << " | TLT Total: " << a.ttest.getTotal();
    return os;
}
