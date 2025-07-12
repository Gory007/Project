#include "Dictionary.h"
#include <algorithm>

Dictionary::Dictionary(const std::string& filePath) : filePath(filePath) {
    loadFromFile();
}

void Dictionary::loadFromFile() {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось открыть файл словаря");
    }

    words.clear();
    std::string unknown, translation;
    while (file >> unknown >> translation) {
        words.emplace_back(unknown, translation);
    }
}

void Dictionary::addWord(const std::string& unknown, const std::string& translation) {
    if (unknown.empty() || translation.empty()) {
        throw std::invalid_argument("Оба поля должны быть заполнены");
    }
    words.emplace_back(unknown, translation);
    saveToFile();
}

void Dictionary::saveToFile() {
    std::ofstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Не удалось сохранить словарь");
    }

    for (const auto& pair : words) {
        file << pair.first << " " << pair.second << "\n";
    }
}

const std::vector<std::pair<std::string, std::string>>& Dictionary::getWords() const {
    return words;
}

void Dictionary::editWord(int index, const std::string& newUnknown, const std::string& newTranslation) {
    if (index < 0 || index >= words.size()) {
        throw std::out_of_range("Неверный индекс слова");
    }
    words[index] = {newUnknown, newTranslation};
    saveToFile();
}

void Dictionary::removeWord(int index) {
    if (index < 0 || index >= words.size()) {
        throw std::out_of_range("Неверный индекс слова");
    }
    words.erase(words.begin() + index);
    saveToFile();
}