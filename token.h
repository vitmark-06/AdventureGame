#ifndef TOKEN_H
#define TOKEN_H

#include <QWidget>

class Token : public QWidget {
    Q_OBJECT

public:
    Token(QWidget* parent, const QColor& color);
    void setPosition(int position);
    int getPosition() const;
    QColor getColor() const;
    QString getName() const;

private:
    int currentPosition = 0;
    QColor color;
    QString m_name;
};

#endif // TOKEN_H
