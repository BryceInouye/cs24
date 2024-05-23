#include "Counter.h"

// Counter::Iterator Member Functions

Counter::Iterator::Iterator(List::Node* node) {
    currentNode = node;
}

const std::string& Counter::Iterator::key() const {
    return currentNode->key;
}
int Counter::Iterator::value() const {
    return currentNode->value;
}

void Counter::Iterator::operator ++ () {
    currentNode = currentNode->next;
}
bool Counter::Iterator::operator == (const Iterator& other) const {
    return (currentNode == other.currentNode);
}
bool Counter::Iterator::operator != (const Iterator& other) const {
    return (currentNode != other.currentNode);
}
