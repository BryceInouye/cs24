#include "Index.h"

// Index Member Functions
Map::~Map() {
    for (int i = 0; i < bucketCount; ++i) {
        chainNode* current = chain[i];
        while (current != nullptr) {
            chainNode* toDelete = current;
            current = current->next;
            delete toDelete;
        }
    }
    delete[] chain;
}

int Map::calcHash(const std::string KEY) const {
                                         // djb2 hash algorithm
    unsigned long hash = 5381;           // uses two prime numbers for a better distribution
    for (size_t i = 0; i < KEY.length(); i++) {         
        hash = (hash << 4) + hash;       // it multiplies by a prime number that is 1 from a power of 2 for quick computation. << 4 = *2^4    
        hash += KEY[i];                  // the ASCII value is added to hash to also help with distribution
    }
    return hash;
}

Node* Map::find(const std::string KEY) const {
    // compute the index of chain using the calcHash function. then go through the linked list at the calculated bucket
    int index = calcHash(KEY) % bucketCount; // calculated hash mod bucketCount guarantees a legitimate bucket
    chainNode* current = chain[index];
    if (current == nullptr) { // added null pointer check
        return nullptr;
    }
    while (current != nullptr) {
        if (current->key == KEY) {
            return current->node; // return chainNode if matches key
        }
        current = current->next;
    }
    return nullptr; // key not found
}

void Map::insert(const std::string KEY, Node* value) { // add node to single linked list, runs in constant time since it iterates through the entire list. can be improved by implementing tail pointer
    int index = calcHash(KEY) % bucketCount; // same method as find()
    chainNode* current = new chainNode(KEY, value);
    if (chain[index] == nullptr) { // if list is empty
        chain[index] = current;
    } else {
        chainNode* end = chain[index];
        while (end->next != nullptr) { // iterate until empty spot
            end = end->next;
        }
        end->next = current; // add to the end of the list
    }
}

void Map::remove(Node* KEY) {
    // Assuming KEY is the key of the node to be removed
    int index = calcHash(KEY->key) % bucketCount;
    chainNode* current = chain[index];
    chainNode* preCurrent = nullptr;
    while (current != nullptr) {
        if (current->node == KEY) {
            if (preCurrent == nullptr) {
                chain[index] = current->next;
            } else {
                preCurrent->next = current->next;
            }
            delete current;
            return;
        }
        preCurrent = current;
        current = current->next;
    }
}