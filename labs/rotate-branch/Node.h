#ifndef NODE_H
#define NODE_H

#include <string>

struct Node {
  // Node();
  Node(const std::string& s);
  ~Node();
  int weight;
  int imbalance;
  int calcWeight();
  void calcImbalance();
  Node* left;
  Node* right;
  std::string data;

  // Node Function Implementations
  // right, left
  // count of subtrees if it has any
  // value
};

#endif
