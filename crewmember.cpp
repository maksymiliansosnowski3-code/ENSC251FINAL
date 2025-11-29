#include "crewmember.hpp"

CrewMember::CrewMember(std::string first, std::string last,
                       float training, int aptitude, unsigned int id)
{
    first_name = first;
    last_name  = last;

    try {
        setTrainingScore(training);
        setMissionAptitude(aptitude);
        setId(id);
    } catch (const std::invalid_argument& e) {
        throw;
    }
} 

void CrewMember::setFirstName(const std::string& fn) {
    if (fn.empty()) throw std::invalid_argument("first name empty");
    first_name = fn;
}

void CrewMember::setLastName(const std::string& ln) {
    if (ln.empty()) throw std::invalid_argument("last name empty");
    last_name = ln;
}

void CrewMember::setTrainingScore(float score) {
    if (score < 0.0f || score > 4.3f) {
        throw std::invalid_argument("training_score out of range");
    }
    training_score = score;
}

void CrewMember::setMissionAptitude(int aptitude) {
    if (aptitude < 0 || aptitude > 100) {
        throw std::invalid_argument("mission_aptitude out of range");
    }
    mission_aptitude = aptitude;
}

void CrewMember::setId(unsigned int id) {
    if (id < 25220000 || id > 99999999) {
        throw std::invalid_argument("id invalid");
    }
    id_number = id;
}

bool CrewMember::operator>(const CrewMember& other) const {
    if (mission_aptitude > other.mission_aptitude)
        return true;
    if (mission_aptitude < other.mission_aptitude)
        return false;

    if (training_score > other.training_score)
        return true;
    if (training_score < other.training_score)
        return false;

    return false;
}
