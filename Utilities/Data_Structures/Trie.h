#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <set>
#include <unordered_map>
#include <vector>

class Node {
public:
    bool endWord;
    Node* children[26];

    Node();
};

class Trie {
private:
    Node* root;//was private

public:
    Trie();
    void insertWord(std::string word);
    bool searchWord(std::string word);
    bool startsWith(std::string pre);
    void deleteWord(std::string word);
    void displayTrie();
    std::vector<std::string> getWords(std::string word,std::unordered_map<std::string, int> frequency, int choice);
    
    private:
    void __displayTrieHelper(std::string pre, Node* node);
    std::string __sanitizeWord(std::string word);
    void __DFSsearch(std::vector<std::string>& words, std::string currentWord, Node * root , int depth);
    void __BFSsearch(std::vector<std::string>& words, std::string currentWord, Node* node);
    void __ByFrequency(std::vector<std::string>& words, std::string currentWord, Node* node, std::unordered_map<std::string, int> frequency);
};

#endif
