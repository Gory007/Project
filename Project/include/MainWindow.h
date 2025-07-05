#pragma once
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = nullptr);
    
private slots:
    void onAddWordsClicked();
    void onEditWordsClicked();
    void onTrainingClicked();
    
private:
    QPushButton *addWordsButton;
    QPushButton *editWordsButton;
    QPushButton *trainingButton;
    QPushButton *exitButton;
    
    void setupUI();
};