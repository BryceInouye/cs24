#include "Index.h"

// Index Member Functions
Map::~Map(){
    for(int i = 0; i < bucketCount; ++i){
        chainNode* current;
        while((current = bucket[i])){
            bucket[i] = current->next;
            delete current;
        }
    }
    delete[] bucket;
}

int Map::calcHash(const std::string KEY) const {
                                         // djb2 hash algorithm
    unsigned long hash = 5381;           // uses two prime numbers for a better distribution
    for (size_t i = 0; i < KEY.length(); i++) {         
        hash = (hash << 4) + hash;       // it multiplies by a prime number that is 1 from a power of 2 for quick computation. << 4 = *2^4    
        hash += KEY[i];                  // the ASCII value is added to hash to also help with distribution
    }
    return hash % bucketCount;
}

Node* Map::find(const std::string KEY) const {
    // compute the index of chain using the calcHash function. then go through the linked list at the calculated bucket
    // calculated hash mod bucketCount guarantees a legitimate bucket
    for(chainNode* current = bucket[calcHash(KEY)]; current; current = current->next){ 
        if(current->key == KEY) {
            return current->node;
        }
    }
    return nullptr; 
}

void Map::insert(const std::string KEY, Node* value){  // add node to single linked list, runs in constant time since it iterates through the entire list. can be improved by implementing tail pointer
    int hashValue = calcHash(KEY); // same method as find()
    chainNode* newNode = new chainNode(KEY, value); // FIXED: properly utilizing memory allocated here
    if(bucket[hashValue] == nullptr){ // if list is empty
        bucket[hashValue] = newNode; // fixed seg fault. properly assigning values to the chain linked list. before they were all set to null
    } 
    else{
        chainNode* end = bucket[hashValue];
        while(end->next != nullptr){ // iterate until empty spot
            end = end->next;
        }
        end->next = newNode; // add to the end of the list
    }
}

void Map::remove(Node* KEY) {
    // Assuming KEY is the node key to be removed
    int hashValue = calcHash(KEY->key);
    chainNode** current = &bucket[hashValue];
    while(*current) { // single linked list deletion
        if((*current)->key == KEY->key) {
            chainNode* toDelete = *current;
            *current = (*current)->next;
            delete toDelete;
            return;
        }
        current = &(*current)->next;
    }
}