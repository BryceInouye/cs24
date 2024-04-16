#include "FibVec.h"
#include <iostream>

int main() {
  // Test 1: Pop once
  FibVec fibVec;
  fibVec.push(100);
  fibVec.push(200);

  std::cout << "Popped: " << fibVec.pop() << std::endl;
  std::cout << "Size: " << fibVec.capacity() << std::endl;
  std::cout << "numItems " << fibVec.count() << std::endl;

  // Test 2: Pop twice
  fibVec.push(300);

  std::cout << "Popped: " << fibVec.pop() << std::endl;
  std::cout << "Popped: " << fibVec.pop() << std::endl;
  std::cout << "Size: " << fibVec.capacity() << std::endl;
  std::cout << "numItems " << fibVec.count() << std::endl;

  // Test 3: Pop five times
  for (int i = 1; i <= 5; ++i) {
    fibVec.push(i);
  }

  for (int i = 5; i >= 1; --i) {
    std::cout << "Popped: " << fibVec.pop() << std::endl;
  }

  std::cout << "Size: " << fibVec.capacity() << std::endl;
  std::cout << "numItems " << fibVec.count() << std::endl;

  return 0;
}


