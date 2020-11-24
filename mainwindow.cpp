#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    StartWindow start(this);
    start.exec();
    ui->setupUi(this);
    this->setWindowTitle("Chess Knights");
}

MainWindow::~MainWindow()
{
    delete ui;
}

