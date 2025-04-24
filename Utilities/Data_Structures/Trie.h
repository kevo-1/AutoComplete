#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <set>
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
    std::set<char> validChar = {'-', '_', '\'', '\"'};

public:
    Trie();
    void insertWord(std::string word);
    bool searchWord(std::string word);
    bool startsWith(std::string pre);
    void deleteWord(std::string word);
    void displayTrie();
    std::vector<std::string> getWords(std::string word);
    
    private:
    void __displayTrieHelper(std::string pre, Node* node);
    std::string __sanitizeWord(std::string word);
    void __DFSsearch(std::vector<std::string>& words, std::string currentWord, Node * root , int depth);
    void __BFSsearch(std::vector<std::string>& words, std::string currentWord);
};

#endif
