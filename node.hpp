#ifndef LIST_HPP
#define LIST_HPP

#include <iostream>
#include "crewmember.hpp"
using namespace std;

class Node {
public:
    Node(CrewMember* crew);
    ~Node();

    CrewMember* getData() const;
    Node* getNext() const;
    void setNext(Node* node);

private:
    CrewMember* data;
    Node* next;
};

#endif
