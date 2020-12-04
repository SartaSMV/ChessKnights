#ifndef CHESSFIGURE_H
#define CHESSFIGURE_H

#include "figure.h"

class ChessFigure : public Figure
{
    Q_OBJECT
public:
    explicit ChessFigure(int sizeSquare, QObject *parent = nullptr);
    ~ChessFigure();

    virtual bool moveFigure(int coords) = 0;
private:
    virtual bool checkMove(int coords) const = 0;
};

#endif // CHESSFIGURE_H
