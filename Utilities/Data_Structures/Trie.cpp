#include "Trie.h"

Node::Node() {
    endWord = false;
    for (int i = 0; i < 26; i++) {
        children[i] = nullptr;
    }
}

Trie::Trie() : root(new Node()) {}

void Trie::insertWord(std::string word) {
    Node* dummy = root;
    word = __sanitizeWord(word);
    for (auto ch : word) {
        if (dummy->children[ch - 'a'] == nullptr) {
            dummy->children[ch - 'a'] = new Node();
        }
        dummy = dummy->children[ch - 'a'];
    }
    dummy->endWord = true;
}

bool Trie::searchWord(std::string word) {
    Node* dummy = root;
    word = __sanitizeWord(word);
    for (auto ch : word) {
        if (dummy->children[ch - 'a'] == nullptr) {
            return false;
        }
        dummy = dummy->children[ch - 'a'];
    }
    return dummy->endWord;
}

bool Trie::startsWith(std::string pre) {
    Node* dummy = root;
    pre = __sanitizeWord(pre);
    for (auto ch : pre) {
        if (dummy->children[ch - 'a'] == nullptr) {
            return false;
        }
        dummy = dummy->children[ch - 'a'];
    }
    return true;
}

void Trie::deleteWord(std::string word) {
    Node* dummy = root;
    word = __sanitizeWord(word);
    for (auto ch : word) {
        if (dummy->children[ch - 'a'] == nullptr) {
            return;
        }
        dummy = dummy->children[ch - 'a'];
    }
    dummy->endWord = false;
}

void Trie::displayTrie() {
    __displayTrieHelper("", root);
}

void Trie::__displayTrieHelper(std::string pre, Node* node) {
    if (node->endWord) {
        std::cout << pre << '\n';
    }
    for (int i = 0; i < 26; i++) {
        if (node->children[i] != nullptr) {
            __displayTrieHelper(pre + char(i + 'a'), node->children[i]);
        }
    }
}

std::string Trie::__sanitizeWord(std::string word) {
    std::string res;
    for (auto i : word) {
        if (isalpha(i)) {
            res += (islower(i) ? i : tolower(i));
        } else if (validChar.find(i) != validChar.end()) {
            res += i;
        }
    }
    return res;
}
