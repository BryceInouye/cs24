#include "Index.h"

// Index Member Functions
Map::Map() {
    chain = new chainNode*[bucketCount];
    for (size_t i = 0; i < bucketCount; i++) {
        chain[i] = nullptr;
    }
}
Map::~Map() {
    for (size_t i = 0; i < bucketCount; i++) { // same method as list.cpp destructor
        chainNode* current = chain[i]; // get the current bucket then delete the list associated with it
        while (current != nullptr) {
            chainNode* next = current->next;
            delete current;
            current = next;
        } 
    }
    delete[] chain; // memory allocation issue 
}

List::Node* Map::get(const std::string& key) const {
    // compute the index of chain using the calcHash function. then go through the linked list at the calculated bucket
    int index = calcHash(key) % bucketCount; // calculated hash mod bucketCount guarantees a legitimate bucket
    chainNode* current = chain[index];
    while (current != nullptr) {
        if (current->key == key) {
            return current->node; // return chainNode if matches key
        }
        current = current->next;
    }
    return nullptr; // key not found
}

void Map::add(const std::string& key, List::Node* value){ // add node to single linked list, runs in constant time since it iterates through the entire list. can be improved by implementing tail pointer
    int index = calcHash(key) % bucketCount; // same method as get()
    chainNode* current = chain[index]; 
    if (current == nullptr) { // if list is empty
        chain[index] = new chainNode(key, value);
    } else {
        while (current->next != nullptr) { // iterate until empty spot
            current = current->next;
        }
        current->next = new chainNode(key, value); // add to the end of the list
    }
}

void Map::remove(const std::string& key){ // remove node from single linked list
    int index = calcHash(key) % bucketCount;
    chainNode* current = chain[index];
    chainNode* preCurrent = nullptr;
    while (current != nullptr) {
        if (current->key == key) {
            if (preCurrent == nullptr) {
                chain[index] = current->next;
            } else {
                preCurrent->next = current->next;
            }
            delete current;
            break;
        }
        preCurrent = current;
        current = current->next;
    }
}

int Map::calcHash(const std::string& key) const {
                                         // djb2 hash algorithm
    unsigned long hash = 5381;           // uses two prime numbers for a better distribution
    for (size_t i = 0; i < key.length(); i++) {         
        hash = (hash << 4) + hash;       // it multiplies by a prime number that is 1 from a power of 2 for quick computation    
        hash += key[i];                  // the ASCII value is added to hash to also help with distribution
    }
    return hash;
}
