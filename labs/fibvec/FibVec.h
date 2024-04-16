#ifndef FIBVEC_H
#define FIBVEC_H

// This provides the size_t type:
#include <cstddef>

class FibVec {
    public:
        FibVec();
        ~FibVec();
        size_t capacity() const;
        size_t count() const;
        void insert(int val, size_t index);
        int lookup(size_t index) const;
        int pop();
        void push(int value);
        int remove(size_t index);
        void newFibVec();

    private:
        int* fibVector;
        size_t size;
        size_t numItems;
        size_t fibNum;
        size_t fibNum0;
};

#endif
