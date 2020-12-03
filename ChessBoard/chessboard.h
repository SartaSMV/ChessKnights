#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Figure/figure.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QTimer>

class ChessBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ChessBoard(QObject *parent = nullptr);
    ~ChessBoard();

    void setSizeBoard(int countSquare, int sizeSquare);
private:
    int countSquare;
    int sizeSquare;
    int sizeBoard;
    int points[25][25];

    void mousePressEvent(QGraphicsSceneMouseEvent * event) Q_DECL_OVERRIDE;
};

#endif // CHESSBOARD_H
