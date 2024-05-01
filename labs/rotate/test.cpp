#include "Tree.h"
#include <iostream>

int main() {
    Tree tree;

    // Insert some elements
    tree.insert("Texas");
    // tree.insert("z");
    // tree.insert("c");
    // tree.insert("k");
    // tree.insert("w");
    // tree.insert("g");
    

    // Print the tree
    std::cout << "Tree contents: \n";
    tree.print();
    std::cout << std::endl;
    tree.createArray();

    // // Check if the tree contains certain elements
    // std::cout << "Does the tree contain 'apple'? " << (tree.contains("apple") ? "Yes" : "No") << std::endl;
    // std::cout << "Does the tree contain 'pear'? " << (tree.contains("pear") ? "Yes" : "No") << std::endl;

    // // Print the number of elements in the tree
    // std::cout << "Number of elements in the tree: " << tree.count() << std::endl;

    // // Clear the tree
    // tree.clear();
    // std::cout << "Tree cleared. Number of elements in the tree: " << tree.count() << std::endl;
    // std::cout << "Is the tree really empty? ";
    // tree.print();

    return 0;
}
