#pragma once
#include "../../Utilities/Data_Fetching/DataFetcher.h"
#include "../../Utilities/Data_Structures/Trie.h"
#include <unordered_map>

/**
 * * @class BFF (Backend-for-frontend)
 * @brief The logic of the AutoComplete meets here
 * A Class to handle connection between database and the front end and the words processes
 * @author Belal & Peter & Kevin
 */

class BFF
{
public:
    Trie trie;
    std::unordered_map<std::string, int> freq;

    void addWord(std::string);
    void removeWord(std::string);
    BFF(DataFetcher &df);
    ~BFF();
};