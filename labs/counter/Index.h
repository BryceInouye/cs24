#ifndef INDEX_H
#define INDEX_H
#include <string>

struct Node;
class Map {
    public:
        struct chainNode {
            std::string key;
            Node* node;
            chainNode* next;
            chainNode(std::string x, Node* y) : key(x), node(y) {}
        };
    
    public:
        Map();
        ~Map();

        Node* get(const std::string& key); // return desired node of chain
        void add(const std::string& key, Node* value); // add node to single linked list 
        void remove(const std::string& key); // remove node from linked list
    
    private:
    // member variables
        static const int bucketCount = 32749; // prime number yields less collisions. memory should not be an issue so we create a large table
        chainNode** chain;

    private:
    // helper functions
        int calcHash(const std::string& str); // used to determine bucket
};

#endif