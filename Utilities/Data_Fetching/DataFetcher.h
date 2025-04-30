#ifndef DATAFETCHER_H
#define DATAFETCHER_H

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
private:
    std::fstream dictionary;  // File stream for dictionary

public:
    std::unordered_map<std::string, int> frequency;  // Frequency map to store word counts
    std::string path = "../Storage/Dictionary.txt";  // Path to dictionary file

    // Constructor and Destructor declarations
    DataFetcher();
    ~DataFetcher();

    // Methods to load and save frequency data
    std::unordered_map<std::string, int> LoadFrequency();
    void SaveFrequency(std::unordered_map<std::string, int> &data);
};

#endif  // DATAFETCHER_H
