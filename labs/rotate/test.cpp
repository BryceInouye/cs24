#include "Tree.h"
#include <iostream>

int main() {
    Tree tree;

    // Insert some elements
    tree.insert("A");
    tree.insert("B");
    tree.insert("C");
    tree.insert("D");
    tree.insert("E");
    tree.insert("F");


    // tree.insert("Q");
    // tree.insert("P");
    // tree.insert("S");

    // tree.insert("A");
    // tree.insert("B");
    // tree.insert("C");
    // Print the tree
    std::cout << "Tree contents: \n";
    tree.print();

    // std::cout << std::endl;
    // tree.createArray();
    // std::cout << "finding A: expected 0, actual: " << tree.find("A");
    // std::cout << "\nfinding L: expected 4, actual: " << tree.find("L");
    // std::cout << "\nfinding P: expected 6, actual: " << tree.find("P") << std:: endl;
    // std::cout << "lookup 0: expected A, actual: " << tree.lookup(0) << std::endl;
    // std::cout << "lookup 3: expected E, actual: " << tree.lookup(3) << std::endl;
    // std::cout << "lookup 8: expected S, actual: " << tree.lookup(8) << std::endl;
    
    // std::cout << "contains D, expected: true, actual: " << tree.contains("D") << std::endl;
    // std::cout << "contains Z, expected: false, actual: " << tree.contains("Z") << std::endl;
    // std::cout << "contains S, expected: true, actual: " << tree.contains("S") << std::endl;


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
