#include "Trie.h"
#include <queue>
#include <unordered_map>
#include <utility>

#define alphabet 26
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
        }
    }
    return res;
}

std::vector<std::string> Trie::getWords(std::string prefix, std::unordered_map<std::string, int>& frequency,int choice = 0) {
    std::vector<std::string> result;
    if (choice  == 0) {
        __ByFrequency(result, prefix, root, frequency);
    } else if(choice == 1) {
        __DFSsearch(result, prefix, root, 0);
    } else if (choice == 2) {
        __BFSsearch(result, prefix, root);
    }
    return result;
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
    if(!node){//if the root (the current node) is null then we return because the trie doesn't exist
        return;
    }
// Traverse to the end of the prefix
    for (char c : currentWord) {
        if (!node->children[c-'a']) return;  // Prefix not found
        node = node->children[c-'a'];
    }
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
            words.push_back(word);

        //Loop all over the 26 children (letters)
        for (int i = 0; i < 26; i++)
        {
            //If the node has any children then add the node's child and the current word we have + the letter to the queue of the BFS  
            if(currNode->children[i]){
                char temp = 'a'+i;
                wordQueue.push({currNode->children[i], word+temp});
            } 
        }
    }
}

/**
 * @brief DFS Traversing to get the words with the same prefix passed
 *  
 * A Function that traverses all over the possible words and returns them ordered lexicographically
 * 
 * @param words_vector a vector that contains the results of the search
 * @param current_word the current word/prefix
 * @param root the inital node of the trie
 * @param depth the level of the tree the funciton is at
 * 
 * @author Mario
 * 
 */
void Trie::__DFSsearch(std::vector<std::string>& words, std::string currentWord, Node *root,int depth = 0){
    if(!root){//if the root (the current node) is null then we return because the trie doesn't exist
        return;
    }//pro(cess)
    //if the root is an end of a word then we add the current word to the vector even if it is the same as the prefix given
    if(!(depth < currentWord.length())){
    if(root->endWord){
        words.push_back(currentWord);
    }
}
    //{loop over every child from 0 to 25 (so in lexicographical order)
    // and if we find one we enter it with additional depth and add it to the current word before the calling of the function
    //so it will visit the next node(vertex) with out exploring the whole current node (Deapth first search) and then when it hits a leaf
    //it returns one at a time and coninue exploring the last node so it simulates a stack functionality without using a stack FILO/LIFO
    //as the funciton return to the last node it left, and the function progress recursively
    //note : this part is executed if and only if the root (current node) is the last node in the current word}
    if(depth == currentWord.length()){
            for(int i = 0 ; i < alphabet; i++){
                if(root->children[i]){
                    __DFSsearch(words , currentWord + char('a' + i),root->children[i], depth + 1);
                }
        }
        return;
    }
    // {this part is to be executed before the code above to increment the depth and to pass the last node in the current word
    //the current word doesn't change here because the intial currnet word already has all the letters till the last one in
    //the intial current word (prefix) and so we get the root as the last letter and the depth as the number of letters in
    //the current word and then enters the function again to start with the right depth and the root}
    else{
            int index;
            for(char c : currentWord){
                index = c - 'a';
                if(root->children[index] == nullptr){
                    return ;
                }
                root = root->children[index];
            }
            return __DFSsearch(words, currentWord, root,depth + 1);
        }
}


/**
 * @brief get the words with the same prefix passed ordered by frequency of us
 *  
 * A Function that traverses all over the possible words and returns them ordered by frequence
 * 
 * @param words_vector a vector that contains the results of the search
 * @param current_word the current word/prefix
 * @param root the inital node of the trie
 * @param frequency a hashmap of the number of occurences of the word
 * 
 * @author Peter & Kevin
 * 
 */
void Trie::__ByFrequency(std::vector<std::string>& words, std::string currentWord, Node* node, std::unordered_map<std::string, int> frequency) {
    // A lambda compartor to order the priority queue by the value of the pair descendingly (frequency)
    auto cmp = [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
        return a.second < b.second; 
    };

    // Priority queue to sort the words
    std::priority_queue<std::pair<std::string, int>, std::vector<std::pair<std::string, int>>, decltype(cmp)> orderedWords(cmp);

    // Temporary vector to fetch the results in
    std::vector<std::string> temp;
    __BFSsearch(temp, currentWord, root);

    // Emptying the fetched results from the search into the priority queue
    for(auto a: temp) {
        orderedWords.push({a, frequency[a]});
    }

    // Clearing the vector (as a precaution from previously fetched results)
    words.clear();

    // Emptying the priority queue with the results ordered into the results vector (words)
    while (!orderedWords.empty()) {
        words.push_back(orderedWords.top().first);
        orderedWords.pop();
    }
}