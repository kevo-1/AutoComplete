#include "../Utilities/Data_Structures/Trie.h"
#include <iostream>
#include <vector>
#include<string>
#include<unordered_map>

int main() {
    Trie tr;
    std::vector<std::string> words;
    tr.insertWord("program");
    tr.insertWord("progress");
    tr.insertWord("project");
    tr.insertWord("promotion");
    tr.insertWord("prototype");
    tr.insertWord("process");
    tr.insertWord("priority");
    tr.insertWord("problem");
    tr.insertWord("prediction");
    tr.insertWord("proceed");
    tr.insertWord("processing");
    tr.insertWord("ninja");

    std::unordered_map<std::string, int> freq;
    freq["program"] = 12;
    freq["progress"] = 85;
    freq["project"] = 97;
    freq["promotion"] = 0;
    freq["prototype"] = 30;
    freq["ninja"] = 100;
    freq["process"] = 100;
    freq["processing"] = 100;
    freq["priority"] = 17;
    freq["problem"] = 65;
    freq["prediction"] = 5;
    freq["proceed"] = 40;
    
    std::vector<std::string> temp = tr.getWords("", freq, 0);
    tr.displayTrie();
    std::cout<<std::endl;
    for(auto c: temp) {
        std::cout<<c<<std::endl;
    }
    // temp = tr.getWords("pro", 2);
    // tr.displayTrie();
    // for(auto c: temp) {
    //     std::cout<<c<<std::endl;
    // }
}