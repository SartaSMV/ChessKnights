#include "chessboard.h"

ChessBoard::ChessBoard(QObject *parent) : QGraphicsScene(parent)
{
}

ChessBoard::~ChessBoard()
{

}

void ChessBoard::setSizeBoard(int countSquare, int sizeSquare)
{
    this->countSquare = countSquare;
    this->sizeSquare = sizeSquare;
    this->sizeBoard = (sizeSquare+1)*countSquare;
    this->setSceneRect(QRect(0,0,sizeBoard,sizeBoard));
    for(int i = -1; i <= sizeBoard; i+=sizeSquare)
    {
        i++;
        addLine(i,0,i,sizeBoard,QPen(Qt::green));
        addLine(0,i,sizeBoard,i,QPen(Qt::green));
    }
}

#include <QDebug>

void ChessBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{   
    int x = event->scenePos().x() / (sizeSquare + 1);
    int y = event->scenePos().y() / (sizeSquare + 1);
    x = x * (sizeSquare + 1);
    y = y * (sizeSquare + 1);

    addEllipse(    x + 2,
                   y + 2,
                   sizeSquare - 4,
                   sizeSquare - 4,
                   QPen(Qt::NoPen),
                   QBrush(Qt::red));
}
