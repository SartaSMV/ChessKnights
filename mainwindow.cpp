#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, bool *start)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Chess Knights");

    /*// Вводимые данные до запуска окна
    QString playerName; int enemy;
    StartWindow startW(this, &playerName, &enemy);
    //Игрок решил не играть
    if (startW.exec() != StartWindow::Accepted) *start = false;
    else *start = true;*/
    *start = true;

    ui->graphicsView_chessboard->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_chessboard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_chessboard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer = new QTimer();
    timer->setSingleShot(true);
    connect(timer, &QTimer::timeout, this, &MainWindow::refresh);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh()
{
    int countSquare = (ui->comboBox_Field_Size->currentIndex()+1)*8;
    timer->stop();
    int width = ui->graphicsView_chessboard->width();
    int height = ui->graphicsView_chessboard->height();
    int sizeSquare = (height > width) ? (width) : (height);
    sizeSquare = sizeSquare / (countSquare) - 2;
    mChessBoard->setSizeBoard(countSquare, sizeSquare);
    timer->start(50);
}

//! Загрузить сохраненную партию.
bool MainWindow::loadGame()
{
    QApplication::instance()->quit();
    return true;
}

//! Сохранить текущую партию.
bool MainWindow::saveGame()
{
    QApplication::instance()->quit();
    return true;
}

//! Выход из программы.
void MainWindow::exit()
{
   QApplication::instance()->quit();
}

//! Отображает таблицу рекордов.
void MainWindow::ratingBoard()
{
    QApplication::instance()->quit();
}

//! Вызывает окно с инструкцией.
void MainWindow::help()
{
    QApplication::instance()->quit();
}

//! Вызывает окно с инструкцией.
void MainWindow::hideForGame()
{
    QApplication::instance()->quit();
}

//! Вызывает окно с инструкцией.
void MainWindow::undo()
{
    QApplication::instance()->quit();
}

//! Стартуе и заканчивает игру.
void MainWindow::startFinishGame()
{
    if(ui->pushButton_Start_Finish->text() == "Start")
    {
        mChessBoard = new ChessBoard(this);
        ui->graphicsView_chessboard->setScene(mChessBoard);
        timer->start(50);
        ui->pushButton_Start_Finish->setText("Finish");
    }
    else
    {
        timer->stop();
        mChessBoard->clear();
        delete mChessBoard;
        ui->pushButton_Start_Finish->setText("Start");
    }
}
