#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent, bool *start)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Chess Knights");
    connect(this, &MainWindow::gameMenu, this, &MainWindow::game);
    mRatingboard = new RatingBoard();
    mRatingboard->load();

    // Вводимые данные до запуска окна
    QString playerName = ""; enemy = 0;
    StartWindow startW(this, &playerName, &enemy);
    //Игрок решил не играть
    if (startW.exec() != StartWindow::Accepted) *start = false;
    else *start = true;

    if(enemy == 0)
    {
        ui->label_First_Player->setText(playerName);
        ui->label_Second_Player->setText("Bot");
    }
    ui->label_First_Player->setStyleSheet("QLabel { color: red }");
    ui->label_Second_Player->setStyleSheet("QLabel { color: green }");

    ui->actionUndo->setEnabled(false);
    ui->actionSave->setEnabled(false);
    ui->actionHide->setEnabled(false);
    if(enemy) ui->comboBox_Difficulty->setEnabled(false);
    ui->graphicsView_chessboard->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView_chessboard->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView_chessboard->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timer.setSingleShot(true);
    connect(&timer, &QTimer::timeout, this, &MainWindow::refresh);
}

MainWindow::~MainWindow()
{
    disconnect(this, &MainWindow::gameMenu, this, &MainWindow::game);
    disconnect(&timer, &QTimer::timeout, this, &MainWindow::refresh);
    delete ui;
}

//! Обновляет экран через установленное значения
void MainWindow::refresh()
{
    timer.stop();

    int countSquare = (ui->comboBox_Field_Size->currentIndex() + 1) * 8;
    int width = ui->graphicsView_chessboard->width();
    int height = ui->graphicsView_chessboard->height();

    int sizeSquare = (height > width) ? (width) : (height);
    sizeSquare = sizeSquare / (countSquare) - 2;
    mChessBoard->setSizeBoard(countSquare, sizeSquare);

    timer.start(50);
}

//! Обновляет экран после изменения количества очков
void MainWindow::refreshPoints(int points, int movePlayer)
{
    if(movePlayer == 0)
    {
        ui->lineEdit_First_Player->setText(QString::number(points));
    }
    else
    {
        ui->lineEdit_Second_Player->setText(QString::number(points));
    }
}

void MainWindow::finishGame(ChessPlayer *ChessPlayers[2])
{
    timer.stop();

    ChessPlayers[0]->setName(ui->label_First_Player->text());
    ChessPlayers[1]->setName(ui->label_Second_Player->text());

    if(enemy == 0)
    {
        mRatingboard->setSizeBoard((ui->comboBox_Field_Size->currentIndex() + 1) * 8);
        mRatingboard->pushNewUsers(*ChessPlayers[0]);
        mRatingboard->save();
    }
    QString finishText = "Win ";
    if(ChessPlayers[0]->getPoints() > ChessPlayers[1]->getPoints())
    {
        finishText += ui->label_First_Player->text() + " with " + QString::number(ChessPlayers[0]->getPoints()) + " points!!!";
    }
    else if(ChessPlayers[0]->getPoints() < ChessPlayers[1]->getPoints())
    {
        finishText += ui->label_Second_Player->text() + " with " + QString::number(ChessPlayers[0]->getPoints()) + " points!!!";
    }
    else
    {
        finishText = "Draw!";
    }

    emit gameMenu(false);

    QMessageBox finish_Game(QMessageBox::Information, "Finish game!!!", finishText, QMessageBox::Ok, this);
    finish_Game.exec();
}

//! Загрузить сохраненную партию.
bool MainWindow::loadGame()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Load Game"), QString(), QT_TRANSLATE_NOOP("Load", "Game (*.save)"));
    // Если пользователь не выбрал файл, возвращаем false
    if (fileName.isEmpty())
    {
        return false;
    }
    // Блок обработки исключительных ситуаций
    try
    {
        // Создаём объект inf, связанный с файлом fileName
        QFile inf(fileName);
        // Открываем файл только для чтения
        if (!inf.open(QIODevice::ReadOnly))
        {
            throw std::runtime_error((tr("open(): ") + inf.errorString()).toStdString());
        }
        // Привязываем к файлу поток, позволяющий считывать объекты Qt
        QDataStream ist(&inf);

        QString name1(""), name2("");
        ist >> name1 >> name2;
        ui->label_First_Player->setText(name1);  ui->label_Second_Player->setText(name2);

        mChessBoard = new ChessBoard(this);
        connect(mChessBoard, &ChessBoard::refreshPoints, this, &MainWindow::refreshPoints);
        connect(mChessBoard, &ChessBoard::finishGame, this, &MainWindow::finishGame);
        connect(mChessBoard, &ChessBoard::swapEnemy, this, &MainWindow::swapEnemy);
        mChessBoard->load(ist);
        ui->graphicsView_chessboard->setScene(mChessBoard);

        ui->actionUndo->setEnabled(true);
        ui->actionSave->setEnabled(true);
        ui->actionLoad->setEnabled(false);
        ui->comboBox_Field_Size->setEnabled(false);
        ui->comboBox_Figure->setEnabled(false);
        ui->comboBox_Difficulty->setEnabled(false);
        ui->pushButton_Start_Finish->setText("Finish");
        timer.start(50);

    }
    catch (const std::exception &e)
    {
        // Если при открытии файла возникла исключительная ситуация, сообщить пользователю
        QMessageBox::critical(this, "Chess Knight", tr("Unable to open the file %1: %2").arg(fileName).arg(e.what()));
        return false;
    }

    return true;
}

//! Сохранить текущую партию.
bool MainWindow::saveGame()
{
    // Если игра не начата, выдаём сообщение об этом
    if (mChessBoard == nullptr) return false;
    // Выводим диалог выбора файла для сохранения
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save game"), QString(), QT_TRANSLATE_NOOP("Save", "Game (*.save)"));
    // Если пользователь не выбрал файл, возвращаем false
    if (fileName.isEmpty())
    {
        return false;
    }

    // Блок обработки исключительных ситуаций
    try
    {
        /*
         * Создаём объект outf, связанный с файлом fileName.
         * QSaveFile обеспечивает безопасное сохранение (через промежуточный
         * временный файл), чтобы избежать потери данных в случае нештатного
         * завершения операции сохранения. Само сохранение происходит при вызове
         * метода commit().
         */
        QSaveFile outf(fileName);
        // Открываем файл только для записи
        outf.open(QIODevice::WriteOnly);
        // Привязываем к файлу поток, позволяющий выводить объекты Qt
        QDataStream ost(&outf);
        ost << ui->label_First_Player->text() << ui->label_Second_Player->text();
        // Выводим записную книжку в файл
        mChessBoard->save(ost);
        // Запускаем сохранение и смотрим результат.
        // В случае неудачи запускаем исключительную ситуацию (блок прерывается,
        // управление передаётся в блок catch)
        if (!outf.commit())
        {
            throw std::runtime_error(tr("Unable to commit the save").toStdString());
        }
    }
    catch (const std::exception &e)
    {
        // Если при сохранении файла возникла исключительная ситуация, сообщить пользователю
        QMessageBox::critical(this, "Chess Knight", tr("Unable to write to the file %1: %2").arg(fileName).arg(e.what()));
    }

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
    mRatingboard->setSizeBoard((ui->comboBox_Field_Size->currentIndex() + 1) * 8);
    mRatingboard->load();
    mRatingboard->fillTable();
    mRatingboard->show();
}

//! Вызывает окно с инструкцией.
void MainWindow::help()
{
    QApplication::instance()->quit();
}

//! Подсказка для выгодного хода.
void MainWindow::hideForGame()
{
    mChessBoard->hideForGame();
}

//! Игра возврощается на ход назад.
void MainWindow::undo()
{
    mChessBoard->undoStep();
}

//! Слот настройки меню игры на старт и финишь
void MainWindow::game(bool game)
{
    if(game)
    {
        int countSquare = (ui->comboBox_Field_Size->currentIndex() + 1) * 8;
        int width = ui->graphicsView_chessboard->width();
        int height = ui->graphicsView_chessboard->height();
        int sizeSquare = (height > width) ? (width) : (height);
        sizeSquare = sizeSquare / (countSquare) - 2;

        mChessBoard = new ChessBoard(this);
        connect(mChessBoard, &ChessBoard::refreshPoints, this, &MainWindow::refreshPoints);
        connect(mChessBoard, &ChessBoard::finishGame, this, &MainWindow::finishGame);
        connect(mChessBoard, &ChessBoard::swapEnemy, this, &MainWindow::swapEnemy);
        mChessBoard->startGame(countSquare, sizeSquare, ui->comboBox_Figure->currentIndex(), enemy);
        ui->graphicsView_chessboard->setScene(mChessBoard);

        ui->lineEdit_First_Player->setText("0");
        ui->lineEdit_Second_Player->setText("0");
        ui->pushButton_Start_Finish->setText("Finish");
    }
    else
    {
        disconnect(mChessBoard, &ChessBoard::refreshPoints, this, &MainWindow::refreshPoints);
        disconnect(mChessBoard, &ChessBoard::finishGame, this, &MainWindow::finishGame);
        disconnect(mChessBoard, &ChessBoard::swapEnemy, this, &MainWindow::swapEnemy);
        mChessBoard->clear();
        delete mChessBoard;
        mChessBoard = nullptr;

        ui->lineEdit_First_Player->setText("");
        ui->lineEdit_Second_Player->setText("");
        ui->pushButton_Start_Finish->setText("Start");
    }

    ui->actionUndo->setEnabled(game);
    ui->actionSave->setEnabled(game);
    ui->actionHide->setEnabled(game);
    ui->actionLoad->setEnabled(!game);
    ui->comboBox_Field_Size->setEnabled(!game);
    ui->comboBox_Figure->setEnabled(!game);
    if(!enemy) ui->comboBox_Difficulty->setEnabled(!game);
}

//! Слот смены врага
void MainWindow::swapEnemy(int enemy)
{
    this->enemy = enemy;
}

//! Стартует и заканчивает игру.
void MainWindow::startFinishGame()
{
    if(ui->pushButton_Start_Finish->text() == "Start")
    {
        emit gameMenu(true);
        timer.start(50);
    }
    else
    {
        timer.stop();
        emit gameMenu(false);
    }
}
