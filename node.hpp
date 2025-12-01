#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "crewmember.hpp"
using namespace std;

class Node {
public:
    // constructor and destructor
    Node(CrewMember* crew);
    ~Node();

    // getters and setters
    CrewMember* getData() const;
    Node* getNext() const;
    void setNext(Node* node);

private:
    // member variables
    CrewMember* data;
    Node* next;
};

#endif
