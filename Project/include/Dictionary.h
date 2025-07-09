#pragma once
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <stdexcept>  // для исключений

class Dictionary {
public:
    Dictionary(const std::string& filePath);
    
    void addWord(const std::string& unknown, const std::string& translation);
    void saveToFile();
    const std::vector<std::pair<std::string, std::string>>& getWords() const;
    
private:
    std::vector<std::pair<std::string, std::string>> words;
    std::string filePath;
    
    void loadFromFile();
};