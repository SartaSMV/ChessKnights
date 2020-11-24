#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class StartWindow; }
QT_END_NAMESPACE

class StartWindow : public QDialog
{
    Q_OBJECT

public:
    StartWindow(QWidget *parent = nullptr, QString *name = new QString(""), int *enemy = new int(0));
    ~StartWindow();

private:
    QString *name;
    int *enemy;
    Ui::StartWindow *ui;

public slots:
    //! Обрабатывает подтверждение диалога.
    void accept() Q_DECL_OVERRIDE;
    //! Обновляет значение имени игрока при изменении
    void setName(QString name);
    //! Обновляет значение противника игрока при изменении
    void setEnemy(int enemy);
};
#endif // STARTWINDOW_H
