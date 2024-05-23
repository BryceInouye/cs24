#ifndef INDEX_H
#define INDEX_H

#include <string>
#include "List.h"

class Index {
    public:
    //  public member variables
        List list;
    public:
    // public member functions

    Index();
    ~Index();
        int get(const std::string& key) const;
        void increment(const std::string& key, int val);
        void remove(const std::string& key);

    private:
        static const int bucketCount = 157; // prime number so that there is a greater number of quotients
        List::Node* hashTable[bucketCount]; // array to represent hash table
        int stringHash(const std::string& key) const;

};

#endif
