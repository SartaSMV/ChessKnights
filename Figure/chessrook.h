#ifndef CHESSROOK_H
#define CHESSROOK_H

#include "chessfigure.h"

class ChessRook : public ChessFigure
{
    Q_OBJECT
public:
    explicit ChessRook(QObject *parent = nullptr);
    ~ChessRook();

    //! Проверят возможност хода на координаты \a coords.
    bool checkMove(QPointF *coords) const Q_DECL_OVERRIDE;
    //! Устанавливает фигуру на место.
    void setPose(int x, int y, int countSquare, int x_enemy = 0, int y_enemy = 0) Q_DECL_OVERRIDE;

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // CHESSROOK_H
