#include "crewmember.hpp"

CrewMember::CrewMember(std::string first, std::string last,
                       float training, int aptitude, unsigned int id)
{
    first_name = first;  
    last_name = last;    

    try {                //validate numeric fields
        setTrainingScore(training);
        setMissionAptitude(aptitude);
        setId(id);
    } catch (const std::invalid_argument& e) {
        throw;           //sends error message to caller if invalid
    }
}

void CrewMember::setFirstName(const std::string& fn) {
    if (fn.empty()) throw std::invalid_argument("first name empty"); // check
    first_name = fn; // set
}

void CrewMember::setLastName(const std::string& ln) {
    if (ln.empty()) throw std::invalid_argument("last name empty"); //check
    last_name = ln; // set
}

void CrewMember::setTrainingScore(float score) {
    if (score < 0.0f || score > 4.3f) {
        throw std::invalid_argument("training_score out of range"); //check
    }
    training_score = score; // set
}

void CrewMember::setMissionAptitude(int aptitude) {
    if (aptitude < 0 || aptitude > 100) {
        throw std::invalid_argument("mission_aptitude out of range"); //check0
    }
    mission_aptitude = aptitude; // set
}

void CrewMember::setId(unsigned int id) {
    if (id < 25220000 || id > 99999999) {
        throw std::invalid_argument("id invalid"); //check
    }
    id_number = id; // set
}

bool CrewMember::operator>(const CrewMember& other) const {
    if (mission_aptitude > other.mission_aptitude) {
        return true;
    } else if (mission_aptitude == other.mission_aptitude) {
        if (training_score > other.training_score) {
            return true;
        }
    }
}