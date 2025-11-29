#include "node.hpp"
#include <iostream>
using namespace std;

Node::Node(CrewMember* crew) {
    data = crew;
    next = nullptr;
}

Node::~Node()  {
    if (data != nullptr) {
        delete data;
        data = nullptr;
    }
}

CrewMember* Node::getData() const {
    return data;
}

void Node::setNext(Node* node) {
    next = node;
}

Node* Node::getNext() const {
    return next;
}

