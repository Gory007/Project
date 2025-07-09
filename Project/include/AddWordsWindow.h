#pragma once
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include "Dictionary.h"

class AddWordsWindow : public QDialog {
    Q_OBJECT

public:
    AddWordsWindow(Dictionary& dictionary, QWidget* parent = nullptr);

private slots:
    void onConfirmClicked();
    void onDoneClicked();

private:
    Dictionary& dictionary;
    QLineEdit* unknownInput;
    QLineEdit* translationInput;
    QPushButton* confirmButton;
    QPushButton* doneButton;

    void setupUI();
};