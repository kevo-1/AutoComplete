#include "../../Utilities/Data_Fetching/DataFetcher.h"
#include "../../Utilities/Data_Structures/Trie.h"
#include <unordered_map>

/**
 * * @class BFF (Backend-for-frontend)
 * @brief The logic of the AutoComplete meets here
 * A Class to handle connection between database and the front end and the words
 * @author Belal & Peter & Kevin
 */

class BFF
{
public:
    Trie trie;
    std::unordered_map<std::string, int> freq;

    int addWord(std::string);
    int removeWord(std::string);
private:
    BFF(DataFetcher &df);
    ~BFF();
};