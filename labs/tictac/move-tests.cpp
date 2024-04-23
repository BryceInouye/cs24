#include <iostream>
#include <string>
#include "Errors.h"
#include "Move.h"

// Function to test the move parser
void testMoveParser(const std::string& input) {
    try {
        Move move(input);
        std::cout << "Parsed move: " << move.to_string() << std::endl;
    } catch (const ParseError& e) {
        std::cerr << "Error parsing move: " << e.what() << std::endl;
    }
}

int main() {
    // positive test cases
    // std::cout << "positive test cases: " << std::endl;
    // testMoveParser("2 X A2"); // Uppercase letters
    // testMoveParser("7 O C1");
    // testMoveParser("3 x a3"); // Lowercase letters
    // testMoveParser("8 o c2");
    // testMoveParser("6 x B2"); // Mix of upper and lowercase
    // testMoveParser("7 O b3");

    // // negative test cases
    // std::cout << "\nnegative test cases: " << std::endl;
    // testMoveParser("0 X A1");  // Move number out of range
    // testMoveParser("5 Z A1");  // Invalid player code
    // testMoveParser("3 X D2");  // Invalid row
    // testMoveParser("2 X A4");  // Invalid column

    // // more test cases
    // std::cout << "\nMore Test cases: " << std::endl;
    // testMoveParser("1 X A1  ");
    // testMoveParser("9 O C3 ");
    // testMoveParser("4 X B3 # this is a comment"); // Comment in correct format
    // testMoveParser("6 O C2  "); // Extra spaces
    // testMoveParser("6 O C3              "); // Tabs
    // testMoveParser("2 O B2                                    "); // Tabs and spaces mix

    // // edge cases
    // std::cout << "\nEdge cases: " << std::endl;
    // testMoveParser("");        // Empty input
    // testMoveParser("1  X A1"); // Extra space in input
    // testMoveParser("1 X A2#"); // Comment after the move
    // testMoveParser("5 O C1    #"); // Empty comment
    // testMoveParser("incorrect input"); // Random words
    
    // testMoveParser("5 x A1   # Comment here");
    // testMoveParser("3 o b2   # lowercase player and row codes");
    // testMoveParser("  # Only a comment");
    // testMoveParser("  # C   omment without any move details");
    // testMoveParser("6 # Comment after move number x C3");
    // testMoveParser("2XA2");
    // testMoveParser("1 X B2#");
    // testMoveParser("1 X B2#invalid_comment");
    // testMoveParser("1 X B2#");
    // testMoveParser("1 X B2# This is comment 1 ## This is comment 2");
    // testMoveParser("# This is a comment only");
    testMoveParser("1 X B2\t# This is a comment");
    // std::cout << "1 X B2\t# This is a comment";
    // testMoveParser("1 X B2# This is a comment");

    return 0;
}
