#include "figure.h"

Figure::Figure(QObject *parent)
    : QObject(parent), QGraphicsItem()
{

}

Figure::~Figure()
{

}

//!Устанавливает размер фигуры
void Figure::setSizeSquare(int sizeSquare)
{
    this->sizeSquare = sizeSquare - 4;
}

QRectF Figure::boundingRect() const
{
    return QRectF(0,0,sizeSquare,sizeSquare);
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(2, 2, sizeSquare, sizeSquare));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
