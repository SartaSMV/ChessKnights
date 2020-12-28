#ifndef CHESSUSER_H
#define CHESSUSER_H

#include "chessplayer.h"

class ChessUser : public ChessPlayer
{
public:
    explicit ChessUser();
    ~ChessUser();

    //! По возможности передвигает игрока
    bool checkMove(QPointF *coords) Q_DECL_OVERRIDE;
};

#endif // CHESSUSER_H
