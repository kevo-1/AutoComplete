#include <iostream>
#include <fstream>
#include <unordered_map>

class DataFetcher {
public:
    private:
        std::fstream dictionary;

    public:
        std::unordered_map<std::string, int> frequency;
        std::string path = "AutoComplete\Storage\Dictionary.txt";

        DataFetcher(){};
        std::unordered_map<std::string, int> dictionaryMap() {};
        std::unordered_map<std::string, int> LoadFrequency() {};
        void SaveFrequency(std::unordered_map<std::string, int> data) {};
};

