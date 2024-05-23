#include "List.h"

// List Member Functions
List::List() {
    head = nullptr;
    tail = nullptr;
}
List::~List() {
    Node* temp = head;
    while (temp != nullptr) {
        Node* temp1 = temp->next;
        delete temp;
        temp = temp1;
    }
}
List::Node* List::insert(const std::string& KEY, int VALUE) {
    Node* temp = new Node;
    temp->key = KEY;
    temp->value = VALUE;
    temp->prev = nullptr;
    temp->next = nullptr;
    return temp;
}
void List::remove(Node* KEY) {
    if (KEY == nullptr) {
        return;
    }

    if (KEY == head && KEY == tail) { // list size = 1
        head = nullptr;
        tail = nullptr;
    } else if (KEY == head) {
        head = KEY->next;
        head->prev = nullptr;
    } else if (KEY == tail) {
        tail = KEY->prev;
        tail->next = nullptr;
    } else {
        KEY->prev->next = KEY->next;
        KEY->next->prev = KEY->prev;
    }
    delete KEY;
}
List::Node* List::find(const std::string& key) const {
    Node* temp = head;
    while(temp != nullptr) {
        if (temp->key == key) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}
List::Node* List::getHead() const {
    return head;
}
List::Node* List::getTail() const {
    return tail;
}