#include "Tree.h"
#include <iostream>

// Tree Function Implementations
Tree::Tree() {
    root = NULL;
    numNodes = 0;
}
Tree::~Tree() {
    clear();
}

Node* Tree::createLeaf(const std::string& s) {
    Node* ptr = new Node(s);
    return ptr;
}

void Tree::insert(const std::string& s){
    recursiveInsert(root, s);
    numNodes++; // update the count of nodes
    balance();
    return;
}
void Tree::recursiveInsert(Node* ptr, const std::string& s) {
    if (root == NULL) { // if current tree is empty
        root = createLeaf(s);
    } else if (s <= ptr->data) {
        if (ptr->left != NULL) {
            recursiveInsert(ptr->left, s);
        } else {
            ptr->left = createLeaf(s);
        }
    } else {
        if (ptr->right != NULL) {
            recursiveInsert(ptr->right, s);
        } else {
            ptr->right = createLeaf(s);
        }
    }
    return;
}

void Tree::print() const {
    // std::cout << "root is: " << root->data << std::endl;
    recursivePrint(root);
    return;
}
void Tree::recursivePrint(Node* ptr) const{
    if (ptr == NULL) { // do nothing if tree is empty
        std::cout << "tree is empty!";
    } else {
        if ((ptr->left != NULL) || (ptr->right != NULL)) {
            std::cout << "(";
            if (ptr->right != NULL && ptr->left == NULL) {
                std::cout << "- ";
            }
        }
        if (ptr->left != NULL) {
            recursivePrint(ptr->left);
            std::cout << " ";
        }
        std::cout << ptr->data;
        if (ptr->right != NULL) {
            std::cout << " ";
            recursivePrint(ptr->right);
        }
        if ((ptr->left != NULL) || (ptr->right != NULL)) {
            if (ptr->right == NULL && ptr->left != NULL) {
                std::cout << " -";
            }
            std::cout << ")";
        }
    }
    return;
}

size_t Tree::count() const {
    return numNodes; // instead of recursive count, the weight of the parent root is the weight of the tree
}

void Tree::clear() {
    if (root != NULL) { 
        recursiveClear(root);
    }
    root = NULL;
    numNodes = 0;
    return;
}
void Tree::recursiveClear(Node* ptr) {
    if (ptr == NULL) { // do nothing if tree is empty
        return;
    } else if (ptr != NULL) {
        if (ptr->left != NULL) {
            recursiveClear(ptr->left);
        }
        if (ptr->right != NULL) {
            recursiveClear(ptr->right);
        }
        delete ptr;
    }
    return;
}

bool Tree::contains(const std::string& s) const {
    return recursiveContains(root, s);
}
bool Tree::recursiveContains(Node* ptr, const std::string& s) const{
    // 1. check current node
    // 1.5 if current node is null, return false, this means that it reached the end of the tree
    // 2. if node is less than current, go left, else go right
    if (ptr == NULL) {
        return false;
    }
      else if (ptr->data == s) {
        return true;
    } else if (s < ptr->data) {
        return recursiveContains(ptr->left, s);
    } else {
        return recursiveContains(ptr->right, s);
    }
}

size_t Tree::find(const std::string& s) const {
    // tree nodes need to be indexed for this to work
    // alternatively, we take the (num nodes / 2) and add for numbers greater than mid, and sub for numbers less than mid 

    return 0;
}
std::string Tree::lookup(size_t index) const {
    return 0;
}
void Tree::remove(size_t index) {
    // use lookup to find where it is
    return;
}

void Tree::balance() {
    return;
}