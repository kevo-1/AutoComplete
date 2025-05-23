#include "BFF.h"
#include <iostream>

BFF::BFF(DataFetcher& df) {
    this->freq = df.LoadFrequency();
    for (const auto &p : this->freq) {
        this->trie.insertWord(p.first);
    }
}

BFF::~BFF(){}

void BFF::addWord(std::string word) {
    std::cout<<"I am here";
    if(!this->trie.searchWord(word)) {
        this->trie.insertWord(word);
    }
    this->freq[word]++;
    std::cout<<"I am here";
}

void BFF::removeWord(std::string word) {
    if (this->trie.searchWord(word)) {
        this->trie.deleteWord(word);
    }
    this->freq[word] = 0;
}