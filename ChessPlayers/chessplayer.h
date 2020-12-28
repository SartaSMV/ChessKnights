#ifndef CHESSPLAYER_H
#define CHESSPLAYER_H

#include "Figure/chessfigure.h"

#include <QString>

class ChessPlayer
{

public:
    ChessPlayer();
    virtual ~ChessPlayer();

    //! Задает имя игрока
    void setName(QString name);
    //! Выводит текущее имя игрока
    QString getName();
    //! Задает фигуру игрока
    void setChessFigure(ChessFigure *mChessFigure);
    //! Выводит текущую фигуру
    ChessFigure *getChessFigure();

    //!Добовляет очки равные prize
    void addPoints(int prize);
    //!Выводит колтчество очков prize
    int getPoints();
    //!Выводит колтчество ходов steps
    int getSteps();
    //!Обнуляет очки prize
    void refreshPoints();

    //! По возможность хода
    virtual bool checkMove(QPointF *coords = new QPointF(0, 0));

    //! Сохраняет игрока в поток \a ost.
    void save(QDataStream &ost) const;
    //! Загружает игрока из потока \a ist.
    void load(QDataStream &ist);
private:
    //! Имя игрока
    QString name;
    //! Собранные очки
    int points;

protected:
    //! Фигура игрока
    ChessFigure *mChessFigure;
    //! Шаги игрока
    int steps;
};

/*!
 * \brief Реализация оператора << для вывода Note в QDataStream.
 * \param ost Поток для вывода.
 * \param note Заметка.
 * \return Поток \a ost после вывода.
 *
 * Данная функция объявлена \c inline, чтобы компилятор мог подставить её код
 * вместо полноценного вызова функции. В данном случае это оправданно, так как
 * функция всего лишь перенаправляет вызов методу save().
 */
inline QDataStream &operator<<(QDataStream &ost, const ChessPlayer &player)
{
    player.save(ost);
    return ost;
}

/*!
 * \brief Реализация оператора >> для ввода Note из QDataStream.
 * \param ist Поток для ввода.
 * \param note Заметка.
 * \return Поток \a ist после ввода.
 */
inline QDataStream &operator>>(QDataStream &ist, ChessPlayer &player)
{
    player.load(ist);
    return ist;
}

#endif // CHESSPLAYER_H
