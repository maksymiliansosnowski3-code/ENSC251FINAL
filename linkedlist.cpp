#include <iostream>
#include <string>
#include "node.hpp"
#include "linkedlist.hpp"
#include "stringManip.hpp"
#include <fstream>
using namespace std;

// default constructor to initialize the linked list with head and tail as nullptr
LinkedList::LinkedList() {
    head = nullptr;
    tail = nullptr;
}

// destructor to free memory allocated for the linked list

LinkedList::~LinkedList() {
    Node* curr = head;
    while (curr != nullptr) {
        Node* nextNode = curr->getNext();
        delete curr;
        curr = nextNode;
    }
}

// inserts a CrewMember into the linked list in sorted order
void LinkedList::insertSorted(CrewMember* member) {
    Node* newNode = new Node(member);

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

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

// deletes all nodes with a CrewMember matching the given name
void LinkedList::deleteWithName(string name) {
    if (!head) return;

    string target = StringManip::toUpper(name);
    Node* curr = head;
    Node* prev = nullptr;
    // go thru the list to find matches
    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        string full = data->getFirstName() + " " + data->getLastName();
        string upperFull = StringManip::toUpper(full);
        // If a match is found, delete the node
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
        if (data != nullptr && (int)data->getId() == id) {
            cout << "Match found: "
                 << data->getFirstName() << " "
                 << data->getLastName()
                 << " (ID " << data->getId() << ")\n";
            found = true;
        }
        curr = curr->getNext();
    }

    if (!found) {
        cout << "No crew member found with ID " << id << ".\n";
    }
}

void LinkedList::searchByName(string name) const {
    Node* curr = head;
    bool found = false;

    string target = StringManip::toUpper(name);
    // go thru the list to find matches
    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        string full = data->getFirstName() + " " + data->getLastName();
        if (StringManip::toUpper(full) == target) {
            cout << "Found: " << full << "\n";
            found = true;
        }
        curr = curr->getNext();
    }

    if (!found) cout << "No match found.\n";
}

void LinkedList::searchByTrainingScore(double trainingScore) const {
    Node* curr = head;
    bool found = false;

    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        if (data->getTrainingScore() == trainingScore) {
            cout << data->getFirstName() << " " << data->getLastName()
                 << " | Training: " << data->getTrainingScore() << "\n";
            found = true;
        }
        curr = curr->getNext();
    }

    if (!found) cout << "No match found.\n";
}

// searches for CrewMembers by mission aptitude and prints matches
void LinkedList::searchByMissionAptitude(double missionAptitude) const {
    Node* curr = head;
    bool found = false;
    // go thru the list to find matches
    while (curr != nullptr) {
        CrewMember* data = curr->getData();
        if (data->getMissionAptitude() == missionAptitude) {
            cout << data->getFirstName() << " " << data->getLastName()
                 << " | Aptitude: " << data->getMissionAptitude() << "\n";
            found = true;
        }
        curr = curr->getNext();
    }

    if (!found) cout << "No match found.\n";
}

// returns the head node of the linked list
Node* LinkedList::getHead() const {
    return head;
}
//  returns the next node after head
Node* LinkedList::getNext() const {
    return head ? head->getNext() : nullptr;
}
