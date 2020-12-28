#ifndef PRIZE_H
#define PRIZE_H

#include "figure.h"

class Prize : public Figure
{
    Q_OBJECT
public:
    explicit Prize(int value, QObject *parent = nullptr);
    ~Prize();

    //! Устанавливает ценность приза
    void setValue(int value);
    //! Выводит ценность приза
    int getValue();

private:
    //! Ценность приза
    int value;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // PRIZE_H
