#ifndef TREE_H
#define TREE_H

#include "Node.h"

class Tree {
  // Member Variables
  Node*        root; // parent node at the top
  size_t          numNodes;
  std::string*         nodeArray;

  // Private Helper Functions
  void       recursiveInsert(Node* root, const std::string& s);
  void recursivePrint(Node* ptr) const; // easier with a node
  void        rotate(Node* ptr, const bool side); // true for left, false for right
  // size_t recursiveCount(Node* root);
  bool recursiveContains(Node* root, const std::string& s) const;
  void recursiveClear(Node* ptr);
  void recursiveCreateArray(Node* ptr, std::string* &nodeArray, size_t &index);
  Node* findParent(Node* ptr);

public:
  Tree();
  ~Tree();

  // Public Member Functions
  void        clear();
  size_t      count() const;
  bool        contains(const std::string& s) const;
  size_t      find(const std::string& s) const;
  void        insert(const std::string& s);
  std::string lookup(size_t index) const;
  void        print() const;
  void        remove(size_t index);
  Node* createLeaf(const std::string& s);
  void  createArray();
};

#endif
