#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QGuiApplication>
#include <QScreen>

class QLabel;
class QLineEdit;
class QPushButton;

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    SettingsWindow(QWidget* parent = nullptr);

    void setPlayer1Name(const QString& name);
    void setPlayer2Name(const QString& name);

    QString getPlayer1Name() const;
    QString getPlayer2Name() const;

signals:
    void settingsSaved(const QString& player1Name, const QString& player2Name);

private slots:
    void saveSettings();

private:
    QLabel* m_player1NameLabel;
    QLineEdit* m_player1NameEdit;
    QLabel* m_player2NameLabel;
    QLineEdit* m_player2NameEdit;
    QPushButton* m_saveButton;
    QPushButton* m_cancelButton;
};

#endif // SETTINGSWINDOW_H
