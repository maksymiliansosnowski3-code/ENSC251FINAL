#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include <string>
#include <iostream>
#include <stdexcept>

class CrewMember {
public:
    CrewMember() = default;

    CrewMember(std::string first, std::string last,
               float training, int aptitude, unsigned int id);

    // getters
    std::string getFirstName() const { return first_name; }
    std::string getLastName() const { return last_name; }
    float getTrainingScore() const { return training_score; }
    int getMissionAptitude() const { return mission_aptitude; }
    unsigned int getId() const { return id_number; }

    // setters
    void setFirstName(const std::string& fn);
    void setLastName(const std::string& ln);
    void setTrainingScore(float score);
    void setMissionAptitude(int aptitude);
    void setId(unsigned int id);

    // overload comparison operator

    bool operator>(const CrewMember& other) const;

private:
    // member variables
    std::string first_name;
    std::string last_name;
    float training_score = 0.0f;
    int mission_aptitude = 0;
    unsigned int id_number = 25220000;
};

#endif
