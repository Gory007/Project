#include "MainWindow.h"
#include "AddWordsWindow.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QApplication>
#include "EditWordsWindow.h"
#include "TrainingWindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    setWindowTitle("Vocabulary Trainer");
    resize(300, 200);
    setupUI();
}

void MainWindow::setupUI() {
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    
    addWordsButton = new QPushButton("Добавление слов", this);
    editWordsButton = new QPushButton("Редактирование слов", this);
    trainingButton = new QPushButton("Тренировка", this);
    exitButton = new QPushButton("Выход", this);
    
    layout->addWidget(addWordsButton);
    layout->addWidget(editWordsButton);
    layout->addWidget(trainingButton);
    layout->addWidget(exitButton);
    
    setCentralWidget(centralWidget);
    
    // Подключаем сигналы
    connect(addWordsButton, &QPushButton::clicked, this, &MainWindow::onAddWordsClicked);
    connect(editWordsButton, &QPushButton::clicked, this, &MainWindow::onEditWordsClicked);
    connect(trainingButton, &QPushButton::clicked, this, &MainWindow::onTrainingClicked);
    connect(exitButton, &QPushButton::clicked, qApp, &QApplication::quit);
}

void MainWindow::onAddWordsClicked() {
    Dictionary dict("C:/Project/resources/dictionary.txt");  // Путь к файлу
    AddWordsWindow addWindow(dict, this);
    addWindow.exec();
}

void MainWindow::onEditWordsClicked() {
    Dictionary dict("C:/Project/resources/dictionary.txt");
    EditWordsWindow editWindow(dict, this);
    editWindow.exec();
}

void MainWindow::onTrainingClicked() {
    Dictionary dict("C:/Project/resources/dictionary.txt");
    TrainingWindow trainingWindow(dict, this);
    trainingWindow.exec();
}