#include "../Utilities/Data_Structures/Trie.h"
#include "../Utilities/Data_Fetching/DataFetcher.h"
#include "../Utilities/Input_Handling/liveInput.h"
#include <iostream>
#include <vector>
#include<string>
#include<unordered_map>

int main() {
    Trie tr;
    DataFetcher df;
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
    freq = df.LoadFrequency();
    for(auto& [word, fre] : freq) {
        std::cout<<word<<" "<<fre<<'\n';
    }
    LiveInput myInput(tr, freq);
    myInput.startLiveInput();
    freq["'ninja'"] = 10;
    freq["'chicken'"] = 92;
    df.SaveFrequency(freq);
    // temp = tr.getWords("pro", 2);
    // tr.displayTrie();
    // for(auto c: temp) {
    //     std::cout<<c<<std::endl;
    // }
}