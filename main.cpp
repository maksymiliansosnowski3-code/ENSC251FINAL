// ENSC251 C++ Programming Final Project (fixed main.cpp)
// - Replaces any std::sort usage for merged ordering with a simple insertion sort.
// - Adds clear prompts/confirmations for insert/delete menu options.
// - Minimal changes elsewhere to preserve original behavior.

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm> // for remove_if and other utilities

#include "crewmember.hpp"
#include "telepathiclinktest.hpp"
#include "aliencrew.hpp"
#include "humancrew.hpp"
#include "crew_sort.hpp"
#include "linkedlist.hpp"
#include "stringManip.hpp"
#include "unittests.hpp"
#include "logger.hpp"

using namespace std;

// Reusable merged-entry struct used for merge/display sorting
struct MEntry {
    bool isHuman;
    size_t index;
    double apt;
    double train;
};

// Insertion sort for merged vector using the project's comparator rules.
// Simple and easy to read for beginners.
static void insertionSortMerged(vector<MEntry> &merged) {
    auto cmp = [](const MEntry& a, const MEntry& b) {
        if (a.apt != b.apt) return a.apt > b.apt;            // higher aptitude first
        if (a.train != b.train) return a.train > b.train;  // higher training next
        if (a.isHuman != b.isHuman) return a.isHuman && !b.isHuman; // humans before aliens on tie
        return false;
    };

    for (size_t i = 1; i < merged.size(); ++i) {
        MEntry key = merged[i];
        int j = (int)i - 1;
        while (j >= 0 && cmp(key, merged[j])) {
            merged[j + 1] = merged[j];
            --j;
        }
        merged[j + 1] = key;
    }
}

struct humanArchives {
    string FirstName;
    string LastName;
    string Sector;
    double TrainingScore;
    double MissionAptitude;
};

struct alienArchives : humanArchives {
    string Homeworld;
    double SignalStrength;
    double CognitiveLink;
    double EmpathicOverlay;
    double CognitiveResistance;
    double Total;
};

int readIntSafe() {
    int value;
    cin >> value;
    while (!cin) {
        cin.clear();
        cin.ignore(10000, '\n');
        cin >> value;
    }
    return value;
}

bool isValidSector(const string& s) {
    static const string valid[] = {
        "Alpha", "Beta", "Gamma", "Delta", "Sigma", "Zeta", "Omega"
    };
    for (const auto& v : valid) {
        if (s == v) return true;
    }
    return false;
}

bool isValidHomeworld(const string& w) {
    static const string valid[] = {
        "Vulcar", "Orion", "Trask", "Eidolon", "Lyra",
        "Novera", "Talos", "Altair", "Mira", "Zephon"
    };
    for (const auto& v : valid) {
        if (w == v) return true;
    }
    return false;
}

bool parseHumanLine(const string& line, humanArchives& out) {
    if (line.empty()) return true;
    stringstream ss(line);
    if (!(ss >> out.FirstName
            >> out.LastName
            >> out.Sector
            >> out.TrainingScore
            >> out.MissionAptitude)) {
        return false;
    }
    StringManip::typoCorrector(out.Sector);
    if (!isValidSector(out.Sector)) return false;
    if (out.TrainingScore < 0.0 || out.TrainingScore > 4.3) return false;
    if (out.MissionAptitude < 0.0 || out.MissionAptitude > 100.0) return false;
    return true;
}

bool parseAlienLine(const string& line, alienArchives& out) {
    if (line.empty()) return true;
    stringstream ss(line);
    if (!(ss >> out.FirstName
            >> out.LastName
            >> out.Homeworld
            >> out.TrainingScore
            >> out.MissionAptitude
            >> out.SignalStrength
            >> out.CognitiveLink
            >> out.EmpathicOverlay
            >> out.CognitiveResistance
            >> out.Total)) {
        return false;
    }
    if (!isValidHomeworld(out.Homeworld)) return false;
    if (out.TrainingScore < 0.0 || out.TrainingScore > 4.3) return false;
    if (out.MissionAptitude < 0.0 || out.MissionAptitude > 100.0) return false;
    auto in01 = [&](double v) {
        return (v >= 0.0 && v <= 10.0);
    };
    if (!in01(out.SignalStrength) ||
            !in01(out.CognitiveLink)  ||
            !in01(out.EmpathicOverlay) ||
            !in01(out.CognitiveResistance)) {
        return false;
    }
    if (out.Total < 0.0 || out.Total > 40.0) return false;
    return true;
}

Logger logger;

// Add a simple deterministic ID generator so every created crew member gets a unique ID.
// Starts at the previous literal value for compatibility, increments on each call.
static int getNextId() {
    static int nextId = 25220000;
    return nextId++;
}

int main() {
    vector<humanArchives> humanInfo;
    vector<alienArchives> alienInfo;

    ifstream humanRecords("human-crew.txt");
    ifstream alienRecords("alien-crew.txt");

    if (!humanRecords.is_open() || !alienRecords.is_open()) {
        cerr << "Failed to open data files.\n";
        return 1;
    }

    string header;
    getline(humanRecords, header);
    getline(alienRecords, header);

    string line;
    while (getline(humanRecords, line)) {
        humanArchives rec;
        if (!parseHumanLine(line, rec)) {
            cerr << "Error parsing human record: " << line << "\n";
            return 1;
        }
        if (!line.empty())
            humanInfo.push_back(rec);
    }

    while (getline(alienRecords, line)) {
        alienArchives rec;
        if (!parseAlienLine(line, rec)) {
            cerr << "Error parsing alien record: " << line << "\n";
            return 1;
        }
        if (!line.empty())
            alienInfo.push_back(rec);
    }

    vector<HumanCrew> humans;
    vector<AlienCrew> aliens;

    humans.reserve(humanInfo.size());
    for (auto& h : humanInfo) {
        try {
            HumanCrew obj(h.FirstName, h.LastName,
                          (float)h.TrainingScore, (int)h.MissionAptitude,
                          getNextId(), h.Sector);
            humans.push_back(obj);
        } catch (const std::exception &e) {
            cerr << "Failed to construct HumanCrew: " << e.what() << "\n";
            return 1;
        } catch (...) {
            cerr << "Unknown error constructing HumanCrew\n";
            return 1;
        }
    }

    aliens.reserve(alienInfo.size());
    for (auto& a : alienInfo) {
        try {
            TelepathicLinkTest t(
                (int)a.SignalStrength,
                (int)a.CognitiveLink,
                (int)a.EmpathicOverlay,
                (int)a.CognitiveResistance
            );
            AlienCrew obj(a.FirstName, a.LastName,
                          (float)a.TrainingScore, (int)a.MissionAptitude,
                          getNextId(), a.Homeworld, t);
            aliens.push_back(obj);
        } catch (const std::exception &e) {
            cerr << "Failed to construct AlienCrew: " << e.what() << "\n";
            return 1;
        } catch (...) {
            cerr << "Unknown error constructing AlienCrew\n";
            return 1;
        }
    }

    LinkedList list;
    for (auto& h : humans) list.insertSorted(new HumanCrew(h));
    for (auto& a : aliens) list.insertSorted(new AlienCrew(a));

    int choice = 0;
    while (choice != 6) {
        cout << "1. Single-field sort\n";
        cout << "2. Overall sort\n";
        cout << "3. Insert new recruit\n";
        cout << "4. Delete recruits by full name\n";
        cout << "5. Merge and display qualified recruits\n";
        cout << "6. Exit\n";
        cout << "7. Run unit tests\n";
        cout << "8. View search logs\n";
        cout << "9. Search recruits\n";

        choice = readIntSafe();

        switch (choice) {
        case 1: {
            cout << "1. Humans\n2. Aliens\n";
            int category = readIntSafe();

            if (category == 1) {
                cout << "1. Mission Aptitude\n2. Training Score\n3. Home Sector\n";
                int field = readIntSafe();

                vector<size_t> idx(humans.size());
                for (size_t i = 0; i < idx.size(); i++) idx[i] = i;

                if (field == 1) {
                    logger.log("SINGLE-FIELD SORT: Humans by Mission Aptitude");
                    vector<double> keys(idx.size());
                    for (size_t k = 0; k < idx.size(); k++)
                        keys[k] = humans[idx[k]].getMissionAptitude();
                    CrewSort::sortHighToLow(keys, idx);
                    for (size_t k = 0; k < idx.size(); k++) {
                        auto& h = humans[idx[k]];
                        cout << h.getFirstName() << " " << h.getLastName()
                             << " | Aptitude: " << h.getMissionAptitude() << "\n";
                    }
                } else if (field == 2) {
                    logger.log("SINGLE-FIELD SORT: Humans by Training Score");
                    vector<double> keys(idx.size());
                    for (size_t k = 0; k < idx.size(); k++)
                        keys[k] = humans[idx[k]].getTrainingScore();
                    CrewSort::sortHighToLow(keys, idx);
                    for (size_t k = 0; k < idx.size(); k++) {
                        auto& h = humans[idx[k]];
                        cout << h.getFirstName() << " " << h.getLastName()
                             << " | Training: " << h.getTrainingScore() << "\n";
                    }
                } else if (field == 3) {
                    logger.log("SINGLE-FIELD SORT: Humans by Home Sector");
                    vector<string> keys(idx.size());
                    for (size_t k = 0; k < idx.size(); k++)
                        keys[k] = humans[idx[k]].getHomeSector();
                    CrewSort::sortAToZ(keys, idx);
                    for (size_t k = 0; k < idx.size(); k++) {
                        auto& h = humans[idx[k]];
                        cout << h.getFirstName() << " " << h.getLastName()
                             << " | Sector: " << h.getHomeSector() << "\n";
                    }
                }
            } else if (category == 2) {
                cout << "1. Mission Aptitude\n2. Training Score\n3. Homeworld\n";
                int field = readIntSafe();

                vector<size_t> idx(aliens.size());
                for (size_t i = 0; i < idx.size(); i++) idx[i] = i;

                if (field == 1) {
                    logger.log("SINGLE-FIELD SORT: Aliens by Mission Aptitude");
                    vector<double> keys(idx.size());
                    for (size_t k = 0; k < idx.size(); k++)
                        keys[k] = aliens[idx[k]].getMissionAptitude();
                    CrewSort::sortHighToLow(keys, idx);
                    for (size_t k = 0; k < idx.size(); k++) {
                        auto& a = aliens[idx[k]];
                        cout << a.getFirstName() << " " << a.getLastName()
                             << " | Aptitude: " << a.getMissionAptitude() << "\n";
                    }
                } else if (field == 2) {
                    logger.log("SINGLE-FIELD SORT: Aliens by Training Score");
                    vector<double> keys(idx.size());
                    for (size_t k = 0; k < idx.size(); k++)
                        keys[k] = aliens[idx[k]].getTrainingScore();
                    CrewSort::sortHighToLow(keys, idx);
                    for (size_t k = 0; k < idx.size(); k++) {
                        auto& a = aliens[idx[k]];
                        cout << a.getFirstName() << " " << a.getLastName()
                             << " | Training: " << a.getTrainingScore() << "\n";
                    }
                } else if (field == 3) {
                    logger.log("SINGLE-FIELD SORT: Aliens by Home World");
                    vector<string> keys(idx.size());
                    for (size_t k = 0; k < idx.size(); k++)
                        keys[k] = aliens[idx[k]].getHomeworld();
                    CrewSort::sortAToZ(keys, idx);
                    for (size_t k = 0; k < idx.size(); k++) {
                        auto& a = aliens[idx[k]];
                        cout << a.getFirstName() << " " << a.getLastName()
                             << " | Homeworld: " << a.getHomeworld() << "\n";
                    }
                }
            }
            break;
        }

        case 2: {
            cout << "1. Humans\n2. Aliens\n";
            int cat = readIntSafe();

            if (cat == 1) {
                auto sorted = CrewSort::overallSortHumans(humans);
                for (auto& h : sorted) {
                    cout << h.getFirstName() << " " << h.getLastName()
                         << " | Aptitude: " << h.getMissionAptitude()
                         << " | Training: " << h.getTrainingScore()
                         << " | Sector: " << h.getHomeSector() << "\n";
                }
            } else if (cat == 2) {
                auto sorted = CrewSort::overallSortAliens(aliens);
                for (auto& a : sorted) {
                    cout << a.getFirstName() << " " << a.getLastName()
                         << " | Aptitude: " << a.getMissionAptitude()
                         << " | Training: " << a.getTrainingScore()
                         << " | Homeworld: " << a.getHomeworld()
                         << " | TLT Total: " << a.getTelepathicLinkTest().getTotal()
                         << "\n";
                }
            }
            break;
        }

        case 3: {
            cout << "1. Human\n2. Alien\n";
            int cat = readIntSafe();

            if (cat == 1) {
                logger.log("INSERT HUMAN");
                cout << "Enter: FirstName LastName HomeSector TrainingScore MissionAptitude\n";
                string fn, ln, sec;
                double ts;
                int apt;
                cin >> fn >> ln >> sec >> ts >> apt;
                try {
                    HumanCrew obj(fn, ln, (float)ts, apt, getNextId(), sec);
                    humans.push_back(obj);
                    list.insertSorted(new HumanCrew(obj));
                    cout << "Inserted Human: " << obj.getFirstName() << " " << obj.getLastName()
                         << " | Sector: " << obj.getHomeSector()
                         << " | Aptitude: " << obj.getMissionAptitude()
                         << " | Training: " << obj.getTrainingScore() << "\n";
                } catch (const std::exception &e) {
                    cout << "Failed to insert Human: " << e.what() << "\n";
                } catch (...) {
                    cout << "Failed to insert Human: unknown error\n";
                }
            } else if (cat == 2) {
                logger.log("INSERT ALIEN");
                cout << "Enter: FirstName LastName Homeworld TrainingScore MissionAptitude SignalStrength CognitiveLink EmpathicOverlay CognitiveResistance\n";
                string fn, ln, world;
                double ts;
                int apt, s, c, e, r;
                cin >> fn >> ln >> world >> ts >> apt >> s >> c >> e >> r;
                try {
                    TelepathicLinkTest t(s, c, e, r);
                    AlienCrew obj(fn, ln, (float)ts, apt, getNextId(), world, t);
                    aliens.push_back(obj);
                    list.insertSorted(new AlienCrew(obj));
                    cout << "Inserted Alien: " << obj.getFirstName() << " " << obj.getLastName()
                         << " | Homeworld: " << obj.getHomeworld()
                         << " | Aptitude: " << obj.getMissionAptitude()
                         << " | Training: " << obj.getTrainingScore()
                         << " | TLT Total: " << obj.getTelepathicLinkTest().getTotal() << "\n";
                } catch (const std::exception &e) {
                    cout << "Failed to insert Alien: " << e.what() << "\n";
                } catch (...) {
                    cout << "Failed to insert Alien: unknown error\n";
                }
            }
            break;
        }

        case 4: {
            cout << "Enter first and last name of recruit to delete (e.g. John Doe):\n";
            string first, last;
            cin >> first >> last;
            string fullName = first + " " + last;
            string upperName = StringManip::toUpper(fullName);
            
            logger.log("DELETE REQUEST: name = " + fullName);

            // count nodes and vector sizes before deletion
            auto countListNodes = [&]() {
                int cnt = 0;
                Node* n = list.getHead();
                while (n) { ++cnt; n = n->getNext(); }
                return cnt;
            };
            int beforeNodes = countListNodes();
            size_t beforeHumans = humans.size();
            size_t beforeAliens = aliens.size();

            // perform deletions
            list.deleteWithName(fullName);

            humans.erase(
                remove_if(humans.begin(), humans.end(),
                    [&](const HumanCrew& h) {
                        string n = h.getFirstName() + " " + h.getLastName();
                        return StringManip::toUpper(n) == upperName;
                    }),
                humans.end()
            );

            aliens.erase(
                remove_if(aliens.begin(), aliens.end(),
                    [&](const AlienCrew& a) {
                        string n = a.getFirstName() + " " + a.getLastName();
                        return StringManip::toUpper(n) == upperName;
                    }),
                aliens.end()
            );

            // count after deletion
            int afterNodes = countListNodes();
            size_t afterHumans = humans.size();
            size_t afterAliens = aliens.size();

            int removedFromList = beforeNodes - afterNodes;
            size_t removedHumans = beforeHumans - afterHumans;
            size_t removedAliens = beforeAliens - afterAliens;

            if (removedFromList > 0 || removedHumans > 0 || removedAliens > 0) {
                cout << "Deleted " << removedFromList << " node(s) from linked list";
                cout << " (Humans removed: " << removedHumans << ", Aliens removed: " << removedAliens << ").\n";
                logger.log(
                    "DELETE SUCCESS: name = " + fullName +
                    " | list nodes removed = " + std::to_string(removedFromList) +
                    " | humans removed = " + std::to_string(removedHumans) +
                    " | aliens removed = " + std::to_string(removedAliens)
            );
            } else {
                cout << "No recruit found with name: " << fullName << "\n";
                logger.log("DELETE FAILED: no recruit found with name = " + fullName);
            }
            break;
        }

        case 5: {
            logger.log("MERGE AND DISPLAY QUALIFIED RECRUITS");

            vector<MEntry> merged;
            merged.reserve(humans.size() + aliens.size());

            for (size_t i = 0; i < humans.size(); ++i) {
                MEntry e{true, i, (double)humans[i].getMissionAptitude(),
                         (double)humans[i].getTrainingScore()};
                merged.push_back(e);
            }

            for (size_t i = 0; i < aliens.size(); ++i) {
                if (aliens[i].getTelepathicLinkTest().getTotal() >= 15) {
                    MEntry e{false, i, (double)aliens[i].getMissionAptitude(),
                             (double)aliens[i].getTrainingScore()};
                    merged.push_back(e);
                }
            }

            insertionSortMerged(merged);

            for (auto& e : merged) {
                if (e.isHuman) {
                    const HumanCrew& h = humans[e.index];
                    cout << "Human "
                         << h.getFirstName() << " " << h.getLastName()
                         << " | Aptitude: " << h.getMissionAptitude()
                         << " | Training: " << h.getTrainingScore()
                         << " | Sector: " << h.getHomeSector() << "\n";
                } else {
                    const AlienCrew& a = aliens[e.index];
                    cout << "Alien "
                         << a.getFirstName() << " " << a.getLastName()
                         << " | Aptitude: " << a.getMissionAptitude()
                         << " | Training: " << a.getTrainingScore()
                         << " | Homeworld: " << a.getHomeworld()
                         << " | TLT Total: " << a.getTelepathicLinkTest().getTotal()
                         << "\n";
                }
            }
            break;
        }

        case 6:
            return 0;

        case 7:
            runAllUnitTests();
            logger.log("UNIT TEST FINISHED");
            break;
        case 8:
            logger.show();
            break;
       case 9: {
        
            cout << "Search by:\n";
            cout << "1. ID number\n";
            cout << "2. TrainingScore\n";
            cout << "3. MissionAptitude\n";
            cout << "4. Full name (First Last)\n";

            int opt = readIntSafe();

            if (opt == 1) {
                cout << "Enter ID: ";
                int id = readIntSafe();
                logger.log("SEARCH BY ID: " + to_string(id));
                list.searchByID(id);
            } else if (opt == 2) {
                cout << "Enter TrainingScore (e.g. 3.5): ";
                double ts;
                cin >> ts;
                logger.log("SEARCH BY TRAINING: " + to_string(ts));
                list.searchByTrainingScore(ts);
            } else if (opt == 3) {
                cout << "Enter MissionAptitude (integer): ";
                int apt = readIntSafe();
                logger.log("SEARCH BY APTITUDE: " + to_string(apt));
                list.searchByMissionAptitude(apt);
            } else if (opt == 4) {
                cout << "Enter FirstName and LastName: ";
                string fn, ln;
                cin >> fn >> ln;
                string full = fn + " " + ln;
                logger.log("SEARCH BY NAME: " + full);
                list.searchByName(full);
            } else {
                cout << "Invalid search option.\n";
            }

            break;
        }

        default:
            cout << "Invalid option. Please enter a number from 1 to 9.\n";
            break;
        } // end switch
    } // end while

    return 0;
}