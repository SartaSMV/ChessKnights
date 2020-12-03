#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ChessBoard/chessboard.h"

#include <QMainWindow>
#include <QTimer>

#include <StartWindow/startwindow.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr, bool *start = new bool(true));
    ~MainWindow();

public slots:
    void refresh();

    //! Загрузить сохраненную партию.
    bool loadGame();
    //! Сохранить текущую партию.
    bool saveGame();
    //! Выход из программы.
    void exit();

    //! Отображает таблицу рекордов.
    void ratingBoard();
    //! Вызывает окно с инструкцией.
    void help();

    //! Подсказка для выгодного хода.
    void hideForGame();
    //! Игра возврощается на ход назад.
    void undo();

    //! Стартуе и заканчивает игру.
    void startFinishGame();

private:
    Ui::MainWindow *ui;

    ChessBoard *mChessBoard;
    QTimer     *timer;
};
#endif // MAINWINDOW_H
