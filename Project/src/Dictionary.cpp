#include "Dictionary.h"
#include <algorithm>
#include <random>

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

void Dictionary::markCorrect(int index) {
    stats[index].correct++;
    saveToFile();
}

void Dictionary::markIncorrect(int index) {
    stats[index].incorrect++;
    saveToFile();
}

int Dictionary::getWordWeight(int index) const {
    if (stats.count(index)) {
        const auto& s = stats.at(index);
        // Чем больше ошибок, тем выше вес (слово показывается чаще)
        return s.incorrect * 2 + 1;
    }
    return 1;  // Вес по умолчанию
}

int Dictionary::getRandomWordIndex() const {
    if (words.empty()) {
        throw std::runtime_error("Словарь пуст");
    }

    // Создаем "взвешенный" список индексов
    std::vector<int> weightedIndices;
    for (int i = 0; i < words.size(); ++i) {
        int weight = getWordWeight(i);
        for (int j = 0; j < weight; ++j) {
            weightedIndices.push_back(i);
        }
    }

    // Случайный выбор
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, weightedIndices.size() - 1);
    
    return weightedIndices[distr(gen)];
}