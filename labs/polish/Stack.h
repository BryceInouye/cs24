#ifndef STACK_H
#define STACK_H
#include "Nodes.h"

// Use this file to define your Stack type.
// Implement its member functions in Stack.cpp.
struct Node { // used for creating linked list
            AST* data;
            Node* next;
        };
class Stack {
    public:
        Stack();
        ~Stack();
        void push(AST* node);
        AST* pop();
        AST* top();
        // double count();
    private:
        Node* head; // head is the top of the stack
};

#endif
