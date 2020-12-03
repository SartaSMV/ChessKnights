#include "chessboard.h"

ChessBoard::ChessBoard(QObject *parent) : QGraphicsScene(parent)
{
    for(int i = 0; i < 24; i++)
    {
       for(int j = 0; j < 24; j++)
       {
           points[i][j] = 0;
       }
    }
}

ChessBoard::~ChessBoard()
{

}

void ChessBoard::setSizeBoard(int countSquare, int sizeSquare)
{
    this->clear();
    this->countSquare = countSquare;
    this->sizeSquare = sizeSquare;
    this->sizeBoard = (sizeSquare+1)*countSquare;
    this->setSceneRect(QRect(0,0,sizeBoard,sizeBoard));
    for(int i = -1; i <= sizeBoard; i+=sizeSquare)
    {
        i++;
        addLine(i,0,i,sizeBoard,QPen(Qt::black));
        addLine(0,i,sizeBoard,i,QPen(Qt::black));
    }

    Figure *a;
    for(int i = 0; i < countSquare; i++)
    {
       for(int j = 0; j < countSquare; j++)
       {
           if (points[i][j])
           {
               a = new Figure(sizeSquare, this);
               a->setPos(i * (sizeSquare + 1) + 2, j * (sizeSquare + 1) + 2);
               this->addItem(a);
           }
       }
    }
}

void ChessBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x() / (sizeSquare + 1);
    int y = event->scenePos().y() / (sizeSquare + 1);
    if(x < 0 || y < 0 || x > countSquare - 1 || y > countSquare - 1 || event->scenePos().x() < 0 || event->scenePos().y() < 0) return;
    if (points[x][y]) points[x][y] = 0;
    else points[x][y] = 1;
}
