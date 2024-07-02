#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "gamefield.h"

#include <QApplication>
#include <QLabel>

class StartWindow : public QWidget {
    Q_OBJECT

public:
    StartWindow(QWidget* parent = nullptr);

signals:
    void gameStarted();

private slots:
    void startGame();
    void openSettings();
    void showHighScores();
    void exitGame();
};


#endif // STARTWINDOW_H
