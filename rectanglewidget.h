#ifndef RECTANGLEWIDGET_H
#define RECTANGLEWIDGET_H

#include <QWidget>
#include <QPainter>

class RectangleWidget : public QWidget {
    Q_OBJECT

public:
    RectangleWidget(QWidget *parent = nullptr);
    QColor getColor() const;
    void setHalfColor(const QColor& color);
    void setColor(const QColor &color);
    void setNumber(int number);
    void setNumber(const QString &number);
    int getNumber() const;

    QColor m_color;
    QColor m_halfColor;
    QString m_number;

private:
    void paintEvent(QPaintEvent *) override;

};
#endif // RECTANGLEWIDGET_H
