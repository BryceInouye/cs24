
#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
    list = new List(); // doubly linked list
}
Counter::~Counter() {
    delete list;
}

size_t Counter::count() const {
    return list->getNumNodes();
}
int    Counter::total() const {
    return list->sumNodes();
}

void Counter::inc(const std::string& key, int by) {
    List::Node* keyNode = list->find(key);
    if (keyNode != nullptr) 
        keyNode->value = keyNode->value + by;
    else 
        list->insert(key, by); // The inc(), dec(), and set() functions will add keys to the counter if they are not already present.
}
void Counter::dec(const std::string& key, int by) {
    List::Node* keyNode = list->find(key);
    if (keyNode != nullptr) 
        keyNode->value = keyNode->value - by;
    else
        list->insert(key, -by);
}
void Counter::del(const std::string& key) { // The del() function is the only function that removes keys;
    List::Node* keyNode = list->find(key);  // setting a value to zero does not remove the corresponding key
    list->remove(keyNode);
}
int  Counter::get(const std::string& key) const {
    List::Node* keyNode = list->find(key); // looks up a count by key. If the key isn't present, it returns zero.
    return (keyNode == nullptr) ? 0 : keyNode->value;
}
void Counter::set(const std::string& key, int count) {
    List::Node* keyNode = list->find(key); //  sets a count by key.
    if (keyNode != nullptr) 
        keyNode->value = count;
    else 
        list->insert(key, count);
}

Counter::Iterator Counter::begin() const {
    Counter::Iterator iterator(list->getHead()); // loaded constructor
    return iterator;
}
Counter::Iterator Counter::end() const {
    Counter::Iterator iterator; // default constructor is nullptr
    return iterator;
}