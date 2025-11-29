#include "node.hpp"

Node::Node(CrewMember* crew) {
    data = crew;
    next = nullptr;
}

Node::~Node() {
    delete data;
}

CrewMember* Node::getData() const {
    return data;
}

Node* Node::getNext() const {
    return next;
}

void Node::setNext(Node* node) {
    next = node;
}
