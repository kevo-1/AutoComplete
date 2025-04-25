#include <iostream>
#include <fstream>
#include <unordered_map>


/**
 * @class DataFetcher
 * @brief Data writing and reading
 *  
 * A Class to handle loading the dictionary of previously used words and save them when done
 *
 * @author Peter & Kevin
 */
class DataFetcher {
public:
    private:
        std::fstream dictionary;

    public:
        std::unordered_map<std::string, int> frequency; // -> to be sent to the client & <- receive from the client a hash table
        std::string path = "AutoComplete\Storage\Dictionary.txt"; //string : freq

        
        DataFetcher() : dictionary(path, std::ios::in | std::ios::out) {
            try {
                this->dictionary.open(path);
            } catch(std::exception& e) {
                std::cerr << e.what() << '\n';
            }
    }

    std::unordered_map<std::string, int> dictionaryMap() {
        std::unordered_map<std::string, int> dict;
        std::string word;
        int freq;

        while (dictionary >> word >> freq) {
            dict[word] = freq;
        }

        return dict;
    }
    
    std::unordered_map<std::string, int> LoadFrequency() {
        std::string word;
        int freq;
        while(this->dictionary >> word >> freq) {
            this->frequency[word] = freq;
        }
        this->dictionary.close();
        return this->frequency;
    }

    void SaveFrequency(std::unordered_map<std::string, int> data) {
        std::ofstream file(path, std::ios::out | std::ios::trunc);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + path);
        }
        for(const auto& [word, freq] : data) {
            file << word << " " << freq << '\n';
        }        
    };

};

