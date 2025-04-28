#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include "liveInput.h"
#include "../Data_Structures/Trie.h"
#include "../Data_Structures/Trie.cpp"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

using namespace std;


/// @brief Constructor for LiveInput class
/// @details Initializes the LiveInput object with a Trie and a frequency map.
/// @param trie
/// @param frequency
/// @author Belal 
LiveInput::LiveInput(Trie &trie, std::unordered_map<std::string, int> &frequency): mytrie{trie}, freq{frequency} {}

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

        if (c == ENTER_KEY || c == CARRIAGE_RETURN) break;
        if (c == SPACE) {
            currentWord = sanitizeWord(input);
            if (!currentWord.empty())
            {
                updateWordFrequency(currentWord);
                currentWord.clear();
            }
        }
        // exit logic .. 
        cout << "\r" << input << flush;
        std::cout << input << '\n' << setw(20) << left << "Suggested words: " << flush;
        for (const auto& word : getMatchingWords(input, 0)) {
            std::cout << word << " ";
        }
        std::cout << std::endl;
    }
    setBufferedInput(true); // re-enable buffering before exiting
}
void LiveInput::updateWordFrequency(string word)
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
string LiveInput::getLastWord(string input) {
    istringstream stream(input);
    string word;
    string lastWord;

    while (stream >> word) {
        lastWord = word;
    }
    return lastWord;
}

/// @brief Takes a string and removes all non-alphabetic characters, lowercases without special characters
string LiveInput::sanitizeWord(std::string input) {
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
vector<string>& LiveInput::getMatchingWords(string input, int searchType = 0){
    string lastWord = sanitizeWord(input);
    if(lastWord.empty()) return vector<string>{};
    updateWordFrequency(lastWord);
    vector<string> result;
    result = mytrie.getWords(input, freq, searchType);
    return result;
}


/// @brief  Perform an operation on the Trie from the input from gui "specifically"
/// @param wordChoice sanitized word came from the user choice of suggested words
/// @param opChoice operation choice (0: insert, 1: delete)
/// @return answer of the operation (1: success, -1: failure)
/// @author Belal
int LiveInput::performOperation(string wordChoice, int opChoice){
    if (opChoice == 0) {
        mytrie.insertWord(wordChoice);
        return 1;
    }else if(opChoice == 1) {
        mytrie.deleteWord(wordChoice);
        return 1;
    }
    return -1; // return -1 if the operation is not valid
}
