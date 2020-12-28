#include "prize.h"

Prize::Prize(int value, QObject *parent)
    : Figure(parent)
{
    this->value = value;
}

Prize::~Prize()
{

}

//! Устанавливает ценность приза
void Prize::setValue(int value)
{
    this->value = value;
}

//! Выводит ценность приза
int Prize::getValue()
{
    return this->value;
}

void Prize::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 2));
    painter->drawEllipse(QRectF(2, 2, sizeSquare-2, sizeSquare-2));

    painter->setPen(QPen(Qt::red, 2));
    painter->setFont(QFont("times",sizeSquare/2));
    painter->drawText(2, 2, sizeSquare - 2, sizeSquare - 2, Qt::AlignCenter, QString::number(value));

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
