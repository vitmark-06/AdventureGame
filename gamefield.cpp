#include "gamefield.h"

GameField::GameField(const QString& player1Name, const QString& player2Name, QWidget* parent)
    : QWidget(parent), m_player1Name(player1Name), m_player2Name(player2Name)
{
    QPixmap backgroundImage("C:/Users/User/Desktop/Projects/ProgectQt/AdventureGame/image/space.jpg");
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(backgroundImage));
    setPalette(palette);

    layout = new QGridLayout(this);
    layout->setSpacing(20);
    layout->setContentsMargins(30, 30, 30, 30);

    m_layout = new QGridLayout;
    m_layout->setSpacing(0);

    h_layout = new QVBoxLayout;
    h_layout->setSpacing(20);

    numberWidget = new NumberWidget;
    numberWidget->setStyleSheet("font-size: 36px; font-weight: bold; color: #333;");
    h_layout->addWidget(numberWidget);

    rollDice = new QPushButton("Roll Dice");
    rollDice->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    connect(rollDice, &QPushButton::clicked, this, &GameField::rollDiceButtonClicked);
    h_layout->addWidget(rollDice);

    for (int i = 0; i < 35; i++) {
        auto* rect = new CircleWidget;
        if (i == 0) {
            rect->setColor(Qt::white);
            rect->setNumber("Start");
            rect->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
        } else if (i == 34) {
            rect->setColor(Qt::white);
            rect->setNumber("Finish");
            rect->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
        } else {
            rect->setColor(colors[i % colors.size()]);
            rect->setNumber(QString::number(i + 1));
            rect->setStyleSheet("font-size: 18px; color: #333;");
        }
        m_layout->addWidget(rect, i / 7, i % 7);
    }

    currentPlayerLabel = new QLabel();
    currentPlayerLabel->setAlignment(Qt::AlignCenter);
    currentPlayerLabel->setStyleSheet("font-size: 24px; font-weight: bold; color: #333;");
    layout->addWidget(currentPlayerLabel, 1, 0);

    layout->addLayout(m_layout, 0, 0);
    layout->addLayout(h_layout, 0, 1);

    exitButton = new QPushButton("Exit");
    exitButton->setStyleSheet("background-color: #F44336; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    connect(exitButton, &QPushButton::clicked, this, &GameField::exitTriggered);
    h_layout->addWidget(exitButton);

    token1 = new Token(this, Qt::yellow);
    token2 = new Token(this, Qt::cyan);
    layout->addWidget(token1, 1, 2);
    layout->addWidget(token2, 1, 3);
    token1->setPosition(0);
    token2->setPosition(0);
    currentToken = token1;

    createMenu();

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &GameField::updateTokenPosition);
}

void GameField::paintEvent(QPaintEvent*) {
    QPainter painter(this);
    painter.fillRect(rect(), QColor(229, 229, 229));
}

void GameField::rollDiceButtonClicked() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);
    int diceRoll = dis(gen);

    numberWidget->setNumber(diceRoll);

    int newPosition = (currentToken->getPosition() + diceRoll) % m_layout->count();
    if (newPosition == m_layout->count() - 1 || diceRoll >= m_layout->count() - 1 - currentToken->getPosition()) {
        winner = currentToken;
        showWinnerMessage();
    } else {
        moveToken(currentToken, diceRoll);
        currentToken = (currentToken == token1) ? token2 : token1;
        currentPlayerLabel->setText(QString("Current player: %1").arg((currentToken == token1) ? m_player1Name : m_player2Name));
    }
}

void GameField::moveToken(Token* token, int steps) {
    int newPosition = (token->getPosition() + steps) % m_layout->count();
    CircleWidget* prevRect = qobject_cast<CircleWidget*>(m_layout->itemAt(token->getPosition())->widget());
    prevRect->setColor(colors[token->getPosition() % colors.size()]);

    token->setTargetPosition(newPosition);
    if (token->getPosition() < newPosition) {
        token->setDirection(Token::Direction::Forward);
    } else {
        token->setDirection(Token::Direction::Backward);
    }

    CircleWidget* currentRect = qobject_cast<CircleWidget*>(m_layout->itemAt(newPosition)->widget());
    if (currentRect->getColor() == Qt::red) {
        timer->start(700);
        token->setTargetPosition((newPosition + 3) % m_layout->count());
    } else if (currentRect->getColor() == Qt::gray) {
        timer->start(700);
        token->setTargetPosition((newPosition - 3) % m_layout->count());
    } else if (currentRect->getColor() == Qt::blue) {
        // Фишка попала на синий кружок
        // Добавляем один дополнительный код
        // Здесь нужно добавить дополнительную логику
    } else if (currentRect->getColor() == Qt::black) {
        // Фишка попала на черный кружок
        // Возвращаем фишку в начало
        timer->start(500);
        token->setTargetPosition(0);
    } else {
        timer->start(500);
    }
}

void GameField::updateTokenPosition() {
    if (currentToken->getPosition() != currentToken->getTargetPosition()) {
        int currentPosition = currentToken->getPosition();
        int targetPosition = currentToken->getTargetPosition();
        int step = (currentToken->getDirection() == Token::Direction::Forward) ? 1 : -1;
        currentToken->setPosition((currentPosition + step) % m_layout->count());
        CircleWidget* prevRect = qobject_cast<CircleWidget*>(m_layout->itemAt(currentPosition)->widget());
        prevRect->setColor(colors[currentPosition % colors.size()]);
        CircleWidget* newRect = qobject_cast<CircleWidget*>(m_layout->itemAt(currentToken->getPosition())->widget());
        newRect->setColor(currentToken->getColor());

        if ((currentToken->getDirection() == Token::Direction::Forward && currentToken->getPosition() >= targetPosition) ||
            (currentToken->getDirection() == Token::Direction::Backward && currentToken->getPosition() <= targetPosition)) {
            currentToken->setPosition(targetPosition);
            timer->stop();
        }
    } else {
        timer->stop();
    }
}

void GameField::showWinnerMessage() {
    QString winnerColor = (winner == token1) ? m_player1Name : m_player2Name;
    QMessageBox msgBox(this);
    msgBox.setWindowTitle("Game Over");
    msgBox.setText(QString("The %1 player won!").arg(winnerColor));
    msgBox.setStandardButtons(QMessageBox::Ok);
    int result = msgBox.exec();
    if (result == QMessageBox::Ok) {
        resetGame();
    }
}

void GameField::resetGame() {
    token1->setPosition(0);
    token2->setPosition(0);

    updateUI();

    winner = nullptr;
}

void GameField::createMenu(){
    menuBar = new QMenuBar(this);
    gameMenu = menuBar->addMenu("Game");

    newGameAction = new QAction("New Game", this);
    newGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    gameMenu->addAction(newGameAction);

    rulesAction = new QAction("Rules", this);
    rulesAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    gameMenu->addAction(rulesAction);

    aboutAction = new QAction("About", this);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    gameMenu->addAction(aboutAction);

    gameMenu->addSeparator();

    saveResultsAction = new QAction("Save Results", this);
    saveResultsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    gameMenu->addAction(saveResultsAction);

    exitAction = new QAction("Exit", this);
    exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    gameMenu->addAction(exitAction);

    connect(newGameAction, &QAction::triggered, this, &GameField::newGameTriggered);
    connect(rulesAction, &QAction::triggered, this, &GameField::rulesTriggered);
    connect(aboutAction, &QAction::triggered, this, &GameField::aboutTriggered);
    connect(saveResultsAction, &QAction::triggered, this, &GameField::saveResultsTriggered);
    connect(exitAction, &QAction::triggered, this, &GameField::exitTriggered);
}

void GameField::updateUI() {

    for (int i = 0; i < m_layout->count(); i++) {
        CircleWidget* rect = qobject_cast<CircleWidget*>(m_layout->itemAt(i)->widget());
        rect->setColor(colors[i % colors.size()]);
    }

    currentToken = token1;
    currentPlayerLabel->setText(QString("Current player: Yellow"));

    update();
}

void GameField::newGameTriggered() {
    resetGame();
}

void GameField::rulesTriggered() {
    QMessageBox::information(this, "Game Rules", "We have two colors: blue and light blue. They take turns moving around the playing field: yellow player comes first, and then blue player. Goal: reach the end of the field. When a chip lands on a red square, it moves 3 squares forward, on a gray one - 3 squares back, on a black one - to the beginning of the playing field, on a blue one - it makes an additional move.");
}

void GameField::aboutTriggered() {
    QMessageBox::information(this, "About Game", "The game was created as part of computing practice by students of the Faculty of Applied Mathematics and Informatics of BSU. Project Github: https://github.com/vitmark-06/Game4.git");
}

QString GameField::getPlayerNameByToken(Token* token) const {
    if (token == token1) {
        return m_player1Name;
    } else if (token == token2) {
        return m_player2Name;
    } else {
        return "Unknown";
    }
}

void GameField::saveResultsTriggered() {
    QFile file("game_results.txt");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);

        QString winnerName;
        if (winner != nullptr) {
            winnerName = getPlayerNameByToken(winner);
        } else {
            winnerName = "No Winner";
        }

        m_currentAttempt++;
        out << "Attempt #" << m_currentAttempt << " - Winner: " << winnerName << "\n";
        out << "Date: " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n\n";

        file.close();
        QMessageBox::information(this, "Results Saved", "Game results have been saved.");

        m_currentAttempt++;
    } else {
        QMessageBox::warning(this, "Error", "Unable to save game results.");
    }
}

int GameField::getCurrentAttempt() const {
    return m_currentAttempt;
}

QString GameField::getWinnerName() const {
    return winner != nullptr ? winner->getName() : "";
}

void GameField::exitTriggered() {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Exit Game", "Are you sure you want to exit the game?",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        QApplication::exit();
    }
}
