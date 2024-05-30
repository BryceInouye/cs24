#include "WordList.h"
#include "Point.h"
#include "Heap.h"
#include <cmath>
#include <stdexcept>
#include <sstream>

// check if a word is all lowercase ASCII
bool isLowerCaseAscii(const std::string& word) {
    for (char ch : word) {
        if (ch < 'a' || ch > 'z') {
            return false;
        }
    }
    return true;
}

// constructor
WordList::WordList(std::istream& stream) {
    std::string word;
    while (stream >> word) {
        if (isLowerCaseAscii(word)) {
            mWords.push_back(word);
        }
    }
}

/*The correct() function is where the important stuff happens. It takes in a sequence of points; 
these are the points where the user touched the screen. It then finds all the words of the correct length, 
scores them according to the scoring algorithm below, and uses a Heap with capacity maxcount to collect the most likely words. 
Words with scores lower than cutoff are not included in the output.*/

Heap WordList::correct(const std::vector<Point> &points, size_t maxcount, float cutoff) const
{
    Heap heap(maxcount);
    size_t pointLength = points.size();
    std::vector<std::string> temp;
    auto itr = mWords.begin();
    while (itr != mWords.end())
    {
        if ((*itr).length() == pointLength)
        {
            temp.push_back(*itr);
        }
        ++itr;
    }
    for (auto itr = temp.begin(); itr != temp.end(); itr++)
    {
        float total = 0;
        size_t i = 0;
        for (auto it = points.begin(); it != points.end(); it++)
        {
            int idx = ((*itr)[i] - 97);
            float euclidDistance = sqrt(pow((QWERTY[idx].x - it->x), 2) + pow((QWERTY[idx].y - it->y), 2));
            float score = 1.0 / (10.0 * pow(euclidDistance, 2) + 1.0);
            total = total + score;
            i++;
        }
        float s = total / float((*itr).length()); // s


        if (s >= cutoff)
        {
            if (heap.count() < heap.capacity())
            {
                heap.push(*itr, s);
            }
            else if (heap.top().score < s)
            {
                heap.pushpop(*itr, s);
            }
        }
    }
    return heap;
}