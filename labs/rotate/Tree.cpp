
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
    // use lookup to find where it is
    // if node->adjacent == NULL, then delete node. 
    // operations will be easier if keeping track of 
    // if node 1 child, previous->left = current->left so 1->5->7 becomes 1->7; check using current left->left left->right right->right right->left
    // if (removeNode->left == NULL && removeNode->right == NULL) {
    //      delete removeNode;
    // } else if (removeNode->left != NULL && removeNode->right != NULL) {

    // } else {

    // }
    std::string removeNode = lookup(index);
    Node* ptr = root;
    Node* parentNode = NULL;
    
    while (ptr != NULL) {
        if (removeNode < ptr->data) {
            if (ptr->left != NULL) {
                parentNode = ptr;
                ptr = ptr->left;
            } else return;
        } else if (removeNode > ptr->data) {
            if (ptr->right != NULL) {
                parentNode = ptr;
                ptr = ptr->right;
            } else return;
        } else {
            break; // Found the node, break out of the loop
        }
    }
    if (ptr->left == NULL && ptr->right == NULL) { // Leaf node
        delete ptr;
        delete parentNode;
        numNodes--; // update the count of nodes
        createArray();
        return;
    }

    if (ptr->right != NULL && ptr->left != NULL) { // Two child nodes
        // std::string nextGreaterData = lookup(index + 1); // the next data in the array is the next data
        // Node* nextGreaterNode = ptr;
        // while (ptr->data != nextGreaterData) {
        //     if (nextGreaterData < nextGreaterNode->data) {
        //         if (nextGreaterNode->left != NULL) {
        //             nextGreaterNode = nextGreaterNode->left;
        //         } else return;
        //     } else if (nextGreaterData > nextGreaterNode->data) {
        //         if (nextGreaterNode->right != NULL) {
        //             nextGreaterNode = nextGreaterNode->right;
        //         } else return;
        //     } else {
        //         break; // now at the desired node
        //     }
        // }
        // Node* singleChildPtr = NULL;
        // if (nextGreaterNode->left != NULL) { // only one child maximum
        //     singleChildPtr = nextGreaterNode->left;
        // } else if (nextGreaterNode->right != NULL) {
        //     singleChildPtr = nextGreaterNode->right;
        // }
        return; // fix later
    }

    if (ptr->right != NULL) { // Has right child node: A->B->C becomes A->C
        parentNode->right = ptr->right;
        delete ptr;
        numNodes--; // update the count of nodes
        createArray();
    } else { // Has left child node: A<-B<-C becomes A<-C
        parentNode->left = ptr->left;
        delete ptr;
        numNodes--; // update the count of nodes
        createArray();
    }
    delete parentNode;
    return;
}




void Tree::rotate(Node* parent, Node* ptr, const bool side) {
//     if (ptr == NULL) return; // Handle empty tree case
//     ptr->calcImbalance(); // Calculate imbalance before rotation
//     int initialImbalance = ptr->imbalance;

//   // Perform rotation based on side
//     Node* swapPtr = NULL;
//     std::cout << "tree before balance: " << std::endl;
//     print();
//     if (side == true) { // Right rotation
//         swapPtr = ptr->left;
//         rightRotate(ptr);
//     } else { // Left rotation
//         swapPtr = ptr->right;
//         leftRotate(ptr);
//     }
    
//     if (parent != NULL) {
//     if (side) {
//         parent->left = swapPtr;
//     } else {
//         parent->right = swapPtr;
//     }
//     }
    

//     // calculate imbalance from swappedptr

//     swapPtr->calcImbalance();
//     int newImbalance = swapPtr->imbalance;
//     std::cout << "tree after balance: " << std::endl;
//     if (ptr == root) {
//      root = swapPtr;
//     }
//     print();
//     if (newImbalance >= initialImbalance) { // only rotate if new imbalance is less than previous
//         if (side == true) {
//             leftRotate(swapPtr);
//             if (parent != NULL) parent->right = ptr;
//         } else {
//             rightRotate(swapPtr);
//             if (parent != NULL) parent->left = ptr;
//         }
//         if (swapPtr == root) root = ptr;
//     }
    return;
}



void Tree::rightRotate(Node* ptr) {
    Node* tempPtr;
    tempPtr = ptr->left;
    ptr->left = tempPtr->right;
    tempPtr->right = ptr;

}

void Tree::leftRotate(Node* ptr) {
    Node* tempPtr;
    tempPtr = ptr->right;
    ptr->right = tempPtr->left;
    tempPtr->left = ptr;

}





void Tree::insert(const std::string& s){
    // if (root != NULL) std::cout << "old root: " << root->data << std::endl;
    recursiveInsert(root, s);
    numNodes++; // update the count of nodes
    createArray();
    // std::cout << "new root: " << root->data << std::endl;
    return;
}
void Tree::recursiveInsert(Node* ptr, const std::string& s) {
    Node* parent = NULL;
    if (root == NULL) { // if current tree is empty
        root = createLeaf(s);
    } else if (s <= ptr->data) {
        if (ptr->left != NULL) {
            parent = ptr;
            recursiveInsert(ptr->left, s);// right rotate after left insertion, vice versa for left rotate
            rotate(parent, ptr->left, true);
            return;
        } else {
            ptr->left = createLeaf(s);
            return;
        }
    } else {
        if (ptr->right != NULL) {
            recursiveInsert(ptr->right, s);
            rotate(parent, ptr->right, false);
        } else {
            ptr->right = createLeaf(s);
            return;
        }
    }
    return;
}
