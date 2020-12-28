#include "chessplayer.h"

ChessPlayer::ChessPlayer()
{
    points = 0;
    mChessFigure = nullptr;
}

ChessPlayer::~ChessPlayer()
{

}

//! Задает имя игрока
void ChessPlayer::setName(QString name)
{
    this->name=name;
}

//! Выводит текущее имя игрока
QString ChessPlayer::getName()
{
    return this->name;
}

//! Задает фигуру игрока
void ChessPlayer::setChessFigure(ChessFigure *mChessFigure)
{
    this->mChessFigure = mChessFigure;
}

//! Выводит текущую фигуру
ChessFigure *ChessPlayer::getChessFigure()
{
    return this->mChessFigure;
}

//!Добовляет очки равные prize
void ChessPlayer::addPoints(int prize)
{
    this->points += prize;
}

//!Выводит колтчество очков prize
int ChessPlayer::getPoints()
{
    return this->points;
}

int ChessPlayer::getSteps()
{
    return this->steps;
}

//!Обнуляет очки prize
void ChessPlayer::refreshPoints()
{
    points = 0;
}

bool ChessPlayer::checkMove(QPointF *coords)
{
    return mChessFigure->checkMove(coords);
}

//! Сохраняет игрока в поток \a ost.
void ChessPlayer::save(QDataStream &ost) const
{
    ost << this->name << this->points << this->steps;
}

//! Загружает игрока из потока \a ist.
void ChessPlayer::load(QDataStream &ist)
{
    ist >> this->name >> this->points >> this->steps;
}
