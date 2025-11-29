#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "crewmember.hpp"
#include "telepathiclinktest.hpp"
#include "aliencrew.hpp"
#include "humancrew.hpp"
#include "crew_sort.hpp"
using namespace std;


// struct to store human-crew.txt file info
struct humanArchives {
    string FirstName;
    string LastName;
    string Sector;
    double TrainingScore;
    double MissionAptitude;
};

// derived struct to store alien-crew.txt file info
struct alienArchives : humanArchives {

    // FirstName LastName Homeworld TrainingScore MissionAptitude SignalStrength CognitiveLink EmpathicOverlay CognitiveResistance Total
    string Homeworld;
    double SignalStrength;
    double CognitiveLink;
    double EmpathicOverlay;
    double CognitiveResistance;
    double Total;

};

void singleFieldSortMenu(CrewSort& sortHelper, const vector<HumanCrew>& humans, const vector<AlienCrew>& aliens) {
    cout << "Which crew would you like to sort?\n";
    cout << "1: Humans\n";
    cout << "2: Aliens\n";
}   

int readIntSafe() {
    int value;
    cin >> value;

    while (!cin) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Invalid input. Try again: ";
        cin >> value;
    }

    return value;
}

int main() {

    // vector to store records 
    vector<humanArchives> humanInfo;
    vector<alienArchives> alienInfo;

    ifstream humanRecords("human-crew.txt");
    ifstream alienRecords("alien-crew.txt");


    // check whether files are open or closed
    if (!humanRecords.is_open() || !alienRecords.is_open()) {
        cerr << "Error accessing human or alien information. Please make sure file is open and try again.\n";
        return 1;
    }


    // read and discard header line to avoid type conflicts while parsing text 
    string header;
    getline(humanRecords, header);
    getline(alienRecords, header);


    // temporary struct objects to store field information associated with each text file
    humanArchives parseHumanInfo;
    alienArchives parseAlienInfo;


    while(humanRecords >> parseHumanInfo.FirstName >> parseHumanInfo.LastName >> parseHumanInfo.MissionAptitude >> parseHumanInfo.Sector >> parseHumanInfo.TrainingScore) {
        humanInfo.push_back(parseHumanInfo);
    }

    while(alienRecords >> parseAlienInfo.FirstName >> parseAlienInfo.LastName >> parseAlienInfo.Homeworld >> parseAlienInfo.TrainingScore >> parseAlienInfo.MissionAptitude >> parseAlienInfo.SignalStrength >> parseAlienInfo.CognitiveLink >> parseAlienInfo.EmpathicOverlay >> parseAlienInfo.CognitiveResistance >> parseAlienInfo.Total) {
        alienInfo.push_back(parseAlienInfo);
    }

    // looped menu for sorting options (single field sorting, overall sorting)
    vector<HumanCrew> humans;
    vector<AlienCrew> aliens;

    // TODO: load humans and aliens here (parseInputHumanCrew / parseInputAlienCrew)

    int choice = 0;
    bool exitMenu = false;

    while (!exitMenu) {
        cout << "\n=== Interplanetary Alliance Recruitment Menu ===\n";
        cout << "1. Single-field sort\n";
        cout << "2. Overall sort\n";
        cout << "3. Exit\n";
        cout << "Enter choice: ";
        choice = readIntSafe();

        switch (choice) {
        case 1: {
            // single field sort
            cout << "\nSingle-field sort:\n";
            cout << "1. Humans\n";
            cout << "2. Aliens\n";
            cout << "Enter category: ";
            int category = readIntSafe();

            switch (category) {
            case 1: {
                // Humans
                if (humans.empty()) {
                    cout << "No human data loaded.\n";
                } else {
                    cout << "\nSort humans by:\n";
                    cout << "1. Mission aptitude (high→low)\n";
                    cout << "2. Training score (high→low)\n";
                    cout << "3. Home sector (A→Z)\n";
                    cout << "Enter field: ";
                    int field = readIntSafe();

                    // make a working copy (kept as in your code, though unused)
                    vector<HumanCrew> sorted = humans;

                    switch (field) {
                    // ---------- 1. Mission aptitude ----------
                    case 1: {
                        vector<double> keys(sorted.size());
                        for (size_t i = 0; i < sorted.size(); i++)
                            keys[i] = sorted[i].getMissionAptitude();

                        CrewSort::sortHighToLow(keys);

                        cout << "\nHumans sorted by mission aptitude:\n";
                        for (double val : keys)
                            cout << "Aptitude: " << val << "\n";
                        break;
                    }

                    // ---------- 2. Training score ----------
                    case 2: {
                        vector<double> keys(sorted.size());
                        for (size_t i = 0; i < sorted.size(); i++)
                            keys[i] = sorted[i].getTrainingScore();

                        CrewSort::sortHighToLow(keys);

                        cout << "\nHumans sorted by training score:\n";
                        for (double val : keys)
                            cout << "Training: " << val << "\n";
                        break;
                    }

                    // ---------- 3. Home sector ----------
                    case 3: {
                        vector<string> keys(sorted.size());
                        for (size_t i = 0; i < sorted.size(); i++)
                            keys[i] = sorted[i].getHomeSector();

                        CrewSort::sortAToZ(keys);

                        cout << "\nHumans sorted by home sector:\n";
                        for (const string& s : keys)
                            cout << s << "\n";
                        break;
                    }

                    default:
                        cout << "Invalid field.\n";
                        break;
                    }
                }
                break;
            }

            case 2: {
                // Aliens
                if (aliens.empty()) {
                    cout << "No alien data loaded.\n";
                } else {
                    cout << "\nSort aliens by:\n";
                    cout << "1. Mission aptitude (high→low)\n";
                    cout << "2. Training score (high→low)\n";
                    cout << "3. Homeworld (A→Z)\n";
                    cout << "Enter field: ";
                    int field = readIntSafe();

                    vector<AlienCrew> sorted = aliens;

                    switch (field) {
                    case 1: { // aptitude
                        vector<double> keys(sorted.size());
                        for (size_t i = 0; i < sorted.size(); i++)
                            keys[i] = sorted[i].getMissionAptitude();

                        CrewSort::sortHighToLow(keys);

                        cout << "\nAliens sorted by mission aptitude:\n";
                        for (double val : keys)
                            cout << val << "\n";
                        break;
                    }

                    case 2: { // training
                        vector<double> keys(sorted.size());
                        for (size_t i = 0; i < sorted.size(); i++)
                            keys[i] = sorted[i].getTrainingScore();

                        CrewSort::sortHighToLow(keys);

                        cout << "\nAliens sorted by training score:\n";
                        for (double val : keys)
                            cout << val << "\n";
                        break;
                    }

                    case 3: { // homeworld
                        vector<string> keys(sorted.size());
                        for (size_t i = 0; i < sorted.size(); i++)
                            keys[i] = sorted[i].getHomeworld();

                        CrewSort::sortAToZ(keys);

                        cout << "\nAliens sorted by homeworld:\n";
                        for (const string& s : keys)
                            cout << s << "\n";
                        break;
                    }

                    default:
                        cout << "Invalid field.\n";
                        break;
                    }
                }
                break;
            }

            default:
                cout << "Invalid category.\n";
                break;
            }

            break;
        }
// Overall Sort
        case 2: {
            cout << "\nOverall sort:\n";
            cout << "1. Humans\n";
            cout << "2. Aliens\n";
            cout << "Enter category: ";

            int category = readIntSafe();
            // Humans
            switch (category) {
            case 1: {
                if (humans.empty()) {
                    cout << "No human data loaded.\n";
                } else {
                    vector<HumanCrew> sorted = CrewSort::overallSortHumans(humans);
                    cout << "\nOverall sorted humans:\n";
                    for (size_t i = 0; i < sorted.size(); i++) {
                        cout << sorted[i] << '\n';
                }

                }
                break;
            }
            // Aliens
            case 2: {
                if (aliens.empty()) {
                    cout << "No alien data loaded.\n";
                } else {
                    vector<AlienCrew> sorted = CrewSort::overallSortAliens(aliens);
                    if (sorted.empty()) {
                        cout << "\nNo aliens meet TLT >= 15 requirement.\n";
                    } else {
                        cout << "\nOverall sorted aliens:\n";
                        for (size_t i = 0; i < sorted.size(); i++) {
                            cout << sorted[i] << '\n';
                        }

                    }
                }
                break;
            }

            default:
                cout << "Invalid category.\n";
                break;
            }

            break;
        }

        case 3:
            cout << "Exiting program.\n";
            exitMenu = true;
            break;

        default:
            cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
    
}