#include "AddWordsWindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>

AddWordsWindow::AddWordsWindow(Dictionary& dictionary, QWidget* parent)
    : QDialog(parent), dictionary(dictionary) {
    setWindowTitle("Добавление слов");
    resize(300, 200);
    setupUI();
}

void AddWordsWindow::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    QLabel* unknownLabel = new QLabel("Слово на английском:", this);
    unknownInput = new QLineEdit(this);

    QLabel* translationLabel = new QLabel("Перевод слова:", this);
    translationInput = new QLineEdit(this);

    confirmButton = new QPushButton("Подтвердить", this);
    doneButton = new QPushButton("Готово", this);

    layout->addWidget(unknownLabel);
    layout->addWidget(unknownInput);
    layout->addWidget(translationLabel);
    layout->addWidget(translationInput);
    layout->addWidget(confirmButton);
    layout->addWidget(doneButton);

    connect(confirmButton, &QPushButton::clicked, this, &AddWordsWindow::onConfirmClicked);
    connect(doneButton, &QPushButton::clicked, this, &AddWordsWindow::onDoneClicked);
}

void AddWordsWindow::onConfirmClicked() {
    try {
        QString unknown = unknownInput->text().trimmed();
        QString translation = translationInput->text().trimmed();
        
        if (unknown.isEmpty() || translation.isEmpty()) {
            throw std::invalid_argument("Заполните оба поля");
        }
        
        dictionary.addWord(
            unknown.toStdString(),
            translation.toStdString()
        );
        
        unknownInput->clear();
        translationInput->clear();
        QMessageBox::information(this, "Успех", "Слова добавлены в словарь!");
        
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void AddWordsWindow::onDoneClicked() {
    close();
}