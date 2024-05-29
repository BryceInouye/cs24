#include "Heap.h"
#include <stdexcept>

// constructor
Heap::Heap(size_t capacity) : mCapacity(capacity), mCount(0) {
    mData = new Entry[capacity];
}

// copy
Heap::Heap(const Heap& other) : mCapacity(other.mCapacity), mCount(other.mCount) {
    mData = new Entry[mCapacity];
    for (size_t i = 0; i < mCount; ++i) {
        mData[i] = other.mData[i];
    }
}

// destructor
Heap::~Heap() {
    delete[] mData;
}

// returns mCapacity
size_t Heap::capacity() const {
    return mCapacity;
}

// returns mCount
size_t Heap::count() const {
    return mCount;
}

// lookup of an array
const Heap::Entry& Heap::lookup(size_t index) const {
    if (index >= mCount) {
        throw std::out_of_range("lookup() error");
    }
    return mData[index];
}

/* push adds a new entry to the heap. If there is no space for the new item, it throws a std::overflow_error. */
void Heap::push(const std::string& value, float score) {
    if (mCount >= mCapacity) {
        throw std::overflow_error("push() error");
    }
    mData[mCount] = {value, score};
    size_t currentIndex = mCount;
    ++mCount;

    // percolate up
    while (currentIndex > 0) {
        size_t parentIndex = (currentIndex - 1) / 2;
        if (mData[currentIndex].score >= mData[parentIndex].score) {
            break;
        }
        // swap
        Entry temp = mData[currentIndex];
        mData[currentIndex] = mData[parentIndex];
        mData[parentIndex] = temp;
        currentIndex = parentIndex;
    }
}

/*pop function removes the entry with the lowest score and returns it. 
If there are no items in the heap, it throws a std::underflow_error.*/
Heap::Entry Heap::pop() {
    if (mCount == 0) {
        throw std::underflow_error("pop() error");
    }
    Entry minEntry = mData[0];
    mData[0] = mData[mCount - 1];
    --mCount;

    // percolate down
    size_t currentIndex = 0;
    while (true) {
        size_t leftChild = 2 * currentIndex + 1;
        size_t rightChild = 2 * currentIndex + 2;
        size_t smallest = currentIndex;

        if (leftChild < mCount && mData[leftChild].score < mData[smallest].score) {
            smallest = leftChild;
        }
        if (rightChild < mCount && mData[rightChild].score < mData[smallest].score) {
            smallest = rightChild;
        }
        if (smallest == currentIndex) {
            break;
        }
        // Swap without using std::swap
        Entry temp = mData[currentIndex];
        mData[currentIndex] = mData[smallest];
        mData[smallest] = temp;
        currentIndex = smallest;
    }

    return minEntry;
}

/* pushpop function is a more efficient version of a pop() followed by a push(). 
Instead of replacing the popped entry with the last entry in the vector, 
it replaces it with the pushed entry, and then percolates that down. 
If there are no items in the heap, it throws a std::underflow_error.*/

Heap::Entry Heap::pushpop(const std::string& value, float score) {
    if (mCount == 0) {
        throw std::underflow_error("pushpop() error");
    }
    if (mCount < mCapacity || score > mData[0].score) {
        Entry minEntry = mData[0];
        mData[0] = {value, score};

        // percolate down
        size_t currentIndex = 0;
        while (true) {
            size_t leftChild = 2 * currentIndex + 1;
            size_t rightChild = 2 * currentIndex + 2;
            size_t smallest = currentIndex;

            if (leftChild < mCount && mData[leftChild].score < mData[smallest].score) {
                smallest = leftChild;
            }
            if (rightChild < mCount && mData[rightChild].score < mData[smallest].score) {
                smallest = rightChild;
            }
            if (smallest == currentIndex) {
                break;
            }
            // swap
            Entry temp = mData[currentIndex];
            mData[currentIndex] = mData[smallest];
            mData[smallest] = temp;
            currentIndex = smallest;
        }

        return minEntry;
    } else {
        return {value, score}; // if new entry is not pushed, return it directly
    }
}

/*The top() function returns a reference to the entry with the lowest score. 
If there are no items in the heap, it throws a std::underflow_error.*/

const Heap::Entry& Heap::top() const {
    if (mCount == 0) {
        throw std::underflow_error("top() error");
    }
    return mData[0];
}
