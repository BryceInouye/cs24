#include "Node.h"
# include <cmath>

// Node::Node() {
//     left = right = NULL;
//     weight = imbalance = 0;

// }
Node::Node(const std::string& s) {
    data = s;
    left = right = NULL;
    weight = 1;
    imbalance = 0;
}
Node::~Node(){
    
}

int Node::calcWeight() {
    int count = 1;
    if (left != NULL) {
        count += left->calcWeight();
    }
    if (right != NULL) {
        count += right->calcWeight();
    }
    return count;
}

void Node::calcImbalance() {
    int leftWeight = 0;
    int rightWeight = 0;
    if (left != NULL) {
        leftWeight += left->calcWeight();
    }
    if (right != NULL) {
        rightWeight += right->calcWeight();
    }
    imbalance = fabs(leftWeight - rightWeight);
}