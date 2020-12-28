#include "chessfigure.h"

ChessFigure::ChessFigure(QObject *parent)
    : Figure(parent)
{

}

ChessFigure::~ChessFigure()
{

}

//! Задает обводку игрока.
void ChessFigure::setPenPlayer(QPen penPlayer)
{
    this->mPenPlayer = penPlayer;
}

//! Возврощает обводку игрока.
QPen ChessFigure::getPenPlayer()
{
    return this->mPenPlayer;
}

//! Выводит возможные позиции.
QSet <QPair<int, int>> ChessFigure::getTrueMove()
{
    return trueMove;
}
