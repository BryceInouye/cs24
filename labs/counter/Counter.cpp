#include "Counter.h"

// Counter Member Functions
Counter::Counter() {
    list = new List; // doubly linked list
    map = Map(); // initialize map
}
Counter::~Counter() {
    delete list;
}

size_t Counter::count() const {
    return list->getNumNodes();
}
int    Counter::total() const {
    int sum = 0;
    for (auto itr = this->begin(); itr != this->end(); ++itr) {
        sum += itr.value();
    }
    return sum;
}

void Counter::inc(const std::string& key, int by) {
    auto keyNode = map.get(key); // change auto to see if i was declaring wrong type to keyNode
    if (keyNode != nullptr) 
        keyNode->value += + by;
    else 
        list->insert(key, by); // The inc(), dec(), and set() functions will add keys to the counter if they are not already present.
        map.add(key, list->find(key)); // add key to map
}
void Counter::dec(const std::string& key, int by) {
    auto keyNode = map.get(key);
    if (keyNode != nullptr) 
        keyNode->value -= by;
    else
        list->insert(key, -by);
        map.add(key, list->find(key));
}
void Counter::del(const std::string& key) { // The del() function is the only function that removes keys;
    map.remove(key); // remove key from map
    list->remove(key);                  // setting a value to zero does not remove the corresponding key
}
int  Counter::get(const std::string& key) const {
    auto keyNode = map.get(key); // looks up a count by key. If the key isn't present, it returns zero.
    return (keyNode) ? keyNode->value : 0; // swapped
}
void Counter::set(const std::string& key, int count) {
    auto keyNode = map.get(key); //  sets a count by key.
    if (keyNode != nullptr) {
        keyNode->value = count;
    } else {
        list->insert(key, count);
        map.add(key, list->find(key));
    }
}

Counter::Iterator Counter::begin() const {
    Counter::Iterator iterator(list->getHead()); // loaded constructor
    return iterator;
}
Counter::Iterator Counter::end() const {
    Counter::Iterator iterator; // default constructor is nullptr
    return iterator;
}