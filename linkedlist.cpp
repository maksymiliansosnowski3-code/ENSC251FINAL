#include <iostream>
#include <string>
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

    while (curr->getNext() != nullptr && !(*(newNode->getData()) > *(curr->getNext()->getData()))) {
        curr = curr->getNext();
    }

    newNode->setNext(curr->getNext());
    curr->setNext(newNode);

    if (newNode->getNext() == nullptr) {
        tail = newNode;
    }



}

void LinkedList::searchByID(int id) const {
    Node* curr = head;
    bool found = false;
    string target = StringManip::toUpper(name);

    while (curr != nullptr){
        if (StringManip::toUpper(current->getData()->getName()) == target) {
            current->getData()->printInfo();
            found = true;
        }
        current = current->getNext();
    }
    
}