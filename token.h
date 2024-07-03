#ifndef TOKEN_H
#define TOKEN_H

#include <QWidget>

class Token : public QWidget {
    Q_OBJECT

public:
    enum class Direction { Forward, Backward };
    Token(QWidget* parent, const QColor& color);
    void setPosition(int position);
    int getPosition() const;
    QColor getColor() const;
    QString getName() const;

    void setTargetPosition(int position) {
        m_targetPosition = position;
    }

    int getTargetPosition() const {
        return m_targetPosition;
    }

    void setDirection(Direction direction) {
        m_direction = direction;
    }

    Direction getDirection() const {
        return m_direction;
    }

private:
    int currentPosition = 0;
    QColor color;
    QString m_name;
    int m_targetPosition;
    Direction m_direction;
};

#endif // TOKEN_H
