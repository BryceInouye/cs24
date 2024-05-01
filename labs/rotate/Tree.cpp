#include "Tree.h"
#include <iostream>

// Tree Function Implementations
Tree::Tree() {
    nodeArray = NULL;
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

void Tree::createArray() {
    if (root == NULL) {
        nodeArray = NULL;
        return;
    }
    nodeArray = new std::string[numNodes];
    size_t index = 0;
    recursiveCreateArray(root, nodeArray, index);
    std::cout << std::endl;
}
void Tree::recursiveCreateArray(Node* ptr, std::string* &nodeArray, size_t &index) {
    if (ptr->left != NULL) {
        recursiveCreateArray(ptr->left, nodeArray, index);
    }
    nodeArray[index++] = ptr->data;
    if (ptr->right != NULL) {
        recursiveCreateArray(ptr->right, nodeArray, index);
    }
}
void Tree::insert(const std::string& s){
    recursiveInsert(root, s);
    numNodes++; // update the count of nodes
    // createArray();
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
    recursivePrint(root);
    std::cout << std::endl;
    return;
}
void Tree::recursivePrint(Node* ptr) const{
    if (ptr == NULL) { // do nothing if tree is empty
        std::cout << "-";
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
    for (size_t i = 0; i < numNodes; i++) {
        if (nodeArray[i] == s) {
            return true;
        }
    }
    return false;
}
// replaced with the array

// bool Tree::recursiveContains(Node* ptr, const std::string& s) const{ 
//     // 1. check current node
//     // 1.5 if current node is null, return false, this means that it reached the end of the tree
//     // 2. if node is less than current, go left, else go right
//     if (ptr == NULL) {
//         return false;
//     }
//       else if (ptr->data == s) {
//         return true;
//     } else if (s < ptr->data) {
//         return recursiveContains(ptr->left, s);
//     } else {
//         return recursiveContains(ptr->right, s);
//     }
// }

size_t Tree::find(const std::string& s) const {
    // tree nodes need to be indexed for this to work
    // alternatively, we take the (num nodes / 2) and add for numbers greater than mid, and sub for numbers less than mid 
    for (size_t i = 0; i < numNodes; i++) {
        if (nodeArray[i] == s) {
            return i;
        }
    }
    std::cout << "not found" << std::endl;
    return 0;
}
std::string Tree::lookup(size_t index) const {
    
    if (index >= numNodes) {
        std::cout << "bad index!" << std::endl;
        throw std::out_of_range("out of range!");
    }
    return nodeArray[index];
}
void Tree::remove(size_t index) {
    // use lookup to find where it is
    std::string removeNode = lookup(index);
    // if node->adjacent == NULL, then delete node. 
    // operations will be easier if keeping track of 
    // if node 1 child, previous->left = current->left so 1->5->7 becomes 1->7; check using current left->left left->right right->right right->left
    // if (removeNode->left == NULL && removeNode->right == NULL) {
    //      delete removeNode;
    // } else if (removeNode->left != NULL && removeNode->right != NULL) {

    // } else {

    // }
    
    return;
}

void Tree::balance() {
    return;
}