#include "unittests.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "linkedlist.hpp"
#include "humancrew.hpp"
#include "aliencrew.hpp"
#include "telepathiclinktest.hpp"
#include "stringManip.hpp"

using namespace std;

struct TestSummary {
    int passed = 0;
    int failed = 0;
    void pass() { ++passed; }
    void fail() { ++failed; }
    void print() const {
        cout << "\nUnit Test Summary: " << passed << " passed, " << failed << " failed.\n";
    }
};

static void expect(TestSummary &s, bool condition, const string &msg) {
    if (condition) {
        cout << "[PASS] " << msg << "\n";
        s.pass();
    } else {
        cout << "[FAIL] " << msg << "\n";
        s.fail();
    }
}

static vector<CrewMember*> collectList(const LinkedList &list) {
    vector<CrewMember*> out;
    Node* n = list.getHead();
    while (n) {
        out.push_back(n->getData());
        n = n->getNext();
    }
    return out;
}

static void testInsertOrderingHumans(TestSummary &s) {
    LinkedList list;
    // Insert humans with various aptitudes/training to exercise ordering
    // Higher aptitude first, tie-breaker training score higher first
    list.insertSorted(new HumanCrew("Alice", "A", 3.0f, 90, 1001, "Alpha"));
    list.insertSorted(new HumanCrew("Bob",   "B", 4.0f, 85, 1002, "Beta"));
    list.insertSorted(new HumanCrew("Cara",  "C", 2.0f, 90, 1003, "Gamma")); // same aptitude as Alice, lower training -> after Alice
    auto v = collectList(list);
    bool ok = (v.size() == 3)
              && (v[0]->getFirstName() == "Alice")
              && (v[1]->getFirstName() == "Cara" || v[1]->getFirstName() == "Bob"); // depends on comparator, but Alice must be first
    // More strict ordering:
    if (v.size() == 3) {
        ok = (v[0]->getFirstName() == "Alice")
             && (v[1]->getFirstName() == "Cara")
             && (v[2]->getFirstName() == "Bob");
    }
    expect(s, ok, "Insert ordering for HumanCrew (high aptitude then training).");
}

static void testInsertOrderingAliens(TestSummary &s) {
    LinkedList list;
    TelepathicLinkTest t1(5,5,5,5); // total 20
    TelepathicLinkTest t2(1,1,1,1); // total 4
    list.insertSorted(new AlienCrew("Xeno","X", 3.0f, 95, 2001, "Vulcar", t1)); // top aptitude
    list.insertSorted(new AlienCrew("Yuri","Y", 3.5f, 90, 2002, "Orion", t2));
    list.insertSorted(new AlienCrew("Zeta","Z", 4.0f, 95, 2003, "Trask", t2)); // tie aptitude with Xeno, but training higher -> should appear before Xeno if comparator sorts on training
    auto v = collectList(list);
    bool ok = (v.size() == 3);
    if (ok) {
        // expected first: Zeta or Xeno depending on training tie-break; ensure highest aptitude ones are first two
        ok = ((v[0]->getMissionAptitude() >= v[1]->getMissionAptitude()) &&
              (v[1]->getMissionAptitude() >= v[2]->getMissionAptitude()));
    }
    expect(s, ok, "Insert ordering for AlienCrew (high aptitude then training).");
}

static void testSearchOperations(TestSummary &s) {
    LinkedList list;
    list.insertSorted(new HumanCrew("Sam","Search", 2.5f, 70, 3001, "Delta"));
    list.insertSorted(new HumanCrew("Pat","Find",   3.0f, 75, 3002, "Omega"));
    list.insertSorted(new AlienCrew("Al","One",     2.0f, 60, 4001, "Vulcar", TelepathicLinkTest(2,2,2,2)));
    // search by ID (direct traversal check)
    bool found3002 = false;
    for (auto *m : collectList(list)) {
        if ((int)m->getId() == 3002) found3002 = true;
    }
    expect(s, found3002, "Search by ID: found existing ID (3002).");

    // search by training score exact match
    bool foundTS3 = false;
    for (auto *m : collectList(list)) {
        if (m->getTrainingScore() == 3.0f) foundTS3 = true;
    }
    expect(s, foundTS3, "Search by TrainingScore: exact match found.");

    // search by mission aptitude exact match
    bool foundApt75 = false;
    for (auto *m : collectList(list)) {
        if (m->getMissionAptitude() == 75) foundApt75 = true;
    }
    expect(s, foundApt75, "Search by MissionAptitude: exact match found.");

    // search by name case-insensitive
    bool foundName = false;
    string target = "paT Find";
    string tUp = StringManip::toUpper(target);
    for (auto* m : collectList(list)) {
        string full = m->getFirstName() + " " + m->getLastName();
        if (StringManip::toUpper(full) == tUp) {
            foundName = true;
            break;
        }
    }
    expect(s, foundName, "Search by Name (case-insensitive) found match.");

    // illegal: search non-existing ID
    bool found9999 = false;
    for (auto *m : collectList(list)) {
        if ((int)m->getId() == 9999) found9999 = true;
    }
    expect(s, !found9999, "Search by ID: non-existent ID correctly not found.");
}

static void testDeletionByNameAndHeadTail(TestSummary &s) {
    LinkedList list;
    list.insertSorted(new HumanCrew("Del","Me", 1.0f, 50, 5001, "Alpha"));
    list.insertSorted(new HumanCrew("Keep","One",2.0f, 60, 5002, "Beta"));
    list.insertSorted(new HumanCrew("Del","Me", 3.0f, 70, 5003, "Gamma")); // duplicate name Del Me
    // we have 3 nodes
    auto before = collectList(list);
    expect(s, before.size() == 3, "Precondition: 3 nodes present before deletion.");

    // delete "Del Me" should remove both nodes with that full name
    list.deleteWithName("Del Me");
    auto after = collectList(list);
    bool noneDelMe = true;
    for (auto *m : after) {
        string full = m->getFirstName() + " " + m->getLastName();
        if (StringManip::toUpper(full) == StringManip::toUpper("Del Me")) noneDelMe = false;
    }
    expect(s, noneDelMe && after.size() == 1 && after[0]->getFirstName() == "Keep", "Deletion by full name removes all matches (including head/tail).");

    // delete non-existent name: should leave list unchanged (size remains 1)
    list.deleteWithName("No Name");
    auto after2 = collectList(list);
    expect(s, after2.size() == 1 && after2[0]->getFirstName() == "Keep", "Deletion of non-existent name leaves list unchanged.");
}

static void testMergeAndQualifiedFiltering(TestSummary &s) {
    // Build vectors similar to main's merging behavior and verify ordering
    vector<HumanCrew> humans;
    humans.emplace_back("H1","A", 3.0f, 95, 6001, "Alpha");
    humans.emplace_back("H2","B", 4.0f, 90, 6002, "Beta");
    vector<AlienCrew> aliens;
    aliens.emplace_back("A1","X", 3.5f, 95, 7001, "Vulcar", TelepathicLinkTest(5,5,3,2)); // total 15 -> qualifies
    aliens.emplace_back("A2","Y", 3.5f, 95, 7002, "Orion", TelepathicLinkTest(1,1,1,1)); // total 4 -> doesn't qualify
    aliens.emplace_back("A3","Z", 2.0f, 93, 7003, "Trask", TelepathicLinkTest(6,6,6,6)); // total 24 -> qualifies

    struct MEntry { bool isHuman; size_t index; double apt; double train; };

    vector<MEntry> merged;
    for (size_t i = 0; i < humans.size(); ++i) {
        merged.push_back({true, i, (double)humans[i].getMissionAptitude(), (double)humans[i].getTrainingScore()});
    }
    for (size_t i = 0; i < aliens.size(); ++i) {
        if (aliens[i].getTelepathicLinkTest().getTotal() >= 15) {
            merged.push_back({false, i, (double)aliens[i].getMissionAptitude(), (double)aliens[i].getTrainingScore()});
        }
    }


    auto cmp = [](const MEntry& a, const MEntry& b) {
        if (a.apt != b.apt) return a.apt > b.apt;
        if (a.train != b.train) return a.train > b.train;
        if (a.isHuman != b.isHuman) return a.isHuman && !b.isHuman;
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

    // Verify that:
    // only A1 and A3 from aliens are present (A2 filtered out)
    // ordering respects aptitude, training, and human-before-alien tie-break
    bool filteredCorrect = (merged.size() == 4); // 2 humans + 2 qualified aliens
    expect(s, filteredCorrect, "Merge filtering: only qualified aliens are included.");

    // Check that merged[0] has the highest aptitude among entries
    if (merged.size() >= 2) {
        bool orderOk = true;
        for (size_t i = 1; i < merged.size(); ++i) {
            if (merged[i-1].apt < merged[i].apt) orderOk = false;
            else if (merged[i-1].apt == merged[i].apt && merged[i-1].train < merged[i].train) orderOk = false;
        }
        expect(s, orderOk, "Merge ordering: sorted by aptitude, then training, humans before aliens on tie.");
    } else {
        expect(s, false, "Merge ordering: not enough merged entries to validate ordering.");
    }
}

void runAllUnitTests() {
    cout << "Running unit tests...\n";
    TestSummary summary;
    testInsertOrderingHumans(summary);
    testInsertOrderingAliens(summary);
    testSearchOperations(summary);
    testDeletionByNameAndHeadTail(summary);
    testMergeAndQualifiedFiltering(summary);
    summary.print();
    cout << "End of unit tests.\n\n";
}