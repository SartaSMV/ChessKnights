#ifndef CHESSKNIGHT_H
#define CHESSKNIGHT_H

#include "chessfigure.h"

class ChessKnight : public ChessFigure
{
    Q_OBJECT
public:
    explicit ChessKnight(QObject *parent = nullptr);
    ~ChessKnight();

    //! Проверят возможность хода на координаты \a coords.
    bool checkMove(QPointF *coords) const Q_DECL_OVERRIDE;
    //! Устанавливает фигуру на место.
    void setPose(int x, int y, int countSquare, int x_enemy = 0, int y_enemy = 0) Q_DECL_OVERRIDE;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // CHESSKNIGHT_H
