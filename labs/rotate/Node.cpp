#include "Node.h"

// NOTE: moved ALL node weight calculations to tree.cpp
Node::Node(const std::string s, Node* L, Node* R) {
    data = s;
    left = L;
    right = R;
}