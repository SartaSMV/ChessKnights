#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include <QString>
#include <QMessageBox>

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
    Ui::StartWindow *ui;
    //! Имя игрока
    QString *name;
    //! Сложность бота
    int *enemy;

public slots:
    //! Обрабатывает подтверждение диалога.
    void accept() Q_DECL_OVERRIDE;
    //! Обновляет значение имени игрока при изменении проверка входных данных
    void setName(QString name);
    //! Обновляет значение противника игрока при изменении
    void setEnemy(int enemy);
};
#endif // STARTWINDOW_H
