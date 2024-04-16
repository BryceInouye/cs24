#include "FibVec.h"
#include <iostream>

int main() {
    // Create a FibVec object
    FibVec fibVec;

    // Test push operations
    fibVec.push(10);
    fibVec.push(20);
    fibVec.push(30);
    fibVec.push(40);

    // Test pop operations
    std::cout << "Capacity: " << fibVec.capacity() << std::endl;
    std::cout << "Count: " << fibVec.capacity() << std::endl;
    std::cout << "Popped value: " << fibVec.pop() << std::endl;
    std::cout << "Capacity: " << fibVec.capacity() << std::endl;
    std::cout << "Count: " << fibVec.capacity() << std::endl;
    std::cout << "Popped value: " << fibVec.pop() << std::endl;
    std::cout << "Capacity: " << fibVec.capacity() << std::endl;
    std::cout << "Count: " << fibVec.capacity() << std::endl;
    std::cout << "Popped value: " << fibVec.pop() << std::endl;
    std::cout << "Capacity: " << fibVec.capacity() << std::endl;
    std::cout << "Count: " << fibVec.capacity() << std::endl;

    // Test popping from an empty vector
    try {
        std::cout << "Popped value: " << fibVec.pop() << std::endl;
    } catch (const std::underflow_error& e) {
        std::cerr << "Caught exception during pop: " << e.what() << std::endl;
    }

    return 0;
}


