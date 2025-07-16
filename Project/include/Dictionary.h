#pragma once
#include <vector>
#include <map>
#include <string>
#include <utility>
#include <fstream>
#include <stdexcept>

struct WordStats {
    int correct = 0;
    int incorrect = 0;
};

class Dictionary {
public:
    Dictionary(const std::string& filePath);
    
    void addWord(const std::string& unknown, const std::string& translation);
    void saveToFile();
    const std::vector<std::pair<std::string, std::string>>& getWords() const;

    void editWord(int index, const std::string& newUnknown, const std::string& newTranslation);
    void removeWord(int index);

    void markCorrect(int index);
    void markIncorrect(int index);
    int getWordWeight(int index) const;

    int getRandomWordIndex() const;
    
private:
    std::vector<std::pair<std::string, std::string>> words;
    std::string filePath;

    std::map<int, WordStats> stats;
    
    void loadFromFile();
};