#include <iostream>
#include <string>
#include <vector>
#include "aliencrew.hpp"
#include "humancrew.hpp"

using namespace std;

void CrewSort::sortHighToLow(vector<double>& keys, vector<size_t>& idx) {
    // Insertion sort on numeric keys, descending, move idx with keys
    for (int i = 0; i < (int)keys.size(); i++) {
        double kVal   = keys[i];
        size_t idVal  = idx[i];
        int j = i - 1;

        while (j >= 0 && keys[j] < kVal) {
            keys[j + 1] = keys[j];
            idx[j + 1]  = idx[j];
            j--;
        }
        keys[j + 1] = kVal;
        idx[j + 1]  = idVal;
    }
}

void CrewSort::sortAToZ(vector<string>& keys, vector<size_t>& idx) {
    // Insertion sort on string keys, ascending (A->Z), move idx with keys
    for (int i = 0; i < (int)keys.size(); i++) {
        string kVal   = keys[i];
        size_t idVal  = idx[i];
        int j = i - 1;

        while (j >= 0 && keys[j] > kVal) {
            keys[j + 1] = keys[j];
            idx[j + 1]  = idx[j];
            j--;
        }
        keys[j + 1] = kVal;
        idx[j + 1]  = idVal;
    }
}

// ================= OVERALL SORT: HUMANS =================
// Order: MissionAptitude ↓, TrainingScore ↓, HomeSector A->Z

vector<HumanCrew> CrewSort::overallSortHumans(const vector<humanCrew>& input) {
    vector<size_t> idx(input.size());
    for (size_t i = 0; i < idx.size(); i++) {
        idx[i] = i;               // start with original order
    }

    // Pass 1 — lowest priority: HomeSector A->Z
    {
        vector<string> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++) {
            keys[k] = input[idx[k]].getHomeSector();
        }
        CrewSort::sortAToZ(keys, idx);
    }

    // Pass 2 — middle: TrainingScore high->low
    {
        vector<double> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++) {
            keys[k] = input[idx[k]].getTrainingScore();
        }
        CrewSort::sortHighToLow(keys, idx);
    }

    // Pass 3 — highest: MissionAptitude high->low
    {
        vector<double> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++) {
            keys[k] = input[idx[k]].getMissionAptitude();
        }
        CrewSort::sortHighToLow(keys, idx);
    }

    // Build sorted output (copy, not in-place)
    vector<HumanCrew> out;
    out.reserve(idx.size());
    for (size_t k = 0; k < idx.size(); k++) {
        out.push_back(input[idx[k]]);
    }
    return out;
}

// ================= OVERALL SORT: ALIENS =================
// Filter TLT total < 15, then Aptitude ↓, TrainingScore ↓, Homeworld A->Z

vector<alienCrew> CrewSort::overallSortAliens(const vector<alienCrew>& input) {
    vector<size_t> idx;

    // Filter step: only aliens with TLT total >= 15
    for (size_t i = 0; i < input.size(); i++) {
        int total = input[i].getTelepathicLinkTest().getTotal();
        if (total >= 15) {
            idx.push_back(i);
        }
    }

    // If none pass, return empty vector
    if (idx.empty()) {
        return {};
    }

    // Pass 1 — lowest priority: Homeworld A->Z
    {
        vector<string> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++) {
            keys[k] = input[idx[k]].getHomeworld();
        }
        CrewSort::sortAToZ(keys, idx);
    }

    // Pass 2 — middle: TrainingScore high->low
    {
        vector<double> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++) {
            keys[k] = input[idx[k]].getTrainingScore();
        }
        CrewSort::sortHighToLow(keys, idx);
    }

    // Pass 3 — highest: MissionAptitude high->low
    {
        vector<double> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++) {
            keys[k] = input[idx[k]].getMissionAptitude();
        }
        CrewSort::sortHighToLow(keys, idx);
    }

    // Build sorted output
    vector<AlienCrew> out;
    out.reserve(idx.size());
    for (size_t k = 0; k < idx.size(); k++) {
        out.push_back(input[idx[k]]);
    }
    return out;
}