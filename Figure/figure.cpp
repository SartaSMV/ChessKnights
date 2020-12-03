#include "figure.h"

Figure::Figure(int sizeSquare, QObject *parent)
    : QObject(parent), QGraphicsItem()
{
    this->sizeSquare = sizeSquare - 4;
}

Figure::~Figure()
{

}

QRectF Figure::boundingRect() const
{
    return QRectF(0,0,sizeSquare,sizeSquare);
}

void Figure::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(Qt::black);
    painter->drawEllipse(QRectF(0, 0, sizeSquare, sizeSquare));
        Q_UNUSED(option);
        Q_UNUSED(widget);
}
