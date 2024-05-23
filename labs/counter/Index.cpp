#include "Index.h"
#include <cstring>
#include <iostream>

// Index Member Functions
Index::Index() {
    for (size_t i = 0; i < bucketCount; ++i) {
        hashTable[i] = nullptr;
    }
}
Index::~Index() {
    // iterate over each bucket in the hash table
    for (size_t i = 0; i < bucketCount; ++i) {
        List::Node* current = hashTable[i];
        // traverse the linked list in the current bucket and delete each node
        while (current != nullptr) {
            List::Node* temp = current;
            current = current->next;
            delete temp;
        }
        // after deleting all nodes, set the bucket to nullptr
        hashTable[i] = nullptr;
    }
}

int Index::get(const std::string& key) const { // return the value of a specified key
    int index = stringHash(key);
    // each bucket represents a linked list where each index corresponds to a key
    if (hashTable[index] != nullptr && // check if the key is at the front of the list
        hashTable[index] != (List::Node*)1 && 
        hashTable[index]->key == key){
        return hashTable[index]->value;
    } else {
        int probingIndex = (index + 1) % bucketCount;
        while (hashTable[probingIndex] != nullptr) { // iterate through a bucket
            if (hashTable[probingIndex] != (List::Node*)1 && hashTable[probingIndex]->key == key) {
                return hashTable[probingIndex]->value;
            }
            probingIndex++;
            probingIndex %= bucketCount;
        }
    }
    return 0; // key is not found
}
void Index::increment(const std::string& key, int val) {
    int index = stringHash(key);
    int num = -1;
    bool modifiedIndex = false;

    if (hashTable[index] != nullptr &&              // if the bucket is not empty
        hashTable[index] != (List::Node*)1 &&       // if the bucket is not marked as "dirty"
        hashTable[index]->key == key) {             // if the key in the bucket matches the desired key
        hashTable[index]->value = val;         // if all conditions are met, update the value associated with the key
        return;
    } else if (hashTable[index] == nullptr) {
        hashTable[index] = list.List::insert(key, val);
        return;
    } else if (hashTable[index] == (List::Node*)1) {
        num = index;
        modifiedIndex = true;
    }

    int probingIndex = (index + 1) % bucketCount;
    while (probingIndex != index) {
        if (!modifiedIndex && hashTable[probingIndex] == (List::Node*)1) {
            num = probingIndex;
            modifiedIndex = true;
        }

        if (hashTable[probingIndex] == nullptr) {
            if (modifiedIndex == true) {
                probingIndex = num;
            }
            hashTable[probingIndex] = list.List::insert(key, val);
            return;
        } else if (hashTable[probingIndex] != (List::Node*)1 && hashTable[probingIndex]->key ==key) {
            hashTable[probingIndex]->value = val;
            return;
        }
        probingIndex++;
        probingIndex %= bucketCount;
    }
}
void Index::remove(const std::string& key) {
    int index = stringHash(key);

    if (hashTable[index] != nullptr && 
        hashTable[index] != (List::Node*)1 && 
        hashTable[index]->key == key) {
        list.List::remove(hashTable[index]);
        hashTable[index] = (List::Node*)1;
        return;
    }

    int probingIndex = (index + 1) % bucketCount;
    while (probingIndex != index) {
        if (hashTable[probingIndex] != nullptr && 
            hashTable[probingIndex] != (List::Node*)1 && 
            hashTable[probingIndex]->key == key) {
            list.List::remove(hashTable[probingIndex]);
            hashTable[probingIndex] = (List::Node*)1;
            return;
        }
        probingIndex++;
        probingIndex %= bucketCount;
    }
}

int Index::stringHash(const std::string& key) const {
    int startingValue = 149;
    int multiplier = 137;
    // generate a hash value for the key
    for (size_t i = 0; i < key.length(); ++i) {
        startingValue *= multiplier;
        startingValue += key[i];
        startingValue %= bucketCount;
    }
    return startingValue % bucketCount;
}