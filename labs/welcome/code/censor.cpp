#include <iostream>
#include <cctype>
#include <string>
using namespace std;
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cerr << "USAGE: censor [length]" << endl;
        exit(1);    
    }
    string word, sentence;
    getline(cin, sentence);
    size_t wordCensor = stoi(argv[1]);
    for (size_t i = 0; i < sentence.length(); i++) {
        if (!isblank(sentence[i])) {
            word += sentence[i];
        } else {
            if (word.length() != wordCensor) {
                cout << word;
                if (i + 1 != sentence.length()) {
                    cout << " ";
                }
            }
            word.clear();
        }
    }
    if (word.length() != wordCensor) {
        cout << word;
    }
    cout << endl;
}