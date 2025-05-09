#include "BFF.h"

BFF::BFF(DataFetcher& df) {
    this->freq = df.LoadFrequency();
    for (const auto &p : this->freq) {
        this->trie.insertWord(p.first);
    }
}

BFF::~BFF(){}

int BFF::addWord(std::string word) {
    if(!this->trie.searchWord(word)) {
        this->trie.insertWord(word);
    }
    this->freq[word]++;
    return 0;
}

int BFF::removeWord(std::string word) {
    if (this->trie.searchWord(word)) {
        this->trie.deleteWord(word);
    }
    this->freq[word] = 0;
    return 0;
}