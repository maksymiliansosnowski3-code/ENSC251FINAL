#include "node.hpp"

// Constructor
Node::Node(CrewMember* crew) {
    data = crew;
    next = nullptr;
}

// Destructor
Node::~Node() {
    delete data;
}

// Getters and Setters
CrewMember* Node::getData() const {
    return data;
}

// get the next node
Node* Node::getNext() const {
    return next;
}

// set the next node
void Node::setNext(Node* node) {
    next = node;
}
