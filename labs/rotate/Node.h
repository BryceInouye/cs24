#ifndef NODE_H
#define NODE_H

#include <string>

// Node Function Implementation
// right, left
// count of subtrees if it has any
// value

struct Node {
  // Node();
  Node(const std::string s = "empty???", Node* L = nullptr, Node* R = nullptr); // make constructor cover more cases by setting default values
  ~Node(){}
  size_t weight = 1; // default value for weight, will adjust
  std::string data;
  Node* left;
  Node* right;
  Node* parent = nullptr; // default value is null, keep track of parent
};

#endif