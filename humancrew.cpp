#include "humancrew.hpp"
#include <stdexcept> 
#include <iostream>
#include <fstream>

HumanCrew::HumanCrew(std::string fn, std::string ln,
                     float ts, int apt, unsigned int id,
                     std::string sector)
{
    //initialize base fields via base setters
    try {
        setFirstName(fn);
        setLastName(ln);
        setTrainingScore(ts);
        setMissionAptitude(apt);
        setId(id);
    } catch (const std::invalid_argument& e) {
        throw; //throw (error) if any validation fails
    }

    setHomeSector(sector);
}

void HumanCrew::setHomeSector(const std::string& sec) {
    if (sec.empty()) throw std::invalid_argument("home_sector empty"); //check
    home_sector = sec; //set
}

std::ostream& operator<<(std::ostream& os, const HumanCrew& h) {
    os << "Human Crew Member\n"
       << "-----------------\n"
       << "Name: " << h.getFirstName() << " " << h.getLastName() << "\n"
       << "Training Score: " << h.getTrainingScore() << "\n"
       << "Mission Aptitude: " << h.getMissionAptitude() << "\n"
       << "ID: " << h.getId() << "\n"
       << "Home Sector: " << h.getHomeSector();
    return os;
}
