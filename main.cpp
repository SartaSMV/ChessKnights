#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    bool start; MainWindow w(nullptr,&start);
    if(start)
    {
        w.show();
        return a.exec();
    }
    return 0;
}
