#ifndef RATINGBOARD_H
#define RATINGBOARD_H

#include <QWidget>
#include "ChessPlayers/chessplayer.h"
#include <QStandardItemModel>
#include <QDataStream>
#include <QDir>

namespace Ui {
class RatingBoard;
}

class RatingBoard : public QWidget
{
    Q_OBJECT

public:
    explicit RatingBoard(QWidget *parent = nullptr);
    ~RatingBoard();

    /*!
     * \brief Функция заполнения таблицы рекордов
     */
    void fillTable();

    /*!
     * \brief Функция добавления пользователя по возможности
     */
    void pushNewUsers(ChessPlayer user);
    //! Установка размера поля
    void setSizeBoard(int sizeBoard);

    //! Сохраняет таблицу в поток \a ost.
    void save();
    //! Загружает таблицу из потока \a ist.
    void load();
private:
    //! Сортитрует таблицу рекордов
    void sortUser();

    //! Указатель на список рекордсменнов
    QList<ChessPlayer> usersToShow;

    //! Элементы для вывода на QTableView
    QStandardItemModel *table;
    //! Размер поля
    int sizeBoard;
    Ui::RatingBoard *ui;
};

#endif // RATINGBOARD_H
