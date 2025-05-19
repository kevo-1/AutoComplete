#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include "liveInput.h"
#include <vector>
#include <string>
#include <stack>
#include<cctype>
#include <limits>
#include "../Data_Structures/Trie.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
#include <cassert>

//Belal
//delete from map along with the trie[done]
//insert(hat7ott el word in the trie+in the map with freq=3 if it doesn't exist)[done] //
// live input works good while fetched data have some problems with some words !!! under testing




/// @brief Constructor for LiveInput class
/// @details Initializes the LiveInput object with a Trie and a frequency map.
/// @param trie
/// @param frequency
/// @author Belal
LiveInput::LiveInput(Trie &tr, std::unordered_map<std::string, int> *frequency) : mytrie{tr}, freq{frequency}
{
    //tr.displayTrie();
    if (freq->empty())
    {
        std::cout << "No words in the frequency map.\n";
    }
}


/// @brief provides greyed out text to seen for complete
/// @param words suggested words
/// @param input input str
/// @return non typed part of the first suggestion
/// @author ramy
std::string LiveInput::completeGreyedOut(std::vector<std::string>words,std::string input){
    std::string completion;
    // std::stack<char> prefStack;
    if(!words.empty() && !input.empty()){
        std::stack<char> suggStack;
        std::string pref =sanitizeWord(input);
        std::string sugg=words[0];
        for (int i = sugg.size()-1; i >=0; i--)
        {
            suggStack.push(sugg[i]);
        }
        for (int i = 0; i < pref.size(); i++)
        {
            if (!suggStack.empty())
            {
                suggStack.pop();
            }
            
        }
        while (!suggStack.empty())
        {
            completion+=suggStack.top();
            suggStack.pop();
        }
        
    }
    return completion;
}

/// @brief highligts exact matching word suggestions
/// @param input string complete input string
/// @param word string word being displayed
/// @param index int index of word
/// @author ramy
void LiveInput::displayWord(int index,std::string input,std::string word){
    if (sanitizeWord(input)==word)
            {
                std::cout << "\033[30m\033[43m[" << index + 1 << "] " << word << " \033[0m  ";
            }else{
                std::cout << "[" << index + 1 << "] " << word << "  ";
            }
}

/// @brief replaces current prefix being typed with the chosen suggestion
/// @param words suggested words
/// @param input input string
/// @param c input character for choosing suggestion
void LiveInput:: replaceWithSuggestion(std::vector<std::string> words,std::string& input,char c){
    int wordChoiceNum;
        if (c=='1' ||c=='2' ||c=='3' ||c=='4' ||c=='5' ||c=='6' ||c=='7' ||c=='8' ||c=='9')
        {
            wordChoiceNum = int(c-'0');
        }else{
            wordChoiceNum = 0;
        }

        
        if (c==TAB || wordChoiceNum!=0)
        {
            char lastChar=0;
            if (!input.empty())
            {
                lastChar=input.back();
            }
            
            
            while (lastChar!=SPACE && !input.empty())
            {
                lastChar=input.back();
                input.pop_back();
            }
            if (!input.empty())
            {
                input+=' ';
            }
            
            if (c==TAB)
            {
                input.append(words[0]);
                input+=' ';
            }
            else
            {
                if (wordChoiceNum > 0 && wordChoiceNum <= words.size()) {
                input.append(words[wordChoiceNum - 1]);
                input += ' ';
                }
            }
        }
}

/// @brief allows user to dynamically change order of suggestions
/// @param c 
/// @return search type: 0(most frequent), 1(lexicographical), 2(shortest first)
void LiveInput::chooseSearchType(char c,int& searchType){
    if (c=='~')
    {
        searchType = 0;
    }
    if (c=='!')
        {
            searchType = 1;
        }
    if (c=='@')
        {
            searchType = 2;
        }
}


void LiveInput::mainDisplay(std::vector<std::string>words,std::string input, int searchType){
    
#ifdef _WIN32
system("cls");
#else
system("clear");
#endif
displayHeader(searchType);
std::cout << input <<"\033[2m"<<completeGreyedOut(words, input)<<"\033[0m\n";
std::cout << "\n+ ----------------------------------------------------------------------------------------------------------- +\n";
std::cout << "Suggested words: \n\n";

//added upper bound: 9 bec i only have numbers 1-9 to chose from in completion
for (int i = 0; i < words.size() && i<9; i++)
{
    displayWord(i,input,words[i]);
    if ((i + 1) % 5 == 0)
    {
        std::cout << std::endl;
    }
}
std::cout << "\n\n+ ----------------------------------------------------------------------------------------------------------- +\n";
// std::cout<<"Order of suggestions: ";
// if (searchType==0)
// {
//     std::cout<<"Most frequently used\n";
// }else if (searchType==1)
// {
//     std::cout<<"Lexicographical\n";
// }else if (searchType==2)
// {
//     std::cout<<"Shortest first\n";
// }
}


/// @brief Starts flow of live input for (terminal) and suggest words
/// not tested yet, and no suggestion can be choosen!
void LiveInput::startLiveInput()
{
    //debugging purpose
    // for(auto& [word, fre] : (*freq)) {
    //     std::cout<<word<<" "<<fre<<'\n';
    // }
    setBufferedInput(false); // disable buffering on Linux/Mac
    std::string input;
    std::string currentWord;
    char c;
    int searchType=0;
    while (true)
    {
        c = getChar();
        if (isalpha(c) || c==SPACE)
        {
            input.append(1, c);
        }
        
        chooseSearchType(c,searchType);
        std::vector<std::string> words = getMatchingWords(input, searchType);

        

        if (c == ENTER_KEY || c == CARRIAGE_RETURN || c == ESCAPE)
            break;
        if (c == BACKSPACE || c == DELETE)
        {
            if (!input.empty())
                input.pop_back();
        }
        if (c == BACKSLASH)
        {
            std::cout << "choose operation: \n[1] Insert\n[2] Delete\n[3] exit\n";
            int choice = -1;
            std::cout << "Enter your choice: ";
            while (true)
            {
                std::cin >> choice;
                if (std::cin.fail())
                {
                    std::cin.clear();                                                   // Clear the error flag
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
                    std::cout << "Invalid input. Please enter a number: ";
                    continue;
                }
                if (choice == 1 || choice == 2 || choice == 3)
                    break;
                std::cout << "Invalid choice. Please enter 1 for Insert, 2 for Delete, 3 for exiting: ";
            }
            if(choice==1){
                std::string wordChoice = sanitizeWord(input);
                mytrie.insertWord(wordChoice);
                (*freq)[wordChoice] = 3;
                std::cout << "Word: "<<wordChoice<<" inserted successfully!\n";
            }else if (choice==2){
                chooseSuggestedWord(input, searchType, words);
            }else if (choice==3){
                continue;
            }
        }

        if (c == SPACE)
        {
            currentWord = sanitizeWord(input);
            updateWordFrequency(currentWord);
            currentWord.clear();
        }

        

        // //moved this here in order to use it in completing using suggestions
        // std::vector<std::string> words = getMatchingWords(input, searchType);
        
        
        replaceWithSuggestion(words,input,c);
        
        mainDisplay(words,input,searchType);
        


    }
    mytrie.displayTrie(); // Display the Trie after exiting the loop
    //debugging purpose
    // for(auto& [word, fre] : (*freq)) {
    //     std::cout<<word<<" "<<fre<<'\n';
    // }
    //system("pause");
    setBufferedInput(true); // re-enable buffering before exiting
}
void LiveInput::updateWordFrequency(std::string word)
{
    (*freq)[word]++;
    int freqnum=(*freq)[word];
    if (freqnum == 3)
    { // Insert the word into the Trie only when it is repeated exactly 3 times
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
std::string LiveInput::getLastWord(std::string input)
{
    std::istringstream stream(input);
    std::string word;
    std::string lastWord;

    while (stream >> word)
    {
        lastWord = word;
    }
    return lastWord;
}

/// @brief Takes a string and removes all non-alphabetic characters, lowercases without special characters
std::string LiveInput::sanitizeWord(std::string input)
{
    input = getLastWord(input);
    for (int i = 0; i < input.length(); i++)
    {
        if (!isalpha(input[i]))
        {
            input.erase(i, 1);
            i--;
        }
        else
        {
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
std::vector<std::string> LiveInput::getMatchingWords(std::string input, int searchType = 0)
{
    std::string lastWord = sanitizeWord(input);
    std::vector<std::string> result;
    if (lastWord.empty())
        return {};
    //updateWordFrequency(lastWord);
    result = mytrie.getWords(lastWord, *freq, searchType);
    return result;
}

/// @brief  Perform an operation on the Trie from the input from gui "specifically"
/// @param wordChoice sanitized word came from the user choice of suggested words
/// @param opChoice operation choice (0: insert, 1: delete)
/// @return answer of the operation (1: success, -1: failure)
/// @author Belal
// int LiveInput::performOperation(std::string wordChoice)
// {
//     std::cout << "choose operation: \n[1] Insert\n[2] Delete\n";
//     int choice = -1;
//     while (true)
//     {
//         std::cin >> choice;
//         if (std::cin.fail())
//         {
//             std::cin.clear();                                                   // Clear the error flag
//             std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
//             std::cout << "Invalid input. Please enter a number: ";
//             continue;
//         }
//         if (choice == 1 || choice == 2)
//             break;
//         std::cout << "Invalid choice. Please enter 1 for Insert, 2 for Delete: ";
//     }
//     if (choice == 1)
//     {
//         mytrie.insertWord(wordChoice);
//         (*freq)[wordChoice] = 3;
//         std::cout << "Word inserted successfully!\n";
//         return 1;
//     }
//     return -1; // return -1 if the operation is not valid
// }

void LiveInput::chooseSuggestedWord(std::string& input,int searchType,const std::vector<std::string>& words)
{
    int choice = 0;
    std::cout << "\n============================\n";
    // std::vector<std::string> words = getMatchingWords(input, searchType);
    // if no suggestions available get back.
    if (words.empty())
    {
        std::cout << "No suggestions available.\n";
        return;
    }
    else if (words.size() == 1)
    {
        std::cout << "Only one suggestion available: " << words[0] << "\n";
        input = words[0];
        choice = 1;
    }
    else
    {
        std::cout << "Choose a word by entering its number : ";
        while (true)
        {
            std::cin >> choice;
            if (std::cin.fail())
            {
                std::cin.clear();                                                   
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
                std::cout << "Invalid input. Please enter a number: ";
                continue;
            }
            if (choice >= 1 && choice <= words.size())
            {
                std::cout << "You chose: " << words[choice - 1] << "\n";
                break;
            }
            std::cout << "Invalid input. Please enter a number: ";
        }
    }
    std::cout << "Choose operation: \n[1] Confirm Delete\n[2] exit\n";
    std::cout << "Enter your choice: ";
    int opChoice = 1;
    while (true)
    {
        std::cin >> opChoice;
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number (1 or 2): ";
            continue;
        }
        if (opChoice == 1 || opChoice == 2)
            break;
        std::cout << "Invalid choice. Please enter 1 for Delete, 2 for go back: ";
    }
    if (opChoice == 1)
    {
        std::cout << "You chose to delete: " << words[choice - 1] << "\n";
        mytrie.deleteWord(words[choice - 1]);
        auto it = freq->find(words[choice - 1]);
        if (it != freq->end())
        {
            (*freq)[words[choice - 1]] = 0;
        }
        std::cout << "Word deleted successfully!\n";
    }
    else if (opChoice == 2)
    {
        std::cout << "Operation cancelled.\n";
    }
    // if (opResult == 1){
    //     std::cout << "Operation successful!\n";
    // }
    // else if (opResult == 2)
    // {
    //     size_t lastWord = getLastWord(input).length();
    //     while (lastWord--)
    //     {
    //         input.pop_back();
    //     }
    //     input.append(words[choice - 1]);
    //     return;
    // }
    // else if (opResult == -1)
    // {
    //     std::cout << "Operation failed!\n";
    // }
    return;
}

void LiveInput::displayHeader(int searchType){
    std::string choosenSearchType[3];
    choosenSearchType[0] = "->'\033[36m~\033[0m' most frequently used           |\n";
    choosenSearchType[1] = "->'\033[36m!\033[0m' lexicographical order          |\n";
    choosenSearchType[2] = "->'\033[36m@\033[0m' Shortest first                 |\n";

    if (searchType == 0)
    {
        choosenSearchType[0] = "\033[32m->\'~\' most frequently used\033[0m           |\n";
    }
    else if (searchType == 1)
    {
        choosenSearchType[1] = "\033[32m->\'!\' lexicographical order\033[0m          |\n";
    }
    else if (searchType == 2)
    {
        choosenSearchType[2] = "\033[32m->\'@\' Shortest first\033[0m                 |\n";
    }
    std::cout << "\n+ =========================================================================================================== +\n";
    std::cout << "+ ========================= +\t+ =========== Options =========== +\t+ =========== Searching types ======= +\n";
    std::cout << "|                           |\t|-> \'\033[36m\\\033[0m\' to insert or Delete       |\t|" + (choosenSearchType[0]);
    std::cout << "|   Input text Down here    |\t|-> \033[36mTAB\033[0m to auto complete          |\t|" + (choosenSearchType[1]);
    std::cout << "|                           |\t|-> \033[36mESC\033[0m to back to home menu      |\t|" + (choosenSearchType[2]);
    std::cout << "+ ========================= +\t+ =============================== +\t+ =================================== +\n";
    std::cout << "+ ----------------------------------------------------------------------------------------------------------- +\n";
    std::cout << "+ ------------------------------------------- Enter input here ---------------------------------------------- +\n";
}
