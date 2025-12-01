#include <iostream>
#include <string>
#include <cmath>
#include "node.hpp"
#include "linkedlist.hpp"
#include "stringManip.hpp"
#include <fstream>

using namespace std;

LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

LinkedList::~LinkedList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* nextNode = curr->getNext();
        delete curr;
        curr = nextNode;
    }
}

// Helper to print a crew member's key info in a consistent format
static void printCrewMemberInfo(const CrewMember* data) {
    if (data == nullptr) return;
    cout << "Name: " << data->getFirstName() << " " << data->getLastName() << "\n";
    cout << "ID: " << data->getId() << "\n";
    cout << "Training Score: " << data->getTrainingScore() << "\n";
    cout << "Mission Aptitude: " << data->getMissionAptitude() << "\n";
    cout << "--------------------------\n";
}

// inserts a CrewMember into the linked list in sorted order
void LinkedList::insertSorted(CrewMember* member) {
    Node* newNode = new Node(member);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    // If new member should be placed before head (assuming '>' means higher priority)
    if (*(newNode->getData()) > *(head->getData())) {
        newNode->setNext(head);
        head = newNode;
        return;
    }

    Node* curr = head;

    while (curr->getNext() != nullptr &&
           !(*(newNode->getData()) > *(curr->getNext()->getData()))) {
        curr = curr->getNext();
    }

    newNode->setNext(curr->getNext());
    curr->setNext(newNode);

    if (newNode->getNext() == nullptr) {
        tail = newNode;
    }
}

// deletes all nodes with a CrewMember matching the given name (case-insensitive exact full name)
void LinkedList::deleteWithName(string name) {
    if (!head) return;

    string target = StringManip::toUpper(name);
    Node* curr = head;
    Node* prev = nullptr;
    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        if (data == nullptr) {
            prev = curr;
            curr = curr->getNext();
            continue;
        }
        string full = data->getFirstName() + " " + data->getLastName();
        string upperFull = StringManip::toUpper(full);

        if (upperFull == target) {
            if (curr == head) {
                head = head->getNext();
                delete curr;
                curr = head;
                continue;
            } else {
                prev->setNext(curr->getNext());
                delete curr;
                curr = prev->getNext();
                continue;
            }
        }

        prev = curr;
        curr = curr->getNext();
    }
}

// searches for CrewMembers by ID and prints matches
void LinkedList::searchByID(int id) const {
    Node* curr = head;
    bool found = false;
    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        if (data != nullptr && data->getId() == id) {
            printCrewMemberInfo(data);
            found = true;
        }
        curr = curr->getNext();
    }

    if (!found) {
        cout << "No crew member found with ID " << id << ".\n";
    }
}

// searches for CrewMembers by name (case-insensitive, partial match allowed) and prints matches
void LinkedList::searchByName(string name) const {
    if (name.empty()) {
        cout << "Please provide a name to search for.\n";
        return;
    }

    string target = StringManip::toUpper(name);
    Node* curr = head;
    bool found = false;

    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        if (data != nullptr) {
            string first = StringManip::toUpper(data->getFirstName());
            string last  = StringManip::toUpper(data->getLastName());
            string full  = first + " " + last;

            // partial match: target appears in first, last, or full
            if (first.find(target) != string::npos ||
                last.find(target)  != string::npos ||
                full.find(target)  != string::npos) {
                printCrewMemberInfo(data);
                found = true;
            }
        }
        curr = curr->getNext();
    }

    if (!found) {
        cout << "No match found for name: " << name << "\n";
    }
}

// searches for CrewMembers by training score and prints matches (uses epsilon)
void LinkedList::searchByTrainingScore(double trainingScore) const {
    const double EPS = 1e-6;
    Node* curr = head;
    bool found = false;

    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        if (data != nullptr) {
            if (fabs(data->getTrainingScore() - trainingScore) <= EPS) {
                printCrewMemberInfo(data);
                found = true;
            }
        }
        curr = curr->getNext();
    }

    if (!found) {
        cout << "No match found for training score: " << trainingScore << "\n";
    }
}

// searches for CrewMembers by mission aptitude and prints matches (uses epsilon)
void LinkedList::searchByMissionAptitude(double missionAptitude) const {
    const double EPS = 1e-6;
    Node* curr = head;
    bool found = false;

    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        if (data != nullptr) {
            if (fabs(data->getMissionAptitude() - missionAptitude) <= EPS) {
                printCrewMemberInfo(data);
                found = true;
            }
        }
        curr = curr->getNext();
    }

    if (!found) {
        cout << "No match found for mission aptitude: " << missionAptitude << "\n";
    }
}

// returns the head node of the linked list
Node* LinkedList::getHead() const {
    return head;
}

// returns the next node after head
Node* LinkedList::getNext() const {
    return head ? head->getNext() : nullptr;
}
