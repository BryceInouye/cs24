#include "FibVec.h"

// This provides exception types:
#include <stdexcept>
#include <cmath>
#include <iostream>
using namespace std;

// FibVec Function Implementations

// The default constructor creates an empty vector with a capacity of f(2) = 1.
FibVec::FibVec() {
            size = 1;
            numItems = 0;
            fibNum = 1;
            fibNum0 = 1;
            fibVector = new int[fibNum];
        }
FibVec::~FibVec(){
    delete[] fibVector;
}

size_t FibVec::capacity() const {
    return size;
}

size_t FibVec::count() const{
    return numItems;
}

int FibVec::pop() {
  if (numItems == 0) {
    throw std::underflow_error("Vector is empty");
  }
  numItems--;

  // Resize if needed based on Fibonacci sequence (f(n-2))
  if (numItems < fibNum0) {
    size = fibNum;  // New size is f(n-1)
    fibNum0 = fibNum;  // Update fibonacci numbers
    fibNum = fibNum + fibNum0;  // Calculate f(n)
    newFibVec();  // Resize the vector
  }

  // Access element from the new vector after potential resize
  return fibVector[numItems];
}


void FibVec::push(int value) {
    if (numItems == size) {
        size = fibNum + fibNum0;
        fibNum0 = fibNum;
        fibNum = size;
        newFibVec();
    }
    fibVector[numItems] = value;
    numItems++;
}

int FibVec::lookup(size_t index) const {
    if (index > numItems) {
        throw std::out_of_range("Index out of range");
    }    
    return fibVector[index];
}

void FibVec::newFibVec() {
    int* newFibVector = new int[size];
    for (size_t i = 0; i < numItems; i++) {
        newFibVector[i] = fibVector[i];
    }
    delete[] fibVector;
    fibVector = newFibVector;    
}

void FibVec::insert(int val, size_t index) {
    if (index > size) {
        throw std::out_of_range("Index out of range");
    }
    if (numItems == size){
        size = fibNum + fibNum0;
        fibNum0 = fibNum;
        fibNum = size;
    }
    numItems++;
    int* newFibVector = new int[size];
    size_t j = 0;
    for (size_t i = 0; i < numItems; i++) {
        if (i < index) {
            newFibVector[j++] = fibVector[i];
        } else if (i == index) {
            newFibVector[j++] = val;
        } else {
            newFibVector[j++] = fibVector[i-1];
        }
    }
    delete[] fibVector;
    fibVector = newFibVector;

}

int FibVec::remove(size_t index) {
  if (index > size) {
    throw std::out_of_range("Index out of range");
  }
  if (numItems < fibNum - fibNum0){
      size_t temp = fibNum - fibNum0;
      size = fibNum0;
      fibNum = fibNum0;
      fibNum0 = temp;
      newFibVec();
  }
  numItems--; // Update numItems after potential resize
  int removedItem = fibVector[index];
  int* newFibVector = new int[size];
  size_t j = 0;
  for (size_t i = 0; i < numItems; i++) {
    if (i == index) {
      continue;
    }
    newFibVector[j++] = fibVector[i];
  }
  delete[] fibVector;
  fibVector = newFibVector;
  return removedItem;
}


// The destructor cleans up all allocated memory owned by the class.

// The capacity function returns the total size of the storage buffer.

// The count function returns the number of items stored in the vector.

// The insert function takes two arguments: the first is a value and the second is an index. 
// It stores the value at the given index. If the index is invalid, it throws a std::out_of_range exception.

// The lookup function takes one argument: an index. It returns the value stored at that index. 
// If the index is invalid, it throws a std::out_of_range exception.

// The pop function takes no arguments. It removes and returns the last value in the vector. 
// If the vector is empty, it throws a std::underflow_error.

// The push function takes one argument: a value. 
// It inserts that value at the end of the vector. It has no return value.

// The remove function takes one argument: an index. It removes the value stored at that index and returns it. 
// If the index is invalid, it throws a std::out_of_range exception.