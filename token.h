#ifndef TOKEN_H
#define TOKEN_H

#include <QWidget>

class Token : public QWidget {
    Q_OBJECT

public:
    enum class Direction {
        Forward,
        Backward
    };

    Token(QWidget* parent, const QColor& color);
    void setPosition(int position);
    int getPosition() const;
    QColor getColor() const;
    QString getName() const;
    void setTargetPosition(int position);
    int getTargetPosition() const;
    void setDirection(Direction direction);
    Direction getDirection() const;

private:
    int currentPosition = 0;
    QColor color;
    QString m_name;
    int m_targetPosition;
    Direction m_direction;
};

#endif // TOKEN_H
