#ifndef CHESSBOT_H
#define CHESSBOT_H

#include "chessplayer.h"
#include <QRandomGenerator>

class ChessBot : public ChessPlayer
{
public:
    explicit ChessBot();
    ~ChessBot();

    //! По возможности передвигает игрока
    bool checkMove(QPointF *coords) Q_DECL_OVERRIDE;
};

#endif // CHESSBOT_H
