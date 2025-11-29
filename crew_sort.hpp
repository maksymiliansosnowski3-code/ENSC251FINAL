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
    static void sortHighToLow(std::vector<double>& keys, std::vector<size_t>& idx);
    static void sortAToZ(std::vector<std::string>& keys, std::vector<size_t>& idx);
    static void sortHighToLow(std::vector<double>& keys);
    static void sortAToZ(std::vector<std::string>& keys);
    static vector<HumanCrew> overallSortHumans(const std::vector<HumanCrew>& input);
    static vector<AlienCrew> overallSortAliens(const std::vector<AlienCrew>& input);
private:
    static bool betterHuman(const HumanCrew& human1, const HumanCrew& human2);
    static bool betterAlien(const AlienCrew& alien1, const AlienCrew& alien2);
};

#endif
