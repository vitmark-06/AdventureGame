#ifndef CIRCLEWIDGET_H
#define CIRCLEWIDGET_H

#include <QWidget>
#include <QPainter>

class CircleWidget : public QWidget {
    Q_OBJECT

public:
    CircleWidget(QWidget *parent = nullptr);

    QColor getColor() const;
    void setHalfColor(const QColor &color);
    void setColor(const QColor &color);
    void setNumber(int number);
    void setNumber(const QString &number);
    int getNumber() const;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QColor m_color;
    QColor m_halfColor;
    QString m_number;
};

#endif // CIRCLEWIDGET_H
