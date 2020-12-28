#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ChessBoard/chessboard.h"
#include "ratingboard.h"

#include <QMainWindow>
#include <QMessageBox>
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
    //! Обновляет экран через установленное значения
    void refresh();
    //! Обновляет экран после изменения количества очков
    void refreshPoints(int points, int movePlayer);
    //! Конец игры
    void finishGame(ChessPlayer *ChessPlayers[2]);

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

    //! Стартует и заканчивает игру.
    void startFinishGame();
    //! Слот настройки меню игры на старт и финишь
    void game(bool game);
    //! Слот смены врага
    void swapEnemy(int enemy);

signals:
    //! Сигнал настройки меню игры на старт и финишь
    void gameMenu(bool game);

private:
    /*!
     * \brief Указатель на сгенерированный интерфейс.
     *
     * Указатель на объект UI-класса, сгенерированного на основе UI-файла
     * mainwindow.ui.
     *
     * Через этот указатель можно обратиться к элементам главного окна,
     * созданного в Qt Designer.
     * \sa \ref faq_qt_designer_whatis
     */
    Ui::MainWindow *ui;

    //!Сылка на доску, которую надо показывать
    ChessBoard *mChessBoard;
    //! Таймер для обновления размера экрана
    QTimer     timer;
    //! Обозначения кто враг
    int enemy = 0;
    //! Таблица рекордов
    RatingBoard *mRatingboard;
};
#endif // MAINWINDOW_H
