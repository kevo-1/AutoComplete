#include "Utilities\Data_Structures\Trie.h"
#include <iostream>

int main() {
    Trie tr;

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
}