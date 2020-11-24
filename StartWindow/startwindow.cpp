#include "startwindow.h"
#include "ui_startwindow.h"

StartWindow::StartWindow(QWidget *parent, QString* name, int *enemy)
    : QDialog(parent)
    , ui(new Ui::StartWindow)
{
    this->name = name;
    this->enemy = enemy;

    ui->setupUi(this);
    this->setWindowTitle("Start window");
    emit this->ui->comboBox_Enemy->currentIndexChanged(0);
}

StartWindow::~StartWindow()
{
    delete ui;
}

//! Обновляет значение имени игрока при изменении
void StartWindow::setName(QString name)
{
    *this->name = name;
}

//! Обновляет значение противника игрока при изменении
void StartWindow::setEnemy(int enemy)
{
    *this->enemy = enemy;
    if(enemy == 1)
    {
        ui->lineEdit_Name->setDisabled(true);
        ui->lineEdit_Name->clear();
    }
    else
    {
        ui->lineEdit_Name->setEnabled(true);
    }
}

void StartWindow::accept()
{
    if( name->contains(QRegularExpression("[^A-Za-z0-9]")) )
    {
        return;
    }
    QDialog::accept();
}
