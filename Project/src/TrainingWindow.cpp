#include "TrainingWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

TrainingWindow::TrainingWindow(Dictionary& dictionary, QWidget* parent)
    : QDialog(parent), dictionary(dictionary) {
    setWindowTitle("Тренировка");
    resize(400, 300);
    setupUI();
    showNewWord();
}

void TrainingWindow::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    wordLabel = new QLabel("", this);
    wordLabel->setAlignment(Qt::AlignCenter);
    wordLabel->setStyleSheet("font-size: 20px;");

    statsLabel = new QLabel("", this);
    statsLabel->setAlignment(Qt::AlignCenter);

    checkButton = new QPushButton("Проверить", this);
    correctButton = new QPushButton("Верно", this);
    incorrectButton = new QPushButton("Неверно", this);
    finishButton = new QPushButton("Финиш", this);

    correctButton->setVisible(false);
    incorrectButton->setVisible(false);

    layout->addWidget(wordLabel);
    layout->addWidget(statsLabel);
    layout->addWidget(checkButton);
    layout->addWidget(correctButton);
    layout->addWidget(incorrectButton);
    layout->addWidget(finishButton);

    connect(checkButton, &QPushButton::clicked, this, &TrainingWindow::onCheckClicked);
    connect(correctButton, &QPushButton::clicked, this, &TrainingWindow::onCorrectClicked);
    connect(incorrectButton, &QPushButton::clicked, this, &TrainingWindow::onIncorrectClicked);
    connect(finishButton, &QPushButton::clicked, this, &TrainingWindow::onFinishClicked);
}

void TrainingWindow::showNewWord() {
    try {
        currentWordIndex = dictionary.getRandomWordIndex();
        const auto& words = dictionary.getWords();
        wordLabel->setText(QString::fromStdString(words[currentWordIndex].first));
        checkButton->setVisible(true);
        correctButton->setVisible(false);
        incorrectButton->setVisible(false);
        updateStatsLabel();
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
        close();
    }
}

void TrainingWindow::updateStatsLabel() {
    QString statsText = QString("Сессия: %1 верно / %2 неверно")
                        .arg(sessionCorrect)
                        .arg(sessionIncorrect);
    statsLabel->setText(statsText);
}

void TrainingWindow::onCheckClicked() {
    const auto& words = dictionary.getWords();
    wordLabel->setText(QString::fromStdString(words[currentWordIndex].second));
    checkButton->setVisible(false);
    correctButton->setVisible(true);
    incorrectButton->setVisible(true);
}

void TrainingWindow::onCorrectClicked() {
    dictionary.markCorrect(currentWordIndex);
    sessionCorrect++;
    showNewWord();
}

void TrainingWindow::onIncorrectClicked() {
    dictionary.markIncorrect(currentWordIndex);
    sessionIncorrect++;
    showNewWord();
}

void TrainingWindow::onFinishClicked() {
    QMessageBox::information(this, "Статистика",
        QString("Итог тренировки:\nВерно: %1\nНеверно: %2")
        .arg(sessionCorrect)
        .arg(sessionIncorrect));
    close();
}