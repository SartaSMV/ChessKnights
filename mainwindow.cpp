#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Вводимые данные до запуска окна
    QString playerName; int enemy;
    StartWindow start(this, &playerName, &enemy);
    start.exec();
    ui->setupUi(this);
    this->setWindowTitle("Chess Knights");
}

MainWindow::~MainWindow()
{
    delete ui;
}
