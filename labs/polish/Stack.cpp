#include "Stack.h"
#include <iostream>

// Implement your Stack member functions here.
Stack::Stack() {
    head = nullptr;
}
Stack::~Stack() {
    while (head != NULL) {
        Node* temp = head;
        head = head->next;
        delete temp->data;
        delete temp;
    } 
    head = nullptr;
}
void Stack::push(AST* node) {
    Node* temp = new Node;
    temp->data = node;
    if (head == NULL) {
        head = temp;
        head->next = NULL;
    } else {
        temp->next = head;
        head = temp;
    }
    return;
}

AST* Stack::pop() { // top of the stack is the head
    if (head == NULL) {
        throw std::runtime_error("pop: trying to pop from empty list!");
        return nullptr;
    }
    Node* temp = head;
    AST* deletedData = head->data; // return value = head contents (tree node)
    head = head->next;
    delete temp;
    return deletedData; // the data is still on heap somewhere probably. make sure it gets deleted
}

AST* Stack::top() {
    if (head == NULL) {
        throw std::runtime_error("top: trying to access head of empty stack!");
        return nullptr;
    }
    return head->data;
}

// double Stack::count() {
//     if (head == NULL) {
//         return 0;
//     }
//     size_t i = 1; // i = counter
//     Node* temp = head;
//     while (temp->next != NULL) {
//         temp = temp->next;
//         i++;
//     }
//     return i;
// }