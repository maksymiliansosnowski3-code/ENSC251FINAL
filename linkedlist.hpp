#ifndef LINKEDLIST_HPP
#define LINKEDLIST_HPP

#include <iostream>
#include <string>
#include "node.hpp"
using namespace std;

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    // inserts a CrewMember into the linked list in sorted order
    void insertSorted(CrewMember* member);
    // deletes a CrewMember by ID
    void deleteWithName(string name);

    // searches for CrewMembers by ID and prints matches
    void searchByID(int id) const;
    // searches for CrewMembers by name and prints matches
    void searchByName(string name) const;
    // searches for CrewMembers by training score and prints matches
    void searchByTrainingScore(double trainingScore) const;
    // searches for CrewMembers by mission aptitude and prints matches
    void searchByMissionAptitude(double missionAptitude) const;

    Node* getHead() const;
    Node* getNext() const;

private:
    // head and tail pointers for the linked list
    Node* head;
    Node* tail;
};

#endif
