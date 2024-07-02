#include <QApplication>
#include <QStackedWidget>
#include "startwindow.h"
#include "gamefield.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QStackedWidget stackedWidget;
    stackedWidget.showFullScreen();

    StartWindow startWindow;
    stackedWidget.addWidget(&startWindow);

    GameField* gameField = nullptr;

    QObject::connect(&startWindow, &StartWindow::gameStarted, [&](const QString& player1Name, const QString& player2Name) {
        gameField = new GameField(player1Name, player2Name, &stackedWidget);

        stackedWidget.addWidget(gameField);
        stackedWidget.setCurrentWidget(gameField);
    });

    stackedWidget.show();

    return app.exec();
}
