#include <iostream>
#include <string>
#include <vector>
#include "aliencrew.hpp"
#include "humancrew.hpp"
#include "crew_sort.hpp"

using namespace std;

void CrewSort::sortHighToLow(vector<double>& keys, vector<size_t>& idx) {
    for (int i = 0; i < (int)keys.size(); i++) {
        double kVal = keys[i];
        size_t idVal = idx[i];
        int j = i - 1;

        while (j >= 0 && keys[j] < kVal) {
            keys[j + 1] = keys[j];
            idx[j + 1] = idx[j];
            j--;
        }
        keys[j + 1] = kVal;
        idx[j + 1] = idVal;
    }
}

void CrewSort::sortAToZ(vector<string>& keys, vector<size_t>& idx) {
    for (int i = 0; i < (int)keys.size(); i++) {
        string kVal = keys[i];
        size_t idVal = idx[i];
        int j = i - 1;

        while (j >= 0 && keys[j] > kVal) {
            keys[j + 1] = keys[j];
            idx[j + 1] = idx[j];
            j--;
        }
        keys[j + 1] = kVal;
        idx[j + 1] = idVal;
    }
}

void CrewSort::sortHighToLow(vector<double>& keys) {
    vector<size_t> idx(keys.size());
    for (size_t i = 0; i < idx.size(); ++i) idx[i] = i;
    sortHighToLow(keys, idx);
}

void CrewSort::sortAToZ(vector<string>& keys) {
    vector<size_t> idx(keys.size());
    for (size_t i = 0; i < idx.size(); ++i) idx[i] = i;
    sortAToZ(keys, idx);
}

vector<HumanCrew> CrewSort::overallSortHumans(const vector<HumanCrew>& input) {
    vector<size_t> idx(input.size());
    for (size_t i = 0; i < idx.size(); i++) idx[i] = i;

    {
        vector<string> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++)
            keys[k] = input[idx[k]].getHomeSector();
        sortAToZ(keys, idx);
    }

    {
        vector<double> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++)
            keys[k] = input[idx[k]].getTrainingScore();
        sortHighToLow(keys, idx);
    }

    {
        vector<double> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++)
            keys[k] = input[idx[k]].getMissionAptitude();
        sortHighToLow(keys, idx);
    }

    vector<HumanCrew> out;
    out.reserve(idx.size());
    for (size_t k = 0; k < idx.size(); k++)
        out.push_back(input[idx[k]]);

    return out;
}

vector<AlienCrew> CrewSort::overallSortAliens(const vector<AlienCrew>& input) {
    vector<size_t> idx;

    for (size_t i = 0; i < input.size(); i++) {
        int total = input[i].getTelepathicLinkTest().getTotal();
        if (total >= 15) idx.push_back(i);
    }

    if (idx.empty()) return {};

    {
        vector<string> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++)
            keys[k] = input[idx[k]].getHomeworld();
        sortAToZ(keys, idx);
    }

    {
        vector<double> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++)
            keys[k] = input[idx[k]].getTrainingScore();
        sortHighToLow(keys, idx);
    }

    {
        vector<double> keys(idx.size());
        for (size_t k = 0; k < idx.size(); k++)
            keys[k] = input[idx[k]].getMissionAptitude();
        sortHighToLow(keys, idx);
    }

    vector<AlienCrew> out;
    out.reserve(idx.size());
    for (size_t k = 0; k < idx.size(); k++)
        out.push_back(input[idx[k]]);

    return out;
}
