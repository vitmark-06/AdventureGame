#include "numberwidget.h"

NumberWidget::NumberWidget(QWidget *parent): QLabel(parent) {
    setAlignment(Qt::AlignCenter);
    setStyleSheet("font-size: 24px; font-weight: bold;");
}

void NumberWidget::setNumber(int number) {
    setText(QString::number(number));
}
