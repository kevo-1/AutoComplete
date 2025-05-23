#include <iostream>
#include <iomanip>
#include <sstream>
#include <unordered_map>
#include "liveInput.h"
#include <vector>
#include <string>
#include <stack>
#include <limits>
#include<cctype>
#include "../Data_Structures/Trie.h"
#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif
//Belal
//delete from map along with the trie[done]
//insert(hat7ott el word in the trie+in the map with freq=3 if it doesn't exist)[done]
// live input works good while fetched data have some problems with some words !!! under testing




/// @brief Constructor for LiveInput class
/// @details Initializes the LiveInput object with a Trie and a frequency map.
/// @param trie
/// @param frequency
/// @author Belal
LiveInput::LiveInput(Trie &tr, std::unordered_map<std::string, int> *frequency) : mytrie{tr}, freq{frequency}
{
    tr.displayTrie();
    if (freq->empty())
    {
        std::cout << "No words in the frequency map.\n";
    }
}


/// @brief provides greyed out text to seen for complete
/// @param words suggested words
/// @param input input str
/// @return non typed part of the first suggestion
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
            suggStack.pop();
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
            char lastChar=input.back();
            
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
                input.append(words[wordChoiceNum-1]);
                input+=' ';
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
std::cout << "Enter Backslash to choose suggested word! \n";
std::cout << input <<"\033[2m"<<completeGreyedOut(words, input)<<"\033[0m\n";
std::cout << "\n============================\n";
std::cout << "Suggested words: \n";

//added upper bound: 9 bec i only have numbers 1-9 to chose from in completion
for (int i = 0; i < words.size() && i<9; i++)
{
    displayWord(i,input,words[i]);
    if ((i + 1) % 5 == 0)
    {
        std::cout << std::endl;
    }
}
std::cout<<"\n\nOrder of suggestions: ";
if (searchType==0)
{
    std::cout<<"Most frequently used\n";
}else if (searchType==1)
{
    std::cout<<"Lexicographical\n";
}else if (searchType==2)
{
    std::cout<<"Shortest first\n";
}

std::cout<<"\nTo change suggestion order enter: \n\033[34m~\033[0m for most frequently used\n\033[34m!\033[0m for lexicographical order\n\033[34m@\033[0m for shortest first\n";

}


/// @brief Starts flow of live input for (terminal) and suggest words
/// not tested yet, and no suggestion can be choosen!
void LiveInput::startLiveInput()
{
    //debugging purpose
    for(auto& [word, fre] : (*freq)) {
        std::cout<<word<<" "<<fre<<'\n';
    }
    system("pause");
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
        
        
        if (c == ENTER_KEY || c == CARRIAGE_RETURN || c == ESCAPE)
            break;
        if (c == BACKSPACE || c == DELETE)
        {
            if (!input.empty())
                input.pop_back();
        }
        if (c==BACKSLASH)
        {
            chooseSuggestedWord(input,searchType);
            continue;
        }
        
        if (c == SPACE)
        {
            currentWord = sanitizeWord(input);
            updateWordFrequency(currentWord);
            currentWord.clear();
        }

        
        chooseSearchType(c,searchType);

        //moved this here in order to use it in completing using suggestions
        std::vector<std::string> words = getMatchingWords(input, searchType);
        
        
        replaceWithSuggestion(words,input,c);
        
        mainDisplay(words,input,searchType);
        


    }
    mytrie.displayTrie(); // Display the Trie after exiting the loop
    //debugging purpose
    for(auto& [word, fre] : (*freq)) {
        std::cout<<word<<" "<<fre<<'\n';
    }
    system("pause");
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
int LiveInput::performOperation(std::string wordChoice, int opChoice)
{
    if (opChoice == 1)
    {
        return 2;
    }
    else if (opChoice == 2)
    {
        mytrie.deleteWord(wordChoice);
        // reset frequency to zero.
        auto it = freq->find(wordChoice);
        if (it != freq->end())
        {
            (*freq)[wordChoice] = 0;
        }
        return 1;
    }
    return -1; // return -1 if the operation is not valid
}

void LiveInput::chooseSuggestedWord(std::string& input,int searchType)
{
    std::cout << "\n============================\n";
    std::vector<std::string> words = getMatchingWords(input, searchType);
    // if no suggestions available get back.
    if (words.empty())
    {
        std::cout << "No suggestions available.\n";
        return;
    }
    std::cout << "Choose a word by entering its number : ";
    int choice = 0;
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
        if (choice >= 1 && choice <= words.size())
        {
            std::cout << "You chose: " << words[choice - 1] << "\n";
            break;
        }
        std::cout << "Invalid input. Please enter a number: ";
    }
    std::cout << "Choose operation: \n[1] Complete\n[2] Delete\n[3] Cancel\n";
    int opChoice = 0;
    while (true)
    {
        std::cin >> opChoice;
        if (std::cin.fail())
        {
            std::cin.clear();                                                   // Clear the error flag
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number (1, 2, or 3): ";
            continue;
        }
        if (opChoice == 1 || opChoice == 2 || opChoice == 3)
            break;
        std::cout << "Invalid choice. Please enter 1 for Complete, 2 for Delete, or 3 to Cancel: ";
    }
    if (opChoice == 3)
    {
        std::cout << "Operation cancelled.\n";
        return;
    }
    int opResult = performOperation(words[choice - 1], opChoice);
    if (opResult == 1){
        std::cout << "Operation successful!\n";
    }
    else if (opResult == 2)
    {
        size_t lastWord = getLastWord(input).length();
        while (lastWord--)
        {
            input.pop_back();
        }
        input.append(words[choice - 1]);
        return;
    }
    else if (opResult == -1)
    {
        std::cout << "Operation failed!\n";
    }
    std::cout << "\n============================\n";
}