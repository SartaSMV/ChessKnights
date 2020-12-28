#include "chessbot.h"

ChessBot::ChessBot()
{

}

ChessBot::~ChessBot()
{

}

bool ChessBot::checkMove(QPointF *coords)
{
    QSet <QPair<int, int>> move = mChessFigure->getTrueMove();
    int iter = QRandomGenerator::global()->bounded(move.size());
    for(auto i:move)
    {
        if(iter == 0)
        {
            *coords = QPointF(i.first, i.second);
            break;
        }
        iter--;
    }
    return true;
}
