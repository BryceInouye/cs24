#ifndef INDEX_H
#define INDEX_H
#include <string>
#include "List.h"

struct chainNode { // separate struct from class
    std::string key;
    Node* node;
    chainNode* next;
    chainNode(std::string x, Node* y) : key(x), node(y), next(nullptr) {}
};

class Map {
    private:
// member variables
    const int bucketCount = 11; // prime number yields less collisions. memory should not be an issue so we create a large table
    chainNode** bucket = new chainNode*[bucketCount] {nullptr};
    
    public:
        Map() {}
        ~Map();

        int calcHash(const std::string str) const; // used to determine bucket
        Node* find(const std::string KEY) const; // return desired node of chain
        void insert(const std::string KEY, Node* value); // add node to single linked list 
        void remove(Node* KEY); // remove node from linked list

};

#endif