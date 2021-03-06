#include "chessrook.h"

ChessRook::ChessRook(QObject *parent)
    : ChessFigure(parent)
{
    iconeChessFigure.load(QString(":/Resourse/ChessFigure/ChessRook.svg"));
}

ChessRook::~ChessRook()
{

}

//! Проверят возможност хода на координаты \a coords.
bool ChessRook::checkMove(QPointF *coords) const
{
    int x1 = coords->x() / (sizeSquare + 5); int y1 = coords->y() / (sizeSquare + 5);
    return trueMove.contains(QPair<int, int> (x1, y1));
}

void ChessRook::setPose(int x, int y, int countSquare, int x_enemy, int y_enemy )
{
    trueMove.clear();
    int x1, y1;
    int x2 = x_enemy / (sizeSquare + 5), y2 = y_enemy / (sizeSquare + 5);

    x1 = x / (sizeSquare + 5);
    y1 = y / (sizeSquare + 5);
    bool ok = !(x1 == x2 && y1 == y2);
    while(1)
    {
        x1++;
        if(x1 < 0 || x1 > countSquare - 1) break;
        if(ok && x1 - 1 == x2 && y1 == y2) break;
        trueMove.insert(QPair<int, int> (x1, y1));
    }

    x1 = x / (sizeSquare + 5);
    y1 = y / (sizeSquare + 5);
    while(1)
    {
        x1--;
        if(x1 < 0 || x1 > countSquare - 1) break;
        if(ok && x1 + 1 == x2 && y1  == y2) break;
        trueMove.insert(QPair<int, int> (x1, y1));
    }

    x1 = x / (sizeSquare + 5);
    y1 = y / (sizeSquare + 5);
    while(1)
    {
        y1++;
        if(y1 < 0 || y1 > countSquare - 1) break;
        if(ok && x1 == x2 && y1 - 1 == y2) break;
        trueMove.insert(QPair<int, int> (x1, y1));
    }

    x1 = x / (sizeSquare + 5);
    y1 = y / (sizeSquare + 5);
    while(1)
    {
        y1--;
        if(y1 < 0 || y1 > countSquare - 1) break;
        if(ok && x1 == x2 && y1 + 1 == y2) break;
        trueMove.insert(QPair<int, int> (x1, y1));
    }


    this->setPos(x, y);
}

void ChessRook::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(mPenPlayer);
    painter->drawRect(QRectF(0,0,sizeSquare,sizeSquare));
    iconeChessFigure.setFixedSize(sizeSquare, sizeSquare);
    iconeChessFigure.render(painter);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
