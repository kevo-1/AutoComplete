#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <set>

class Node {
public:
    bool endWord;
    Node* children[26];

    Node();
};

class Trie {
private:
    Node* root;
    std::set<char> validChar = {'-', '_', '\'', '\"'};

public:
    Trie();
    void insertWord(std::string word);
    bool searchWord(std::string word);
    bool startsWith(std::string pre);
    void deleteWord(std::string word);
    void displayTrie();

private:
    void __displayTrieHelper(std::string pre, Node* node);
    std::string __sanitizeWord(std::string word);
};

#endif
