#pragma once
#include <QDialog>
#include <QTableWidget>
#include <QPushButton>
#include "Dictionary.h"

class EditWordsWindow : public QDialog {
    Q_OBJECT

public:
    EditWordsWindow(Dictionary& dictionary, QWidget* parent = nullptr);

private slots:
    void onConfirmClicked();
    void onRemoveClicked();
    void onDoneClicked();

private:
    Dictionary& dictionary;
    QTableWidget* table;
    QPushButton* confirmButton;
    QPushButton* removeButton;
    QPushButton* doneButton;

    void setupUI();
    void loadWordsIntoTable();
};