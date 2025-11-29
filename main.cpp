#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

#include "crewmember.hpp"
#include "telepathiclinktest.hpp"
#include "aliencrew.hpp"
#include "humancrew.hpp"
#include "crew_sort.hpp"
#include "linkedlist.hpp"
#include "stringManip.hpp"

using namespace std;

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

thanks 


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

int main() {
	vector<humanArchives> humanInfo;
	vector<alienArchives> alienInfo;

	ifstream humanRecords("human-crew.txt");
	ifstream alienRecords("alien-crew.txt");

	if (!humanRecords.is_open() || !alienRecords.is_open()) {
		return 1;
	}

	string header;
	getline(humanRecords, header);
	getline(alienRecords, header);

	string line;
	while (getline(humanRecords, line)) {
		humanArchives rec;
		if (!parseHumanLine(line, rec)) {
			return 1;
		}
		if (!line.empty())
			humanInfo.push_back(rec);
	}

	while (getline(alienRecords, line)) {
		alienArchives rec;
		if (!parseAlienLine(line, rec)) {
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
			              25220000, h.Sector);
			humans.push_back(obj);
		} catch (...) {
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
			              25220000, a.Homeworld, t);
			aliens.push_back(obj);
		} catch (...) {
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
				string fn, ln, sec;
				double ts;
				int apt;
				cin >> fn >> ln >> sec >> ts >> apt;
				try {
					HumanCrew obj(fn, ln, (float)ts, apt, 25220000, sec);
					humans.push_back(obj);
					list.insertSorted(new HumanCrew(obj));
				} catch (...) {
				}
			} else if (cat == 2) {
				string fn, ln, world;
				double ts;
				int apt, s, c, e, r;
				cin >> fn >> ln >> world >> ts >> apt >> s >> c >> e >> r;
				try {
					TelepathicLinkTest t(s, c, e, r);
					AlienCrew obj(fn, ln, (float)ts, apt, 25220000, world, t);
					aliens.push_back(obj);
					list.insertSorted(new AlienCrew(obj));
				} catch (...) {
				}
			}
			break;
		}

		case 4: {
			string first, last;
			cin >> first >> last;
			string fullName = first + " " + last;
			string upperName = StringManip::toUpper(fullName);

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
			break;
		}

		case 5: {
			struct MEntry {
				bool isHuman;
				size_t index;
				double apt;
				double train;
			};

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

			sort(merged.begin(), merged.end(),
			[](const MEntry& a, const MEntry& b) {
				if (a.apt != b.apt) return a.apt > b.apt;
				if (a.train != b.train) return a.train > b.train;
				if (a.isHuman != b.isHuman) return a.isHuman && !b.isHuman;
				return false;
			});

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
			break;
		}
	}

	return 0;
}
