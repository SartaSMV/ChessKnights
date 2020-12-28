#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include "Figure/prize.h"
#include "Figure/chessknight.h"
#include "Figure/chessbishop.h"
#include "Figure/chessrook.h"
#include "ChessPlayers/chessuser.h"
#include "ChessPlayers/chessbot.h"

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItemGroup>
#include <QTimer>
#include <QVector>
#include <QRandomGenerator>

class ChessBoard : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit ChessBoard(QObject *parent = nullptr);
    ~ChessBoard();

    //! Стартует игру с настройками
    void startGame(int countSquare = 24, int sizeSquare = 100, int figure = 0, int enemy = 0);
    //! Устанавливает новое значение размера и обновляет элементы под него
    void setSizeBoard(int countSquare, int sizeSquare);
    //! Возврощает на 1 ход назад.
    void undoStep();
    //! Меняет занчение подсказки
    void hideForGame();
    //! Сохраняет игрока в поток \a ost.
    void save(QDataStream &ost) const;
    //! Загружает игрока из потока \a ist.
    void load(QDataStream &ist);
private:
    //! Ссылки на игроков
    ChessPlayer* ChessPlayers[2];
    //! Чей сейчас ход
    int movePlayer = 0;

    //! Количество квадратов на 1 стороне
    int countSquare;
    //! Размер стороны квадрата
    int sizeSquare;
    //! Размер стороны всей доски
    int sizeBoard;
    //! Количество призов на всей доске
    int count_prizes;
    //! Обозначает врага
    int enemy;
    //! Какой фигурой идет игра
    int figure;
    //! Подсказка для игры
    bool hide = false;

    //! Линии доски
    QGraphicsLineItem **lines;
    //! Обводки ходов
    QVector <QGraphicsRectItem*> rects;
    //! Игровое поле
    QVector< QVector <int> > points;
    //! Призы на поле
    QVector< QVector <Prize*> > prizes;
    //! Ходы игры
    QVector< QPair< QVector< QVector<int> >, int> > steps;

    //! Добавляет ход в память.
    void addStep();

    void mousePressEvent(QGraphicsSceneMouseEvent * event) Q_DECL_OVERRIDE;

signals:
    //! Сообщает о изменении количества очков
    void refreshPoints(int points, int movePlayer);
    //! Сообщает о конце игры
    void finishGame(ChessPlayer *ChessPlayers[2]);
    //! Сигнал о смене врага
    void swapEnemy(int enemy);
};

#endif // CHESSBOARD_H
