#include "List.h"

// List Member Functions
List::List() {
    head = tail = nullptr;
}
List::~List() {
        Node* temp = head;
    while(temp != nullptr) {
        Node* tempNext = temp->next;
        delete temp;
        temp = tempNext;
    }
}
Node* List::insert(const std::string KEY, int VALUE) { // insertion at the tail
    Node* node = new Node(KEY, VALUE);
    if (head == nullptr) { // if list is empty
        head = tail = node;
    } else {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    return node;
}
void List::remove(Node* void List::remove(Node* nodeToDelete){ // removal of any node
    // update the pointers adjacent to the node that is to be deleted
    // end of list: delete and update tail to be tail->prev
    // front of list: delete and update head to be head->next
    // middle of list: make deleted node->prev point to deleted node->next, do same for other direction
    
    if (nodeToDelete == nullptr) return; // if node not found

    if (nodeToDelete == head && nodeToDelete == tail) { // list is size 1
        head = nullptr;
        tail = nullptr;
    } else if (nodeToDelete == head) { // head removal
        head = nodeToDelete->next;
        if (head != nullptr) { // check if head is not null before accessing its member
            head->prev = nullptr;
        }
    } else if (nodeToDelete == tail) { // tail removal
        tail = nodeToDelete->prev;
        if (tail != nullptr) { // check if tail is not null before accessing its member
            tail->next = nullptr;
        }
    } else { // middle removal
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    delete nodeToDelete;
}){ // removal of any node
    // update the pointers adjacent to the node that is to be deleted
    // end of list: delete and update tail to be tail->prev
    // front of list: delete and update head to be head->next
    // middle of list: make deleted node->prev point to deleted node->next, do same for other direction
    
    if (nodeToDelete == nullptr) return; // if node not found

    if (nodeToDelete == head && nodeToDelete == tail) { // list is size 1
        head = nullptr;
        tail = nullptr;
    } else if (nodeToDelete == head) { // head removal
        head = nodeToDelete->next;
        if (head != nullptr) { // check if head is not null before accessing its member
            head->prev = nullptr;
        }
    } else if (nodeToDelete == tail) { // tail removal
        tail = nodeToDelete->prev;
        if (tail != nullptr) { // check if tail is not null before accessing its member
            tail->next = nullptr;
        }
    } else { // middle removal
        nodeToDelete->prev->next = nodeToDelete->next;
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    delete nodeToDelete;
}
Node* List::find(const std::string KEY) const {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->key == KEY) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

Node* List::getHead() const {
    return head;
}
Node* List::getTail() const {
    return tail;
}