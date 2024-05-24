#include "Counter.h"
#include "Index.h"
#include "List.h"

// Counter Member Functions

size_t Counter::count() const {
    size_t i = 0;
    for (auto itr = this->begin(); itr != this->end(); ++itr) {
        i++;
    }
    return i;
}
int    Counter::total() const {
    int total = 0;
    for (auto itr = this->begin(); itr != this->end(); ++itr) {
        total += itr.value();
    }
    return total;
}

void Counter::inc(const std::string& key, int by) {
    auto keyNode = map.find(key); // change auto to see if i was declaring wrong type to keyNode
    if (keyNode != nullptr){
        keyNode->value += by;
    } else {
        Node* keyNode = list.insert(key, by); // The inc(), dec(), and set() functions will add keys to the counter if they are not already present.
        map.insert(key, keyNode);
    }
}
void Counter::dec(const std::string& key, int by) {
    auto keyNode = map.find(key);
    if (keyNode != nullptr){
        keyNode->value -= by;
    } else {
        Node* keyNode = list.insert(key, -by);
        map.insert(key, keyNode);
    }
}
void Counter::del(const std::string& key) { // The del() function is the only function that removes keys;
    auto keyNode = map.find(key); // setting a value to zero does not remove the corresponding key
    if(keyNode != nullptr){
        map.remove(keyNode);
        list.remove(keyNode);
    }
}
int  Counter::get(const std::string& key) const {
    auto keyNode = map.find(key); // looks up a count by key. If the key isn't present, it returns zero.
    return (keyNode) ? keyNode->value : 0; // swapped
}
void Counter::set(const std::string& key, int count) {
    auto keyNode = map.find(key); //  sets a count by key
    if(keyNode != nullptr){
        keyNode->value = count;
    }
    else{
        Node* keyNode = list.insert(key, count);
        map.insert(key, keyNode);
    }
}

Counter::Iterator Counter::begin() const {
    Counter::Iterator iterator(list.getHead()); // loaded constructor
    return iterator;
}
Counter::Iterator Counter::end() const {
    Counter::Iterator iterator; // default constructor is nullptr
    return nullptr;
}