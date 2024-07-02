#include "rectanglewidget.h"

RectangleWidget::RectangleWidget(QWidget *parent): QWidget(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("background-color: transparent;");
}

QColor RectangleWidget::getColor() const{
    return m_color;
}

void RectangleWidget::setHalfColor(const QColor &color){
    m_halfColor = color;
    update();
}

void RectangleWidget::setColor(const QColor &color) {
    m_color = color;
    update();
}
void RectangleWidget::setNumber(int number){
    m_number = QString::number(number);
    update();
}

void RectangleWidget::setNumber(const QString &number){
    m_number = number;
    update();
}

int RectangleWidget::getNumber() const
{
    return m_number.toInt();
}

void RectangleWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.fillRect(rect().adjusted(-20, 10, -10, -10), m_color);

    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, m_number);
}

