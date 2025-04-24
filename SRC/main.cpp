#include "../Utilities/Data_Structures/Trie.h"
#include <iostream>
#include <vector>
#include<string>

int main() {
    Trie tr;
    std::vector<std::string> words;
    tr.insertWord("program");
    tr.insertWord("progress");
    tr.insertWord("project");
    tr.insertWord("promotion");
    tr.insertWord("prototype");
    tr.insertWord("process");

    std::vector<std::string> temp = tr.getWords("pro", 1);
    tr.displayTrie();
    for(auto c: temp) {
        std::cout<<c<<std::endl;
    }
    // temp = tr.getWords("pro", 2);
    // tr.displayTrie();
    // for(auto c: temp) {
    //     std::cout<<c<<std::endl;
    // }
}