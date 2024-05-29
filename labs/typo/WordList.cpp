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
Heap WordList::correct(const std::vector<Point>& points, size_t maxcount, float cutoff) const {
    if (points.empty()) {
        throw std::invalid_argument("Points vector is empty");
    }
    
    size_t length = points.size();
    Heap heap(maxcount);

    for (const std::string& word : mWords) {
        if (word.length() != length) {
            continue;
        }

        float totalScore = 0.0;
        for (size_t i = 0; i < word.length(); ++i) {
            Point keyLocation = QWERTY[word[i] - 'a'];
            float dx = points[i].x - keyLocation.x;
            float dy = points[i].y - keyLocation.y;
            float distanceSquared = dx * dx + dy * dy;
            float score = 1.0f / (10.0f * distanceSquared + 1.0f);
            totalScore += score;
        }
        float averageScore = totalScore / word.length();

        if (averageScore >= cutoff) {
            if (heap.count() < maxcount) {
                heap.push(word, averageScore);
            } else if (averageScore > heap.top().score) {
                heap.pushpop(word, averageScore);
            }
        }
    }

    return heap;
}
