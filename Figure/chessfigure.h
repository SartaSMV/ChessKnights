#ifndef CHESSFIGURE_H
#define CHESSFIGURE_H

#include "figure.h"

#include <QtSvg/QtSvg>
#include <QPointF>

class ChessFigure : public Figure
{
    Q_OBJECT
public:
    explicit ChessFigure(QObject *parent = nullptr);
    virtual ~ChessFigure();

    /*//! Перемещает фигуру на координаты \a coords по возможности Возвращает \c true в случае успеха.
    virtual bool moveFigure(QPointF *coords) = 0;*/
    //! Задает обводку игрока.
    void setPenPlayer(QPen penPlayer);
    //! Возврощает обводку игрока.
    QPen getPenPlayer();
    //! Выводит возможные позиции.
    QSet <QPair<int, int>> getTrueMove();

    //! Проверят возможност хода на координаты \a coords.
    virtual bool checkMove(QPointF *coords) const = 0;
    //! Устанавливает фигуру на место.
    virtual void setPose(int x, int y, int countSquare, int x_enemy = 0, int y_enemy = 0) = 0;

protected:
    //! Обводка игрока \a coords.
    QPen mPenPlayer = QPen(Qt::black, 3);
    //! Куда может пойти фигура
    QSet <QPair<int, int>> trueMove;
    //! Иконка для фигуры
    QSvgWidget iconeChessFigure;
};

#endif // CHESSFIGURE_H
