
#ifndef LIST_H
#define LIST_H
#include <string>
// create node struct
// create doubly linked list functions
// The list should support insertion at the tail, finding the node that contains a given string, and removal of any node.

    struct Node { // separating nested class for simplicity
    Node* next;
    Node* prev;
    std::string key;
    int value;
    Node(const std::string& x, int y) : next(nullptr), prev(nullptr), key(x), value(y) {} // node constructor
};
class List {
    public:
        Node* head;
        Node* tail;
    public:
        List();
        ~List();
        Node* insert(const std::string KEY, int VALUE);
        void remove(Node* nodeToDelete); // string of the node to be deleted
        Node* find(const std::string KEY) const;
        Node* getHead() const;
        Node* getTail() const;
};

#endif