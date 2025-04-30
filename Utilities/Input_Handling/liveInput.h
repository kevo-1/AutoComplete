// this is a class that provide several functions:
// ==> functions for gui:
//      1. sanitize the word (remove all non-alphabetic characters and convert to lowercase)
//      2. get matching and search type : return the words in a vector -> count frequence if == 3 ? add :skip;
//      3. input from user by a certain word and operator to perform (delete, add)
#ifndef LIVEINPUT_H
#define LIVEINPUT_H
#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include "../Data_Structures/Trie.h"

class LiveInput
{
private:
    const char ENTER_KEY = '\n';
    const char CARRIAGE_RETURN = '\r';
    const char SPACE = ' ';
    const char ESCAPE = 27;
    const char TAB = '\t';
    const char BACKSPACE = 8;
    const char DELETE = 127;
    void setBufferedInput(bool enable);
    char getChar(void);
    void updateWordFrequency(std::string word);
    /*done input manipulation functions.. takes a whole string in
    getMatchWords -> getLastWord -> sanitize gives back a word in lowercase english.
    no special characters*/
    std::string getLastWord(std::string input);
    std::string sanitizeWord(std::string input);
    void chooseSuggestedWord(std::string);
    void displayWord(int index,std::string input,std::string word);

public:
    Trie mytrie;
    std::unordered_map<std::string, int> * freq;
    LiveInput(Trie &mytrie, std::unordered_map<std::string, int> *frequency);
    void startLiveInput();
    /*done: choice 1 insert data in the tree from suggested text choice 2 delete word*/
    std::vector<std::string> getMatchingWords(std::string input, int searchType);
    int performOperation(std::string wordChoice, int opChoice);
};
#endif