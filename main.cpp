
#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QStackedWidget>

#include "gamefield.h"
#include "startwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    QMainWindow mainWindow;
    mainWindow.setWindowTitle("AdventureGame");
    //mainWindow.resize(1000, 600);
    mainWindow.showFullScreen();

    QStackedWidget* stackedWidget = new QStackedWidget(&mainWindow);

    StartWindow* startWindow = new StartWindow(stackedWidget);
    stackedWidget->addWidget(startWindow);

    GameField* gameField = new GameField(stackedWidget);

    stackedWidget->addWidget(gameField);

    mainWindow.setCentralWidget(stackedWidget);

    QObject::connect(startWindow, &StartWindow::gameStarted, [stackedWidget]() {
        stackedWidget->setCurrentIndex(1);
    });

    mainWindow.show();
    return app.exec();
}
