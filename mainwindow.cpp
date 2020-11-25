#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, bool *start)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Chess Knights");

    // Вводимые данные до запуска окна
    QString playerName; int enemy;
    StartWindow startW(this, &playerName, &enemy);
    //Игрок решил не играть
    if (startW.exec() != StartWindow::Accepted) *start = false;
    else *start = true;

    int countSquare = 24;
    int sizeSquare = 20;
    mChessBoard = new ChessBoard(this);
    ui->graphicsView_chessboard->setScene(mChessBoard);
    ui->graphicsView_chessboard->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_chessboard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_chessboard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    mChessBoard->setSizeBoard(countSquare, sizeSquare);
    //ui->graphicsView_chessboard->setFixedSize((sizeSquare+1)*countSquare + 2, (sizeSquare+1)*countSquare + 2);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
   QApplication::instance()->quit();
}
