#include "circlewidget.h"

CircleWidget::CircleWidget(QWidget *parent): QWidget(parent) {
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    setStyleSheet("background-color: transparent;");
}

QColor CircleWidget::getColor() const {
    return m_color;
}

void CircleWidget::setHalfColor(const QColor &color) {
    m_halfColor = color;
    update();
}

void CircleWidget::setColor(const QColor &color) {
    m_color = color;
    update();
}
void CircleWidget::setNumber(int number){
    m_number = QString::number(number);
    update();
}

void CircleWidget::setNumber(const QString &number) {
    m_number = number;
    update();
}

int CircleWidget::getNumber() const {
    return m_number.toInt();
}

void CircleWidget::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int diameter = qMin(width(), height()) - 20;
    painter.setBrush(m_color);
    painter.drawEllipse(QRect(width() / 2 - diameter / 2, height() / 2 - diameter / 2, diameter, diameter));

    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, m_number);
}
