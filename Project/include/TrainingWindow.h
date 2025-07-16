#pragma once
#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include "Dictionary.h"

class TrainingWindow : public QDialog {
    Q_OBJECT

public:
    TrainingWindow(Dictionary& dictionary, QWidget* parent = nullptr);

private slots:
    void onCheckClicked();
    void onCorrectClicked();
    void onIncorrectClicked();
    void onFinishClicked();

private:
    Dictionary& dictionary;
    int currentWordIndex = -1;
    int sessionCorrect = 0;
    int sessionIncorrect = 0;

    QLabel* wordLabel;
    QLabel* statsLabel;
    QPushButton* checkButton;
    QPushButton* correctButton;
    QPushButton* incorrectButton;
    QPushButton* finishButton;

    void setupUI();
    void showNewWord();
    void updateStatsLabel();
};