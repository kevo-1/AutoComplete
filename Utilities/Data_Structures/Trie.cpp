#include "Trie.h"
#define alphabet 26 //define the number of alphabet to use it throuout the code
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

bool Trie::startsWith(std::string pre) {//the same as search prefix
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

// Node* Trie::__lastNodeFinder(std::string currentWord,Node* root) {
//     int index;
//     for(char c : currentWord){
//         index = c - 'a';
//         if(root->children[index] == nullptr){
//             return nullptr;
//         }
//         root = root->children[index];
//     }
//     return root;
// }
void Trie::__DFSsearch(std::vector<std::string>& words, std::string currentWord, Node *root,int depth = 0){
    if(!root){//if the root (the current node) is null then we return because the trie doesn't exist
        return;
    }
    //if the root is an end of a word then we add the current word to the vector even if it is the same as the prefix given
    if(root->endWord){
        words.push_back(currentWord);
    }
    //loop over every child from 0 to 25 (so in lexicographical order)
    // and if we find one we enter it with additional depth and add it to the current word before the calling of the function
    //so it will visit the next node(vertex) with out exploring the whole current node (Deapth first search) and then when it hits a leaf
    //it returns one at a time and coninue exploring the last node so it simulates a stack functionality without using a stack FILO/LIFO
    //as the funciton return to the last node it left, and the function progress recursively
    //note : this part is executed if and only if the root (current node) is the last node in the current word
    if(depth = currentWord.length()){
            for(int i = 0 ; i < alphabet; i++){
                if(root->children[i]){
                    __DFSsearch(words , currentWord += ('a' + i),root->children[i], depth + 1);
                }
        }
        return;
    }
    // this part is to be executed before the code above to increment the depth and to pass the last node in the current word
    //the current word doesn't change here because the intial currnet word already has all the letters till the last one in
    //the intial current word (prefix) and so we get the root as the last letter and the depth as the number of letters in
    //the current word and then enters the function again to start with the right depth and the root
    else{
            int index;
            for(char c : currentWord){
                index = c - 'a';
                if(root->children[index] == nullptr){
                    return ;
                }
                root = root->children[index];
                depth+=1;
            }
            return __DFSsearch(words, currentWord, root,depth);
        }
}