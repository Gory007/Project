#include "EditWordsWindow.h"
#include <QVBoxLayout>
#include <QHeaderView>
#include <QMessageBox>

EditWordsWindow::EditWordsWindow(Dictionary& dictionary, QWidget* parent)
    : QDialog(parent), dictionary(dictionary) {
    setWindowTitle("Редактирование слов");
    resize(500, 400);
    setupUI();
}

void EditWordsWindow::setupUI() {
    QVBoxLayout* layout = new QVBoxLayout(this);

    table = new QTableWidget(this);
    table->setColumnCount(2);
    table->setHorizontalHeaderLabels({"Слово на аглийском", "Перевод слова"});
    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::DoubleClicked);

    confirmButton = new QPushButton("Подтвердить", this);
    removeButton = new QPushButton("Удалить", this);
    doneButton = new QPushButton("Готово", this);

    layout->addWidget(table);
    layout->addWidget(confirmButton);
    layout->addWidget(removeButton);
    layout->addWidget(doneButton);

    loadWordsIntoTable();

    connect(confirmButton, &QPushButton::clicked, this, &EditWordsWindow::onConfirmClicked);
    connect(removeButton, &QPushButton::clicked, this, &EditWordsWindow::onRemoveClicked);
    connect(doneButton, &QPushButton::clicked, this, &EditWordsWindow::onDoneClicked);
}

void EditWordsWindow::loadWordsIntoTable() {
    const auto& words = dictionary.getWords();
    table->setRowCount(words.size());

    for (int i = 0; i < words.size(); ++i) {
        table->setItem(i, 0, new QTableWidgetItem(QString::fromStdString(words[i].first)));
        table->setItem(i, 1, new QTableWidgetItem(QString::fromStdString(words[i].second)));
    }
}

void EditWordsWindow::onConfirmClicked() {
    try {
        for (int i = 0; i < table->rowCount(); ++i) {
            QString unknown = table->item(i, 0)->text();
            QString translation = table->item(i, 1)->text();
            dictionary.editWord(i, unknown.toStdString(), translation.toStdString());
        }
        QMessageBox::information(this, "Успех", "Изменения сохранены!");
    } catch (const std::exception& e) {
        QMessageBox::warning(this, "Ошибка", e.what());
    }
}

void EditWordsWindow::onRemoveClicked() {
    int row = table->currentRow();
    if (row >= 0) {
        try {
            dictionary.removeWord(row);
            table->removeRow(row);
        } catch (const std::exception& e) {
            QMessageBox::warning(this, "Ошибка", e.what());
        }
    } else {
        QMessageBox::warning(this, "Ошибка", "Выберите слово для удаления!");
    }
}

void EditWordsWindow::onDoneClicked() {
    close();
}