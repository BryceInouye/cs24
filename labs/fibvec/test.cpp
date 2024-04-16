#include "FibVec.h"
#include <iostream>

int main() {
  // Create a FibVec object
  FibVec fibVec;

  // Test push and pop operations

  // Push three elements
  fibVec.push(10);
  fibVec.push(20);
  fibVec.push(30);
  std::cout << "Count after pushing: " << fibVec.count() << std::endl;

  // Pop one element
  std::cout << "Popped value: " << fibVec.pop() << std::endl;
  std::cout << "Count after popping: " << fibVec.count() << std::endl;

  // Test insert operation (with potential exception)
  try {
    fibVec.insert(15, 1);
    // Print count after insertion
    std::cout << "Count after insertion: " << fibVec.count() << std::endl;
    std::cout << "Inserted value: " << fibVec.lookup(1) << std::endl;
  } catch (const std::out_of_range& e) {
    std::cerr << "Caught exception during insert: " << e.what() << std::endl;
  }

  // Test remove operation (with potential exception)
  try {
    fibVec.remove(1);
    std::cout << "Count after removal: " << fibVec.count() << std::endl;
  } catch (const std::out_of_range& e) {
    std::cerr << "Caught exception during insert: " << e.what() << std::endl;
}


  return 0;
}

