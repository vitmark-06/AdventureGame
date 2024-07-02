#ifndef NUMBERWIDGET_H
#define NUMBERWIDGET_H

#include <QObject>
#include <QLabel>

class NumberWidget : public QLabel {
    Q_OBJECT

public:
    NumberWidget(QWidget* parent = nullptr);
    void setNumber(int number);
};

#endif // NUMBERWIDGET_H
