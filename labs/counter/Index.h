#ifndef INDEX_H
#define INDEX_H
#include <string>
#include "List.h"

class Map {
    public:
        struct chainNode {
            std::string key;
            List::Node* node;
            chainNode* next;
            chainNode(std::string x, List::Node* y) : key(x), node(y) {}
        };
    
    public:
        Map();
        ~Map();

        int calcHash(const std::string str) const; // used to determine bucket
        List::Node* get(const std::string& key) const; // return desired node of chain
        void add(const std::string& key, List::Node* value); // add node to single linked list 
        void remove(const std::string& key); // remove node from linked list
    
    private:
    // member variables
        static const int bucketCount = 101; // prime number yields less collisions. memory should not be an issue so we create a large table
        chainNode** chain = new chainNode*[bucketCount];

};

#endif