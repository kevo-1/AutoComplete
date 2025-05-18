#include "../Utilities/Data_Structures/Trie.h"
#include "../Utilities/Data_Fetching/DataFetcher.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include "../GUI/mainwindow.h"
#include "../Utilities/Input_Handling/liveInput.h"
#include "BFF/BFF.h"
#include <QApplication>

int main(int argc, char *argv[]) {

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
    // freq["'ninja'"] = 10;
    // freq["'chicken'"] = 92;
    // df.SaveFrequency(freq);

    std::vector<std::string> temp = tr.getWords("pro", freq, 2);
    tr.displayTrie();
    for(auto c: temp) {
        std::cout<<c<<std::endl;
    }

    BFF bff = BFF(df);
    bff.addWord("Hello");
    bff.trie.displayTrie();
    std::cout<<std::endl;
    for(auto& c : bff.freq) {
        std::cout<<c.first<<std::endl;
    }

    LiveInput live = LiveInput(tr, &freq);
    live.startLiveInput();
    // QApplication app(argc, argv);
    // MainWindow main_window = MainWindow(df);
    // main_window.show();
    // return app.exec();
}
