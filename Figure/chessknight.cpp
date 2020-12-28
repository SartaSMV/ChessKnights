#include "chessknight.h"

ChessKnight::ChessKnight(QObject *parent)
    : ChessFigure(parent)
{
    iconeChessFigure.load(QString(":/Resourse/ChessFigure/ChessKnight.svg"));
}

ChessKnight::~ChessKnight()
{

}

//! Проверят возможност хода на координаты \a coords.
bool ChessKnight::checkMove(QPointF *coords) const
{
    int x1 = coords->x() / (sizeSquare + 5); int y1 = coords->y() / (sizeSquare + 5);
    return trueMove.contains(QPair<int, int> (x1, y1));
}

void ChessKnight::setPose(int x, int y, int countSquare, int x_enemy, int y_enemy)
{
    trueMove.clear();
    int x1, y1;
    int move_x[8] = {2, 1, -1, -2, -2, -1, 1, 2}; int move_y[8] = {1, 2, 2, 1, -1, -2, -2, -1};

    for(int i = 0; i < 8; i++)
    {
        x1 = x / (sizeSquare + 5) + move_x[i];
        y1 = y / (sizeSquare + 5) + move_y[i];
        if(x1 < 0 || y1 < 0 || x1 > countSquare - 1 || y1 > countSquare - 1) continue;
        trueMove.insert(QPair<int, int> (x1, y1));
    }
    this->setPos(x, y);
    Q_UNUSED(x_enemy);
    Q_UNUSED(y_enemy);
}

void ChessKnight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(mPenPlayer);
    painter->drawRect(QRectF(0,0,sizeSquare,sizeSquare));
    iconeChessFigure.setFixedSize(sizeSquare, sizeSquare);
    iconeChessFigure.render(painter);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
