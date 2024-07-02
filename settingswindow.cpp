#include "settingswindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

SettingsWindow::SettingsWindow(QWidget* parent) : QDialog(parent)
{
    setWindowTitle("Game Settings");
    setStyleSheet("background-color: #E5E5E5;");
    resize(600, 400);

    auto* mainLayout = new QGridLayout(this);
    mainLayout->setSpacing(30);
    mainLayout->setContentsMargins(50, 50, 50, 50);

    auto* titleLabel = new QLabel("Game Settings");
    titleLabel->setStyleSheet("font-size: 28px; font-weight: bold; color: #333;");
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

    m_saveButton = new QPushButton("Save");
    m_saveButton->setStyleSheet("background-color: #4CAF50; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(m_saveButton, 3, 0, Qt::AlignCenter);
    connect(m_saveButton, &QPushButton::clicked, this, &SettingsWindow::saveSettings);

    m_cancelButton = new QPushButton("Cancel");
    m_cancelButton->setStyleSheet("background-color: #F44336; color: white; font-size: 18px; padding: 15px 30px; border-radius: 5px;");
    mainLayout->addWidget(m_cancelButton, 3, 1, Qt::AlignCenter);
    connect(m_cancelButton, &QPushButton::clicked, this, &SettingsWindow::reject);

    auto* screen = QGuiApplication::screens().first();
    QRect screenGeometry = screen->geometry();
    int x = (screenGeometry.width() - width()) / 2;
    int y = (screenGeometry.height() - height()) / 2;
    move(x, y);
}

void SettingsWindow::setPlayer1Name(const QString& name)
{
    m_player1NameEdit->setText(name);
}

void SettingsWindow::setPlayer2Name(const QString& name)
{
    m_player2NameEdit->setText(name);
}

QString SettingsWindow::getPlayer1Name() const
{
    return m_player1NameEdit->text();
}

QString SettingsWindow::getPlayer2Name() const
{
    return m_player2NameEdit->text();
}

void SettingsWindow::saveSettings()
{
    emit settingsSaved(getPlayer1Name(), getPlayer2Name());
    accept();
}
