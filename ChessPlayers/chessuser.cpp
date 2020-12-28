#include "chessuser.h"

ChessUser::ChessUser()
{
    steps = 0;
}

ChessUser::~ChessUser()
{

}

bool ChessUser::checkMove(QPointF *coords)
{
    if(mChessFigure->checkMove(coords))
    {
        steps++;
        return true;
    }
    return false;
}
