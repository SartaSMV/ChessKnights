#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QPainter>
#include <QSet>
#include <QGraphicsItem>

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Figure(QObject *parent = nullptr);
    virtual ~Figure();

    //! Устанавливает размер фигуры
    void setSizeSquare(int sizeSquare);
protected:
    //! Размер одной клетки поля
    int sizeSquare;

private:
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // FIGURE_H
