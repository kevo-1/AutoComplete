#include "../Utilities/Data_Structures/Trie.h"
#include <iostream>
#include <vector>
#include<string>

int main() {
    Trie tr;
    std::vector<std::string> words;
    tr.insertWord("n");
    tr.insertWord("ni");
    tr.insertWord("nin");
    tr.insertWord("ninj");
    tr.insertWord("ninja");

    tr.displayTrie();
    std::cout<< tr.searchWord("ninja") << std::endl;
    tr.deleteWord("ninja");
    std::cout<< tr.searchWord("ninja") << std::endl;
    
    std::cout<< tr.startsWith("ninj") << std::endl;
    tr.deleteWord("ninj");
    std::cout<< tr.startsWith("ninj") << std::endl;
    tr.displayTrie();
    tr.__DFSsearch(words,"ni",tr.root,0);
    for (int i = 0 ; i < words.size();i++){
        std::cout<<words[i]<<std::endl;
    }
}