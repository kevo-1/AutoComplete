#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include "liveInput.h"
#include "../Data_Structures/Trie.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif


/// @brief Constructor for LiveInput class
/// @details Initializes the LiveInput object with a Trie and a frequency map.
/// @param trie
/// @param frequency
/// @author Belal 
LiveInput::LiveInput(Trie &tr, std::unordered_map<std::string, int> frequency): mytrie{tr}, freq{frequency} {
    tr.displayTrie();
    if(freq.empty()){
        std::cout << "No words in the frequency map.\n";
    }
}

/// @brief Starts flow of live input for (terminal) and suggest words
/// not tested yet, and no suggestion can be choosen!
void LiveInput::startLiveInput()
{
    setBufferedInput(false); // disable buffering on Linux/Mac
    std::string input;
    std::string currentWord;
    char c;
    while (true) {
        c = getChar();
        if(c == ESCAPE) break;
        input.append(1, c);
        if (c == TAB){
            chooseSuggestedWord(input);
            continue;
        }
        if (c == ENTER_KEY || c == CARRIAGE_RETURN) break;
        if (c == SPACE) {
            currentWord = sanitizeWord(input);
            if (!currentWord.empty())
            {
                updateWordFrequency(currentWord);
                currentWord.clear();
            }
        }

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
        std::cout << "Enter Tab to choose suggested word! \n";
        std::cout << input << '\n';
        std::cout << "\n============================\n";
        std::cout << "Suggested words: \n";
        std::vector<std::string> words = getMatchingWords(input, 0);
        for (int i = 0; i < words.size(); i++) {
            std::cout << "[" << i + 1 << "] " << words[i] << std::endl;
        }
    }
    setBufferedInput(true); // re-enable buffering before exiting
}
void LiveInput::updateWordFrequency(std::string word)
{
    freq[word]++;
    if (freq[word] == 3) {
        mytrie.insertWord(word);
    }
}
void LiveInput::setBufferedInput(bool enable)
{
#ifndef _WIN32
    static bool enabled = true;
    static struct termios oldt;
    struct termios newt;

    if (enable && !enabled)
    {
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        enabled = true;
    }
    else if (!enable && enabled)
    {
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON); // Turn off canonical mode
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        enabled = false;
    }
#endif
}
char LiveInput::getChar(void)
{
#ifdef _WIN32
    return _getch();
#else
    return getchar();
#endif
}


/// @brief Takes a string and returns the last word in it
std::string LiveInput::getLastWord(std::string input) {
    std::istringstream stream(input);
    std::string word;
    std::string lastWord;

    while (stream >> word) {
        lastWord = word;
    }
    return lastWord;
}

/// @brief Takes a string and removes all non-alphabetic characters, lowercases without special characters
std::string LiveInput::sanitizeWord(std::string input) {
    input = getLastWord(input);
    for (int i = 0; i < input.length(); i++) {
        if (!isalpha(input[i])) {
            input.erase(i, 1);
            i--;
        } else {
            input[i] = tolower(input[i]);
        }
    }
    return input;
}

/// @brief Takes raw input -> sanitizes it -> pass it to searching algorithms according to the "search type"
/// @param input input string to search for matching words
/// @param searchType search performed according (0: frequency, 1: dfs, 2: BFS)
/// @return vector of matching words
/// @author Belal
std::vector<std::string> LiveInput::getMatchingWords(std::string input, int searchType = 0){
    std::string lastWord = sanitizeWord(input);
    //debug
    std::cout <<"last word: " << lastWord << std::endl;
    std::vector<std::string> result;
    if(lastWord.empty()) return {};
    updateWordFrequency(lastWord);
    result = mytrie.getWords(lastWord, freq, searchType);
    return result;
}


/// @brief  Perform an operation on the Trie from the input from gui "specifically"
/// @param wordChoice sanitized word came from the user choice of suggested words
/// @param opChoice operation choice (0: insert, 1: delete)
/// @return answer of the operation (1: success, -1: failure)
/// @author Belal
int LiveInput::performOperation(std::string wordChoice, int opChoice){
    if (opChoice == 1) {
        mytrie.insertWord(wordChoice);
        return 1;
    }else if(opChoice == 2) {
        mytrie.deleteWord(wordChoice);
        return 1;
    }
    return -1; // return -1 if the operation is not valid
}

void LiveInput::chooseSuggestedWord(std::string input){
    std::cout << "\n============================\n";
    std::cout << "Suggested words: \n";
    std::vector<std::string> words = getMatchingWords(input, 0);
    for (int i = 0; i < words.size(); i++) {
        std::cout << "[" << i + 1 << "] " << words[i] << std::endl;
    }
    std::cout << "Choose a word by entering its number : ";
    int choice = 0;
    while (true) {
        std::cin >> choice;
        if (choice >= 1 || choice <= words.size()) {
            break;
        }
        std::cout << "Invalid choice. Please try again: ";
    }
    std::cout << "Choose operation: \n[1] Insert\n[2] Delete\n[3] Cancel\n";
    int opChoice = 0;
    while (true) {
        std::cin >> opChoice;
        if (opChoice == 1 || opChoice == 2 || opChoice == 3) {
            break;
        }
        std::cout << "Invalid choice. Please try again: ";
    }
    std::cout << ((performOperation(words[choice - 1], opChoice) == 1)? "Operation successful!" : "Operation failed!");
    std::cout << "\n============================\n";
}
