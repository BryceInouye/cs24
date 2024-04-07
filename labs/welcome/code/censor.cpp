#include <iostream>
#include <cctype>
#include <string>
#include <vector>
using namespace std;
int main(int argc, char *argv[]) {
    if (argc != 2) {
        cout << "USAGE: censor [length]" << endl;
        exit(1);    
    }
    string word, sentence;
    getline(cin, sentence);
    size_t wordCensor = stoi(argv[1]);
    vector <string> words;
    for (size_t i = 0; i < sentence.length(); i++) {
        if (!isblank(sentence[i])) {
            word += sentence[i];
        } else if (isblank(sentence[i]) && word.length() != 0) {
            if (word.length() != wordCensor) {
                words.push_back(word);
            }
            word.clear();
        }
    }
    if ((words.size() == 0 || (!isblank(sentence[sentence.length() - 1]))) && word.length() != wordCensor){
        words.push_back(word);
    }
    for (size_t j = 0; j < words.size(); j++) {
        cout << words[j];
        if(j != words.size() - 1){
            cout << " ";
        }
       
    }
    cout << endl;
}