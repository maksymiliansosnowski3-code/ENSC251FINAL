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

    void insertSorted(CrewMember* member);
    void deleteWithName(string name);
    void searchByID(int id) const;
    void searchByName(string name) const;
    void searchByTrainingScore(double trainingScore) const;
    void searchByMissionAptitude(double missionAptitude) const;

    Node* getHead() const;
    Node* getNext() const;

private:
    Node* head;
    Node* tail;
};

#endif
