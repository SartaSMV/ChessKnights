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
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::exit()
{
   QApplication::instance()->quit();
}
