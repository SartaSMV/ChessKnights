#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    void exit();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
