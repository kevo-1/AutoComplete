#include "../Utilities/Data_Structures/Trie.h"
#include "../Utilities/Data_Fetching/DataFetcher.h"
#include "../Utilities/Input_Handling/liveInput.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
// #include "../GUI/mainwindow.h"


void displayMainPage();

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
    // for(auto& [word, fre] : freq) {
    //     std::cout<<word<<" "<<fre<<'\n';
    // }
    df.SaveFrequency(freq);

    std::vector<std::string> temp = tr.getWords("pro", freq, 2);
    // tr.displayTrie();
    // for(auto c: temp) {
    //     std::cout<<c<<std::endl;
    // }
    LiveInput li = LiveInput(tr, &freq);
    int choice = -1;
    system("cls");
    while (choice != 2){
        displayMainPage();
        std::cout << "choose operation: \n[1] Start\n[2] exit\n";
        std::cout << "Enter your choice: "; std::cin >> choice;
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a 1 or 2: ";
        }
        if (choice == 1)
        {
            std::cout << "Start typing..\n";
            li.startLiveInput();
        }else if (choice == 2) break;
        system("cls");
    }
    std::cout << "Exiting program...\n";
    // for debugging purposes
    // tr.displayTrie();
    // for(auto c: temp) {
    //     std::cout<<c<<std::endl;
    // }
    // for(auto& [word, fre] : freq) {
    //     std::cout<<word<<" "<<fre<<'\n';
    // }
    // QApplication app(argc, argv);
    // MainWindow main_window;
    // main_window.show();
    // return app.exec();
}

void displayMainPage() {
    std::cout << "Welcome to Auto Complete program ..\n\n";
    std::cout << "\t\t+=======================================+\n";
    std::cout << "\t\t|           Auto Complete               |\n";
    std::cout << "\t\t+=======================================+\n\n";
}