#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QGridLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QTimer>
#include <QVector>
#include <QWidget>
#include <random>
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QApplication>

#include "numberwidget.h"
#include "RectangleWidget.h"
#include "token.h"

class GameField : public QWidget {
    Q_OBJECT

public:
    GameField(QWidget* parent = nullptr);

protected:
    void paintEvent(QPaintEvent*);

private:
    QColor getFieldColor(int index);
    void moveToken(Token* token, int steps);
    void showWinnerMessage();
    void updateUI();
    void resetGame();
    QString getWinnerName() const;
    int getCurrentAttempt() const;
    void createMenu();

    QGridLayout* layout;
    QGridLayout* m_layout;
    QVBoxLayout* h_layout;
    QPushButton* rollDice;
    QPushButton* exitButton;
    QVector<QColor> colors = {Qt::red, Qt::green, Qt::blue, Qt::green, Qt::green, Qt::gray, Qt::green, Qt::black, Qt::green};
    NumberWidget* numberWidget;
    QLabel* currentPlayerLabel;
    Token* token1;
    Token* token2;
    Token* currentToken;
    Token* winner = nullptr;

    QMenuBar* menuBar;
    QMenu* gameMenu;
    QAction* newGameAction;
    QAction* rulesAction;
    QAction* aboutAction;
    QAction* saveResultsAction;
    QAction* exitAction;
    int m_currentAttempt = 0;


private slots:
    void rollDiceButtonClicked();

    void newGameTriggered();
    void rulesTriggered();
    void aboutTriggered();
    void saveResultsTriggered();
    void exitTriggered();


};


#endif // GAMEFIELD_H
