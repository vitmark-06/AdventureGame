#include "token.h"

Token::Token(QWidget *parent, const QColor &color): QWidget(parent) {
    setFixedSize(20, 20);
    setStyleSheet(QString("background-color: %1; border-radius: 10px;").arg(color.name()));
    this->color = color;
}

void Token::setPosition(int position) {
    currentPosition = position;
}

int Token::getPosition() const{
    return currentPosition;
}

QColor Token::getColor() const {
    return color;
}

QString Token::getName() const{
    return m_name;
}
