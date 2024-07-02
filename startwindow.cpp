#include "startwindow.h"

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QScreen>
#include <QStyleFactory>

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: #E5E5E5;");

    auto* mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(50, 50, 50, 50);

    auto* titleLabel = new QLabel("Welcome to the Game!");
    titleLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #333;");
    mainLayout->addWidget(titleLabel, 0, 0, 1, 2, Qt::AlignCenter);

    auto* startButton = new QPushButton("Start Game");
    startButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(startButton, 1, 0, Qt::AlignCenter);
    connect(startButton, &QPushButton::clicked, this, &StartWindow::startGame);

    auto* highScoresButton = new QPushButton("High Scores");
    highScoresButton->setStyleSheet("background-color: #2196F3; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(highScoresButton, 1, 1, Qt::AlignCenter);
    connect(highScoresButton, &QPushButton::clicked, this, &StartWindow::showHighScores);

    auto* settingsButton = new QPushButton("Settings");
    settingsButton->setStyleSheet("background-color: #9C27B0; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(settingsButton, 2, 0, Qt::AlignCenter);
    connect(settingsButton, &QPushButton::clicked, this, &StartWindow::openSettings);

    auto* exitButton = new QPushButton("Exit");
    exitButton->setStyleSheet("background-color: #F44336; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(exitButton, 2, 1, Qt::AlignCenter);
    connect(exitButton, &QPushButton::clicked, this, &StartWindow::exitGame);

    auto* screen = QGuiApplication::screens().first();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void StartWindow::startGame() {
    emit gameStarted();
    close();
}

void StartWindow::showHighScores() {
    qDebug() << "Showing high scores";
}

void StartWindow::exitGame() {
    QApplication::exit();
}

void StartWindow::openSettings() {
    qDebug() << "Opening settings";
}
