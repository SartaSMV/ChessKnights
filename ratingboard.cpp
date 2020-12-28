#include "ratingboard.h"
#include "ui_ratingboard.h"

RatingBoard::RatingBoard(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RatingBoard)
{
    ui->setupUi(this);
    table = new QStandardItemModel(this);
    ui->tableView->setModel(table);
}

RatingBoard::~RatingBoard()
{
    delete ui;
}

/*!
 * \brief Функция заполнения таблицы рекордов
 */
void RatingBoard::fillTable()
{
    this->sortUser();

    table->setColumnCount(3);
    table->setRowCount(usersToShow.size());
    QModelIndex index;
    QStringList collsName = {"User names", "Points", "Steps"};
    table->setHorizontalHeaderLabels(collsName);
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    for (int row = 0; row < table->rowCount(); row++) {
        index = table->index(row, 0);
        table->setData(index, usersToShow[row].getName());
        index = table->index(row, 1);
        table->setData(index, usersToShow[row].getPoints());
        index = table->index(row, 2);
        table->setData(index, usersToShow[row].getSteps());
        ui->tableView->verticalHeader()->setSectionResizeMode(row, QHeaderView::Stretch);
    }
}

/*!
 * \brief Функция добавления пользователя по возможности
 */
void RatingBoard::pushNewUsers(ChessPlayer user)
{
    usersToShow.push_back(user);
    this->sortUser();
    if(usersToShow.size() == 11) usersToShow.pop_back();
}

//! Установка размера поля
void RatingBoard::setSizeBoard(int sizeBoard)
{
    this->sizeBoard = sizeBoard;
}

//! Сохраняет таблицу в поток \a ost.
void RatingBoard::save()
{
    QDir dir;
    if(!dir.exists("Rating")) dir.mkdir("Rating");
    QFile file("Rating/rating"+QString::number(sizeBoard));
    if(file.open(QIODevice::WriteOnly))
    {
        QDataStream ist(&file);
        int len = usersToShow.size();
        ist << len;
        for(auto i:usersToShow ) ist << i;
        file.close();
    }
}

//! Загружает таблицу из потока \a ist.
void RatingBoard::load()
{
    usersToShow.clear();
    QFile file("Rating/rating"+QString::number(sizeBoard));
    if(file.open(QIODevice::ReadOnly))
    {
        QDataStream ost(&file);
        if(ost.atEnd())
        {
            file.close();
            return;
        }
        else
        {
            ChessPlayer user; int len;
            ost >> len;
            while(len--)
            {
                ost >> user;
                usersToShow.push_back(user);
            }
        }
        file.close();
    }
}

//! Сортитрует таблицу рекордов
void RatingBoard::sortUser()
{
    for(int i = 0; i < usersToShow.size(); i++)
    {
        for(int j = i + 1; j < usersToShow.size(); j++)
        {
            if(usersToShow[j].getPoints() > usersToShow[i].getPoints()) usersToShow.swapItemsAt(i, j);
            else if(usersToShow[j].getPoints() == usersToShow[i].getPoints())
            {
                if(usersToShow[j].getSteps() > usersToShow[i].getSteps()) usersToShow.swapItemsAt(i, j);
            }
        }
    }
}
