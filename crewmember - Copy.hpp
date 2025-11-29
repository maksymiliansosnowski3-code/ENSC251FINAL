#ifndef CREWMEMBER_HPP
#define CREWMEMBER_HPP

#include <string>     
#include <iostream>   
#include <stdexcept>  

class CrewMember {
public:
    CrewMember() = default; 

    CrewMember(std::string first, std::string last,
               float training, int aptitude, unsigned int id); //full constructor
    
    //observers
    std::string getFirstName() const { return first_name; } 
    std::string getLastName() const { return last_name; }   
    float getTrainingScore() const { return training_score; } 
    int getMissionAptitude() const { return mission_aptitude; } 
    unsigned int getId() const { return id_number; } 

    void setFirstName(const std::string& fn);     //sets after checking non-empty
    void setLastName(const std::string& ln);      //sets after checking non-empty
    void setTrainingScore(float score);           //sets after checking 0.0–4.3
    void setMissionAptitude(int aptitude);        //sets after checking 0–100
    void setId(unsigned int id);                  //sets after checking 8-digit >= 25220000


    bool operator>(const CrewMember& other) const;

private:
    std::string first_name;            //data: first name
    std::string last_name;             //data: last name
    float       training_score = 0.0f; //data: training score
    int         mission_aptitude = 0;  //data: aptitude
    unsigned int id_number = 25220000; //data: id no.
};

#endif
