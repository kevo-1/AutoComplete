#include <iostream>
#include <fstream>
#include <unordered_map>
#include <DataFetcher.h>


DataFetcher::DataFetcher() : path("../../Storage/Dictionary.txt") {
    dictionary.open(path, std::ios::in | std::ios::out);
    if (!dictionary.is_open()) {
        std::cerr << "ERROR: Failed to open file at: " << path << std::endl;
        throw std::runtime_error("Failed to open file: " + path);
    }
}

std::unordered_map<std::string, int> DataFetcher::LoadFrequency() {
    std::string word;
    int freq;
    while(this->dictionary >> word >> freq) {
        this->frequency[word] = freq;
    }
    this->dictionary.close();
    return this->frequency;
}

void DataFetcher::SaveFrequency(std::unordered_map<std::string, int>& data) {
    std::ofstream file(path, std::ios::out | std::ios::trunc);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open file: " + path);
    }
    for(const auto& [word, freq] : data) {
        file << word << " " << freq << '\n';
    }        
}

DataFetcher::~DataFetcher() {
    if(dictionary.is_open()) {
        dictionary.close();
    }
}

