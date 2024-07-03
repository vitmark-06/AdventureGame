#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>

#include "settingswindow.h"
#include "gamefield.h"

class StartWindow : public QWidget {
    Q_OBJECT

public:
    StartWindow(QWidget* parent = nullptr);

signals:
    void gameStarted(const QString& player1Name, const QString& player2Name);

private slots:
    void startGame();
    void openSettings();
    void showHighScores();
    void exitGame();
    void updatePlayerNames(const QString& player1Name, const QString& player2Name);

private:
    QString getPlayer1Name() const;
    QString getPlayer2Name() const;

    void setPlayer1Name(const QString& name);
    void setPlayer2Name(const QString& name);

    QLineEdit* m_player1NameEdit;
    QLineEdit* m_player2NameEdit;
    QPushButton* m_startButton;
    QPushButton* m_highScoresButton;
    QPushButton* m_settingsButton;
    QPushButton* m_exitButton;

    SettingsWindow* m_settingsWindow;

};

#endif // STARTWINDOW_H
