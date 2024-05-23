#ifndef LIST_H
#define LIST_H
#include <string>
// create node struct
// create doubly linked list functions
// The list should support insertion at the tail, finding the node that contains a given string, and removal of any node.


class List {
    public:
    struct Node {
        std::string key;
        int value;
        Node* prev;
        Node* next;
    };

    private:
    Node* head;
    Node* tail;

    public:
    List();
    ~List();

    Node* insert(const std::string& KEY, int VALUE);
    void remove(Node* KEY);
    Node* find(const std::string& key) const;
    Node* getHead() const;
    Node* getTail() const;
        
};

#endif
