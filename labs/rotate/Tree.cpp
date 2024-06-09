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
    delete[] nodeArray;
    if (root == NULL || numNodes == 0) {    
        nodeArray = NULL;
        return;
    }
    nodeArray = new std::string[numNodes];
    size_t index = 0;
    recursiveCreateArray(root, nodeArray, index);
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
    delete[] nodeArray;
    nodeArray = NULL;
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
    return -1;
}
std::string Tree::lookup(size_t index) const {
    
    if (index >= numNodes) {
        throw std::out_of_range("out of range!");
    }
    return nodeArray[index];
}
void Tree::remove(size_t index) {
    if(index >= numNodes){
        throw std::out_of_range("out of range!");
    }
    if (numNodes == 1) {
        clear();
        return;
    }

    std::string value = lookup(index);
    Node* curr = root;
    while (curr != nullptr) {
        if (curr->data == value) {
            break;
        }
        curr = value < curr->data ? curr->left : curr->right;
    }

    if (curr != nullptr) {
        Node* temp1 = curr->parent;
        while(temp1 != nullptr){
            temp1->weight--;
            temp1 = temp1->parent;
        }
    }

    if(curr == root){
        Node* temp = curr->right;
        // check if temp is not null before entering the while loop
        if(temp != nullptr){
            while(temp->left != nullptr){
                temp = temp->left;
            }
            handleRootRemoval(curr, temp);
        }
    }
    else{
        if(curr->left == nullptr && curr->right == nullptr){
            handleNoChildren(curr);
        }
        else if(curr->left == nullptr && curr->right != nullptr){
            handleOneChild(curr, curr->right);
        }
        else if(curr->left != nullptr && curr->right == nullptr){
            handleOneChild(curr, curr->left);
        }
        else {
            handleTwoChildren(curr);
        }
    }
    numNodes--;
}

void Tree::handleRootRemoval(Node* curr, Node* temp){
    if(temp->parent != curr){
        temp->parent->left = temp->right;
        if(temp->right != nullptr){
            temp->right->parent = temp->parent;
        }
        temp->right = curr->right;
        curr->right->parent = temp;
    }
    temp->left = curr->left;
    curr->left->parent = temp;
    temp->parent = nullptr;
    root = temp;
    delete curr;
}

void Tree::handleNoChildren(Node* curr){
    if(curr->data > curr->parent->data){
        curr->parent->right = nullptr;
    }
    else{
        curr->parent->left = nullptr;
    }
    delete curr;
}

void Tree::handleOneChild(Node* curr, Node* child){
    if(curr->data > curr->parent->data){
        curr->parent->right = child;
    }
    else{
        curr->parent->left = child;
    }
    child->parent = curr->parent;
    Node* temp = curr->parent;
    while(temp != nullptr){
        if(curr->data > temp->data && temp->left != nullptr){
            rotate(temp, temp->left);
        }
        else if(curr->data <= temp->data && temp->right != nullptr){
            rotate(temp, temp->right);
        }
        temp = temp->parent;
    }
    delete curr;
}

void Tree::handleTwoChildren(Node* curr){
    Node* temp = curr->right;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    if(temp->right != nullptr){
        temp->right->parent = temp->parent;
    }
    if(temp->parent != curr){
        temp->parent->left = temp->right;
        temp->right = curr->right;
    }
    temp->parent = curr->parent;
    if(curr->parent == nullptr){
        root = temp;
    }
    else if(curr == curr->parent->left){
        curr->parent->left = temp;
    }
    else{
        curr->parent->right = temp;
    }
    temp->left = curr->left;
    curr->left->parent = temp;
    delete curr;
}

size_t Tree::calcWeight(Node* ptr) {
    return (ptr == nullptr ? 0 : ptr->weight);
}

void Tree::rotate(Node* head, Node* ptr) { 
    // return if the node to rotate is null
    if(ptr == nullptr) return;

    // calculate the imbalance of the head node
    int headImbalance = std::abs(static_cast<int>(calcWeight(head->left) - calcWeight(head->right)));

    // calculate the initial imbalance of the node to rotate
    int ptrImbalance = std::abs(static_cast<int>(calcWeight(ptr->left) + calcWeight(head->left) + 1 - calcWeight(ptr->right)));

    // if the data of the node to rotate is less than or equal to the head's data, recalculate the imbalance
    if(ptr->data <= head->data){
        ptrImbalance = std::abs(static_cast<int>(calcWeight(ptr->right) + calcWeight(head->right) + 1 - calcWeight(ptr->left)));
    }

    // return if the imbalance of the node to rotate is greater than or equal to the head's imbalance
    if(ptrImbalance >= headImbalance) return;

    // if the head is the root of the tree, update the root and the parent of the node to rotate
    if(head == root){
        ptr->parent = nullptr;
        root = ptr;
    }
    else{
        // update the parent's child pointer and the parent of the node to rotate
        if(head == head->parent->right){
            head->parent->right = ptr;
        }
        else{
            head->parent->left = ptr;
        }
        ptr->parent = head->parent;
    }

    // if the node to rotate is the right child of the head
    if(ptr == head->right){
        // update the weights of the node to rotate and the head
        ptr->weight = ptr->weight + calcWeight(head->left) + 1;
        head->weight = calcWeight(head->left) + calcWeight(ptr->left) + 1;

        // update the parent of the left child of the node to rotate if it exists
        if(ptr->left != nullptr){
            ptr->left->parent = head;
        }
        // update the right child of the head and the left child of the node to rotate
        head->right = ptr->left;
        ptr->left = head;
    }
    else{
        // update the weights of the node to rotate and the head
        ptr->weight = ptr->weight + calcWeight(head->right) + 1;
        head->weight = calcWeight(head->right) + calcWeight(ptr->right) + 1;

        // update the parent of the right child of the node to rotate if it exists
        if(ptr->right != nullptr){
            ptr->right->parent = head;
        }
        // update the left child of the head and the right child of the node to rotate
        head->left = ptr->right;
        ptr->right = head;
    }
    // update the parent of the head
    head->parent = ptr;
}


void Tree::insert(const std::string& s){
    // if (root != NULL) std::cout << "old root: " << root->data << std::endl;
    if (root == nullptr) {
        Node* newRoot = new Node();
        newRoot->data = s;
        root = newRoot;
    } else {
        recursiveInsert(root, s);
        root->weight = numNodes;
    }
    numNodes++; // update the count of nodes
    createArray();
    // std::cout << "new root: " << root->data << std::endl;
    return;
}                            // curr                     input
Node* Tree::recursiveInsert(Node* ptr, const std::string& s) {
    Node* temp = nullptr;

    if (s > ptr->data) {
        if (ptr->right != nullptr) {
            temp = recursiveInsert(ptr->right, s);
        } else {
            temp = new Node();
            temp->data = s;
            ptr->right = temp;
            temp->parent = ptr;
        }
    } else {
        if (ptr->left != nullptr) {
            temp = recursiveInsert(ptr->left, s);
        } else {
            temp = new Node();
            temp->data = s;
            ptr->left = temp;
            temp->parent = ptr;
        }
    }

    ptr->weight++;
    rotate(ptr, s > ptr->data ? ptr->right : ptr->left);

    return temp;
}
