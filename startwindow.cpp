#include "startwindow.h"

#include <QApplication>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QScreen>
#include <QStyleFactory>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

StartWindow::StartWindow(QWidget *parent) : QWidget(parent) {
    setStyleSheet("background-color: #E5E5E5;");

    auto* mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(50, 50, 50, 50);

    auto* titleLabel = new QLabel("Welcome to the Adventure game!");
    titleLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #333;");
    mainLayout->addWidget(titleLabel, 0, 0, 1, 2, Qt::AlignCenter);

    auto* player1NameLabel = new QLabel("Player 1 Name:");
    player1NameLabel->setStyleSheet("font-size: 18px; color: #333;");
    mainLayout->addWidget(player1NameLabel, 1, 0, Qt::AlignRight);

    m_player1NameEdit = new QLineEdit();
    m_player1NameEdit->setStyleSheet("font-size: 18px; padding: 5px;");
    mainLayout->addWidget(m_player1NameEdit, 1, 1, Qt::AlignLeft);

    auto* player2NameLabel = new QLabel("Player 2 Name:");
    player2NameLabel->setStyleSheet("font-size: 18px; color: #333;");
    mainLayout->addWidget(player2NameLabel, 2, 0, Qt::AlignRight);

    m_player2NameEdit = new QLineEdit();
    m_player2NameEdit->setStyleSheet("font-size: 18px; padding: 5px;");
    mainLayout->addWidget(m_player2NameEdit, 2, 1, Qt::AlignLeft);

    m_startButton = new QPushButton("Start Game");
    m_startButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(m_startButton, 3, 0, Qt::AlignCenter);
    connect(m_startButton, &QPushButton::clicked, this, &StartWindow::startGame);

    m_highScoresButton = new QPushButton("High Scores");
    m_highScoresButton->setStyleSheet("background-color: #2196F3; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(m_highScoresButton, 3, 1, Qt::AlignCenter);
    connect(m_highScoresButton, &QPushButton::clicked, this, &StartWindow::showHighScores);

    m_settingsButton = new QPushButton("Settings");
    m_settingsButton->setStyleSheet("background-color: #9C27B0; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(m_settingsButton, 4, 0, Qt::AlignCenter);
    connect(m_settingsButton, &QPushButton::clicked, this, &StartWindow::openSettings);

    m_exitButton = new QPushButton("Exit");
    m_exitButton->setStyleSheet("background-color: #F44336; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(m_exitButton, 4, 1, Qt::AlignCenter);
    connect(m_exitButton, &QPushButton::clicked, this, &StartWindow::exitGame);

    auto* screen = QGuiApplication::screens().first();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void StartWindow::startGame()
{
    QString player1Name = getPlayer1Name();
    QString player2Name = getPlayer2Name();
    GameField* gameField = new GameField(player1Name, player2Name);
    emit gameStarted(player1Name, player2Name);
}

void StartWindow::showHighScores() {
    QString highScoresFile = "game_results.txt";
    QFile file(highScoresFile);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString highScoresText;
        while (!in.atEnd()) {
            QString line = in.readLine();
            highScoresText += line + "\n";
        }
        file.close();
        QMessageBox::information(this, "High Scores", highScoresText);
    } else {
        QMessageBox::warning(this, "Error", "Failed to open high scores file.");
    }
}

void StartWindow::exitGame() {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Exit Game", "Are you sure you want to exit the game?",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        QApplication::exit();
    }
}

QString StartWindow::getPlayer1Name() const
{
    return m_player1NameEdit->text();
}

QString StartWindow::getPlayer2Name() const
{
    return m_player2NameEdit->text();
}

void StartWindow::openSettings()
{
    m_settingsWindow = new SettingsWindow(this);
    m_settingsWindow->setPlayer1Name(m_player1NameEdit->text());
    m_settingsWindow->setPlayer2Name(m_player2NameEdit->text());
    connect(m_settingsWindow, &SettingsWindow::settingsSaved, this, &StartWindow::updatePlayerNames);
    m_settingsWindow->exec();
}

void StartWindow::updatePlayerNames(const QString& player1Name, const QString& player2Name)
{
    m_player1NameEdit->setText(player1Name);
    m_player2NameEdit->setText(player2Name);
}
