#ifndef CREWSORT_HPP
#define CREWSORT_HPP
#include <iostream>
#include <string>
#include <vector>
#include "aliencrew.hpp"
#include "humancrew.hpp"

using namespace std;

class CrewSort {
    public:
        void sortHighToLow(std::vector<double>& keys, std::vector<size_t>& idx);
        void sortAToZ(std::vector<std::string>& keys, std::vector<size_t>& idx); 
        vector<HumanCrew> overallSortHumans(const std::vector<HumanCrew>& input);
        vector<AlienCrew> overallSortAliens(const std::vector<AlienCrew>& input);
    private:
        // helper functions to help rank individuals in each recruit category 
        bool betterHuman(const HumanCrew& human1, const HumanCrew& human2);
        bool betterAlien(const AlienCrew& alien1, const AlienCrew& alien2);
};

#endif