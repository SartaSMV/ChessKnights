#ifndef PRIZE_H
#define PRIZE_H

#include "figure.h"

class Prize : public Figure
{
    Q_OBJECT
public:
    explicit Prize(int value,int sizeSquare, QObject *parent = nullptr);
    ~Prize();

    void setValue(int value);
    int getValue();

private:
    int value;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // PRIZE_H
