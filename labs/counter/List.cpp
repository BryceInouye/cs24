#include "List.h"

// List Member Functions
List::List() {
    head = nullptr;
    tail = nullptr;
    numNodes = 0;
}
List::~List() {
    Node* temp = head;
    while(temp != nullptr) {
        Node* temp1 = temp;
        temp = temp->next;
        delete temp1;
    }
}
void List::insert(const std::string& KEY, int VALUE) { // insertion at the tail
    Node* node = new Node(KEY, VALUE);
    if (head == nullptr) { // if list is empty
        head = node;
        tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    numNodes++;
}
void List::remove(Node* KEY){ // removal of any node
    // update the pointers adjacent to the node that is to be deleted
    // end of list: delete and update tail to be tail->prev
    // front of list: delete and update head to be head->next
    // middle of list: make deleted node->prev point to deleted node->next, do same for other direction
    
    if (KEY == nullptr) return; // if empty list

    if (KEY == head && KEY == tail) { // list is size 1
        head = nullptr;
        tail = nullptr;
    } else if (KEY == head) { // head removal
        head = KEY->next;
        KEY->next->prev = nullptr;
    } else if (KEY == tail) { // tail removal
        tail = KEY->prev;
        tail->next = nullptr;
    } else { // middle removal
        KEY->next->prev = KEY->prev;
        KEY->prev->next = KEY->next;
    }
    delete KEY;
    numNodes--;
}
List::Node* List::find(const std::string& KEY) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->key == KEY) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

size_t List::getNumNodes() const {
    return numNodes;
}

int List::sumNodes() const {
    Node* temp = head;
    int sum = 0;
    while (temp != nullptr) {
        sum += temp->value;
        temp = temp->next;
    }
    return sum;
}

List::Node* List::getHead() const {
    return head;
}
List::Node* List::getTail() const {
    return tail;
}
