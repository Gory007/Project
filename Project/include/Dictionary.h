#pragma once
#include <vector>
#include <string>
#include <utility> // для std::pair

class Dictionary {
public:
    Dictionary(const std::string& filePath);
    
    void addWord(const std::string& unknown, const std::string& translation);
    void saveToFile();
    
    // Для последующих этапов
    std::vector<std::pair<std::string, std::string>>& getWords();
    
private:
    std::vector<std::pair<std::string, std::string>> words;
    std::string filePath;
    
    void loadFromFile();
};