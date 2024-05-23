#include "Counter.h"

// Counter Member Functions
Counter::Counter() {}
Counter::~Counter() {}

size_t Counter::count() const {
    size_t count = 0;
    List::Node* temp = index.list.getHead();
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}
int    Counter::total() const {
    int sum = 0;
    List::Node* temp = index.list.getHead();
    while (temp != nullptr) {
        sum += temp->value;
        temp = temp->next;
    }
    return sum;
}

void Counter::inc(const std::string& key, int by) {
    index.increment(key, index.get(key) + by); // The inc(), dec(), and set() functions will add keys to the counter if they are not already present.
}
void Counter::dec(const std::string& key, int by) {
    index.increment(key, index.get(key) - by); // decrement is just a negative increment
}
void Counter::del(const std::string& key) { // The del() function is the only function that removes keys;
    index.remove(key);                      // setting a value to zero does not remove the corresponding key
}
int  Counter::get(const std::string& key) const {
    return index.get(key); // looks up a count by key. If the key isn't present, it returns zero.
}
void Counter::set(const std::string& key, int count) {
    index.increment(key, count); //  sets a count by key.
}

Counter::Iterator Counter::begin() const {
    return Iterator(index.list.getHead()); // loaded constructor
}
Counter::Iterator Counter::end() const {
    return Iterator(nullptr); // default constructor is nullptr
}