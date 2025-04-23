#include "Trie.h"
#include <queue>

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

std::vector<std::string> Trie::getWords(std::string prefix, int choice = 1) {
    
}


/**
 * @brief BFS Traversing to get the words with the same prefix passed
 *  
 * A Function that traverses all over the possible words and returns them ordered by length of word
 * 
 * @param words_vector a vector that contains the results of the search
 * @param current_word the current word/prefix
 * @param node
 * 
 * @author Kevin
 * 
 */
void Trie::__BFSsearch(std::vector<std::string>& words, std::string currentWord, Node* node) {
    std::queue<std::pair<Node*, std::string>> wordQueue;
    // start by queueing the current node and prefix
    wordQueue.push({node, currentWord});

    // here we will start our BFS Traversing
    while (!wordQueue.empty()) {
        //Unpack the current pair from the queue and assign the values to variables
        auto [currNode, word] = wordQueue.front();
        wordQueue.pop();

        //If the node we are currently on is the end of a word then add it to our vector of words
        if(currNode->endWord)
            words.push_back(currentWord);

        //Loop all over the 26 children (letters)
        for (int i = 0; i < 26; i++)
        {
            //If the node has any children then add the node's child and the current word we have + the letter to the queue of the BFS  
            if(node->children[i]){
                wordQueue.push({currNode->children[i], currentWord+char('a'+i)});
            } 
        }
    }
}