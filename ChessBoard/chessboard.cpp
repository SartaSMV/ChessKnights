#include "chessboard.h"

ChessBoard::ChessBoard(QObject *parent)
    : QGraphicsScene(parent)
{

}

ChessBoard::~ChessBoard()
{   
    this->clear();
    points.clear();
    prizes.clear();
    delete [] lines;
    lines = nullptr;
}

//! Стартует игру с настройками
void ChessBoard::startGame(int countSquare, int sizeSquare, int figure, int enemy)
{
    this->countSquare = countSquare;
    this->sizeSquare = sizeSquare;
    this->enemy = enemy;
    this->figure = figure;
    this->sizeBoard = (sizeSquare + 1) * countSquare;
    this->setSceneRect(QRect(0, 0, sizeBoard, sizeBoard));
    ChessPlayers[0] = new ChessUser();

    if(!enemy) ChessPlayers[1] = new ChessBot();
    else ChessPlayers[1] = new ChessUser();

    int sizeLines = countSquare + 1;
    lines = new QGraphicsLineItem *[sizeLines * 2];
    for(int i = 0; i < sizeLines; i++)
    {
        lines[i] = addLine(i * sizeSquare + i, 0, i * sizeSquare + i, sizeBoard, QPen(Qt::black));
        lines[i + sizeLines] = addLine(0, i * sizeSquare + i, sizeBoard, i * sizeSquare + i, QPen(Qt::black));
    }

    points.resize(countSquare);
    prizes.resize(countSquare);
    for(int i = 0; i < countSquare; i++)
    {
       points[i].resize(countSquare);
       prizes[i].resize(countSquare);
       for(int j = 0; j < countSquare; j++)
       {
           points[i][j] = 0;
       }
    }

    switch (figure)
    {
    case 0:
        ChessPlayers[0]->setChessFigure(new ChessKnight(this));
        ChessPlayers[1]->setChessFigure(new ChessKnight(this));
        points[0][0] = -1;
        points[countSquare - 1][countSquare - 1] = -2;
        break;
    case 1:
        ChessPlayers[0]->setChessFigure(new ChessBishop(this));
        ChessPlayers[1]->setChessFigure(new ChessBishop(this));
        points[1][0] = -1;
        points[countSquare - 2][countSquare - 1] = -2;
        break;
    case 2:
        ChessPlayers[0]->setChessFigure(new ChessRook(this));
        ChessPlayers[1]->setChessFigure(new ChessRook(this));
        points[0][0] = -1;
        points[countSquare - 1][countSquare - 1] = -2;
        break;
    default:
        break;
    }
    ChessPlayers[0]->getChessFigure()->setSizeSquare(sizeSquare); ChessPlayers[1]->getChessFigure()->setSizeSquare(sizeSquare);
    ChessPlayers[0]->getChessFigure()->setPenPlayer(QPen(Qt::red, 3)); ChessPlayers[1]->getChessFigure()->setPenPlayer(QPen(Qt::green, 3));
    this->addItem(ChessPlayers[0]->getChessFigure());
    this->addItem(ChessPlayers[1]->getChessFigure());

    QVector< QPair<int, int> > list;
    for(int i = 0; i < countSquare; i++)
    {
        for(int j = 0; j < countSquare; j++)
        {
            if(points[i][j] == 0) list.push_back(QPair<int, int>(i, j));
        }
    }

    int rand_index = 0; count_prizes = countSquare*2;
    for(int i = 0; i < count_prizes; i++)
    {
        rand_index = QRandomGenerator::global()->bounded(list.size());
        prizes[list[rand_index].first][list[rand_index].second] = new Prize (QRandomGenerator::global()->bounded(1, 11),this);
        prizes[list[rand_index].first][list[rand_index].second]->setSizeSquare(sizeSquare);
        this->addItem(prizes[list[rand_index].first][list[rand_index].second]);
        points[list[rand_index].first][list[rand_index].second] = prizes[list[rand_index].first][list[rand_index].second]->getValue();
        list.remove(rand_index);
    }
}

//! Устанавливает новое значение размера и обновляет элементы под него
void ChessBoard::setSizeBoard(int countSquare, int sizeSquare)
{
    this->countSquare = countSquare;
    this->sizeSquare = sizeSquare;
    this->sizeBoard = (sizeSquare + 1) * countSquare;
    this->setSceneRect(QRect(0, 0, sizeBoard, sizeBoard));

    int sizeLines = countSquare + 1;
    for(int i = 0; i < sizeLines; i++)
    {
        lines[i]->setLine(i * sizeSquare + i, 0, i * sizeSquare + i, sizeBoard);
        lines[i + sizeLines]->setLine(0, i * sizeSquare + i, sizeBoard, i * sizeSquare + i);
    }

    for(int i = 0; i < countSquare; i++)
    {
       for(int j = 0; j < countSquare; j++)
       {
           switch (points[i][j])
           {
           case -1:
               ChessPlayers[0]->getChessFigure()->setSizeSquare(sizeSquare);
               ChessPlayers[0]->getChessFigure()->setPose(i * (sizeSquare + 1) + 2, j * (sizeSquare + 1) + 2, countSquare, ChessPlayers[(movePlayer + 1) % 2]->getChessFigure()->x(), ChessPlayers[(movePlayer + 1) % 2]->getChessFigure()->y());
               break;
           case -2:
               ChessPlayers[1]->getChessFigure()->setSizeSquare(sizeSquare);
               ChessPlayers[1]->getChessFigure()->setPose(i * (sizeSquare + 1) + 2, j * (sizeSquare + 1) + 2, countSquare, ChessPlayers[(movePlayer + 1) % 2]->getChessFigure()->x(), ChessPlayers[(movePlayer + 1) % 2]->getChessFigure()->y());
               break;
           case -3:
               ChessPlayers[movePlayer]->getChessFigure()->setSizeSquare(sizeSquare);
               ChessPlayers[movePlayer]->getChessFigure()->setPose(i * (sizeSquare + 1) + 2, j * (sizeSquare + 1) + 2, countSquare, ChessPlayers[(movePlayer + 1) % 2]->getChessFigure()->x(), ChessPlayers[(movePlayer + 1) % 2]->getChessFigure()->y());
               ChessPlayers[(movePlayer + 1) % 2]->getChessFigure()->setSizeSquare(sizeSquare);
               ChessPlayers[(movePlayer + 1) % 2]->getChessFigure()->setPos(i * (sizeSquare + 1) + 2, j * (sizeSquare + 1) + 2);
               break;
           case 0:
               break;
           default:
               prizes[i][j]->setSizeSquare(sizeSquare);
               prizes[i][j]->setPos(i * (sizeSquare + 1) + 2, j * (sizeSquare + 1) + 2);
               break;
           }
       }
    }

    for(auto i:rects) delete i;
    rects.clear();
    if(hide)
    {
        QSet <QPair<int, int>> trueMove = ChessPlayers[movePlayer]->getChessFigure()->getTrueMove();
        QPen penPlayer = ChessPlayers[movePlayer]->getChessFigure()->getPenPlayer();
        for(auto i:trueMove) rects.push_back(this->addRect(i.first * (sizeSquare + 1) + 2, i.second * (sizeSquare + 1) + 2, sizeSquare - 4, sizeSquare - 4, ChessPlayers[movePlayer]->getChessFigure()->getPenPlayer()));
    }
}

//! Добавляет ход в память.
void ChessBoard::addStep()
{
    QPair< QVector< QVector<int> >, int> step;
    step.first = points;
    step.second = movePlayer;
    steps.push_back(step);

}

//! Возврощает на 1 ход назад.
void ChessBoard::undoStep()
{
    if(steps.isEmpty()) return;
    QPair< QVector< QVector<int> >, int> step = steps.back();
    steps.pop_back();
    points = step.first;
    movePlayer = step.second;

    for(int i = 0; i < countSquare; i++)
    {
       for(int j = 0; j < countSquare; j++)
       {
           if(points[i][j] > 0 && prizes[i][j] == nullptr)
           {
               count_prizes++;
               prizes[i][j] =  new Prize (points[i][j], this);
               prizes[i][j]->setSizeSquare(sizeSquare);
               this->addItem(prizes[i][j]);

               ChessPlayers[movePlayer]->addPoints( -1 * points[i][j] );
               emit refreshPoints(ChessPlayers[movePlayer]->getPoints(), movePlayer);
           }
       }
    }

    this->setSizeBoard(countSquare, sizeSquare);
    if(enemy == 0 && movePlayer == 1) this->undoStep();
}

//! Меняет занчение подсказки
void ChessBoard::hideForGame()
{
    this->hide = !hide;
}

//! Сохраняет игрока в поток \a ost.
void ChessBoard::save(QDataStream &ost) const
{
    ost << countSquare << sizeSquare << enemy << figure;

    int size = points.size();
    ost << size;
    for(int i = 0; i < size; i++)
    {
        for(int j = 0; j < size; j++)
        {
            ost << points[i][j];
        }
    }

    int size_s = steps.size();
    ost << size_s;
    for(int k = 0; k < size_s; k++)
    {
        ost << steps[k].second;
        for(int i = 0; i < size; i++)
        {
            for(int j = 0; j < size; j++)
            {
                ost << steps[k].first[i][j];
            }
        }
    }

    ost<< ChessPlayers[0]->getPoints() << ChessPlayers[1]->getPoints() << movePlayer;
}

//! Загружает игрока из потока \a ist.
void ChessBoard::load(QDataStream &ist)
{
    int points0, points1;
    count_prizes = 0;
    ist >> countSquare >> sizeSquare >> enemy >> figure;

    int size;
    ist >> size;
    points.resize(size);
    for(int i = 0; i < size; i++)
    {
        points[i].resize(size);
        for(int j = 0; j < size; j++)
        {
            ist >> points[i][j];
        }
    }

    int size_s;
    ist >> size_s;
    steps.resize(size_s);
    for(int k = 0; k < size_s; k++)
    {
        ist >> steps[k].second;
        steps[k].first.resize(size);
        for(int i = 0; i < size; i++)
        {
            steps[k].first[i].resize(size);
            for(int j = 0; j < size; j++)
            {
                ist >> steps[k].first[i][j];
            }
        }
    }

    ist >> points0 >> points1 >> movePlayer;

    sizeBoard = (sizeSquare + 1) * countSquare;
    ChessPlayers[0] = new ChessUser();

    if(enemy) ChessPlayers[1] = new ChessBot();
    else ChessPlayers[1] = new ChessUser();
    ChessPlayers[0]->refreshPoints(); ChessPlayers[1]->refreshPoints();
    ChessPlayers[0]->addPoints(points0); ChessPlayers[1]->addPoints(points1);
    emit refreshPoints(ChessPlayers[0]->getPoints(), 0); emit refreshPoints(ChessPlayers[1]->getPoints(), 1);

    int sizeLines = countSquare + 1;
    lines = new QGraphicsLineItem *[sizeLines * 2];
    for(int i = 0; i < sizeLines; i++)
    {
        lines[i] = addLine(i * sizeSquare + i, 0, i * sizeSquare + i, sizeBoard, QPen(Qt::black));
        lines[i + sizeLines] = addLine(0, i * sizeSquare + i, sizeBoard, i * sizeSquare + i, QPen(Qt::black));
    }

    prizes.resize(countSquare);
    for(int i = 0; i < countSquare; i++)
    {
       prizes[i].resize(countSquare);
    }

    switch (figure)
    {
    case 0:
        ChessPlayers[0]->setChessFigure(new ChessKnight(this));
        ChessPlayers[1]->setChessFigure(new ChessKnight(this));
        break;
    case 1:
        ChessPlayers[0]->setChessFigure(new ChessBishop(this));
        ChessPlayers[1]->setChessFigure(new ChessBishop(this));
        break;
    case 2:
        ChessPlayers[0]->setChessFigure(new ChessRook(this));
        ChessPlayers[1]->setChessFigure(new ChessRook(this));
        break;
    default:
        break;
    }
    ChessPlayers[0]->getChessFigure()->setSizeSquare(sizeSquare); ChessPlayers[1]->getChessFigure()->setSizeSquare(sizeSquare);
    ChessPlayers[0]->getChessFigure()->setPenPlayer(QPen(Qt::red, 3)); ChessPlayers[1]->getChessFigure()->setPenPlayer(QPen(Qt::green, 3));
    this->addItem(ChessPlayers[0]->getChessFigure());
    this->addItem(ChessPlayers[1]->getChessFigure());

    for(int i = 0; i < countSquare; i++)
    {
        for(int j = 0; j < countSquare; j++)
        {
            if(points[i][j] > 0)
            {
                count_prizes++;
                prizes[i][j] = new Prize (points[i][j], this);
                prizes[i][j]->setSizeSquare(sizeSquare);
                this->addItem(prizes[i][j]);
            }
        }
    }

    emit swapEnemy(enemy);
}

void ChessBoard::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x() / (sizeSquare + 1); int y = event->scenePos().y() / (sizeSquare + 1);
    if(x < 0 || y < 0 || x > countSquare - 1 || y > countSquare - 1 || event->scenePos().x() < 0 || event->scenePos().y() < 0) return;
    int x2 = ChessPlayers[movePlayer]->getChessFigure()->x() / (sizeSquare + 1); int y2 = ChessPlayers[movePlayer]->getChessFigure()->y() / (sizeSquare + 1);

    QPointF to = (event->scenePos());
    if(ChessPlayers[movePlayer]->checkMove(&to))
    {
        this->addStep();
        if(points[x2][y2] == -3)
        {
            if(points[x][y] != 0)
            {
                ChessPlayers[movePlayer]->addPoints(points[x][y]);
                emit refreshPoints(ChessPlayers[movePlayer]->getPoints(), movePlayer);
                delete prizes[x][y];
                prizes[x][y] = nullptr;
                count_prizes--;
            }
            ChessPlayers[movePlayer]->getChessFigure()->setZValue(0);
            points[x][y] = -1*movePlayer - 1;
            points[x2][y2] -= points[x][y];
            movePlayer = (movePlayer + 1) % 2;
        }
        else
        {
            if(points[x][y] < 0)
            {
                points[x][y] += points[x2][y2];
                points[x2][y2] = 0;
                ChessPlayers[movePlayer]->getChessFigure()->setZValue(20);
            }
            else if(points[x][y] == 0)
            {
                points[x][y] = points[x2][y2];
                points[x2][y2] = 0;
                movePlayer = (movePlayer + 1) % 2;
            }
            else
            {
                ChessPlayers[movePlayer]->addPoints(points[x][y]);
                emit refreshPoints(ChessPlayers[movePlayer]->getPoints(), movePlayer);
                delete prizes[x][y];
                prizes[x][y] = nullptr;
                count_prizes--;
                points[x][y] = points[x2][y2];
                points[x2][y2] = 0;
                movePlayer = (movePlayer + 1) % 2;
            }
        }
    }
    if(count_prizes == 0) emit finishGame(ChessPlayers);

    while(enemy == 0 && movePlayer == 1)
    {
        this->addStep();
        setSizeBoard(countSquare, sizeSquare);
        QSet <QPair<int, int>> move = ChessPlayers[movePlayer]->getChessFigure()->getTrueMove();
        ChessPlayers[movePlayer]->checkMove(&to);
        for(auto i:move)
        {
            if(points[to.x()][to.y()] < points[i.first][i.second])
            {
                to = QPointF(i.first, i.second);
            }
        }

        int x = to.x(); int y = to.y();
        if(x < 0 || y < 0 || x > countSquare - 1 || y > countSquare - 1 || event->scenePos().x() < 0 || event->scenePos().y() < 0) return;
        int x2 = ChessPlayers[movePlayer]->getChessFigure()->x() / (sizeSquare + 1); int y2 = ChessPlayers[movePlayer]->getChessFigure()->y() / (sizeSquare + 1);

        if(points[x2][y2] == -3)
        {
            if(points[x][y] != 0)
            {
                ChessPlayers[movePlayer]->addPoints(points[x][y]);
                emit refreshPoints(ChessPlayers[movePlayer]->getPoints(), movePlayer);
                delete prizes[x][y];
                prizes[x][y] = nullptr;
                count_prizes--;
            }
            ChessPlayers[movePlayer]->getChessFigure()->setZValue(0);
            points[x][y] = -1*movePlayer - 1;
            points[x2][y2] -= points[x][y];
            movePlayer = (movePlayer + 1) % 2;
        }
        else
        {
            if(points[x][y] < 0)
            {
                points[x][y] += points[x2][y2];
                points[x2][y2] = 0;
                ChessPlayers[movePlayer]->getChessFigure()->setZValue(20);
            }
            else if(points[x][y] == 0)
            {
                points[x][y] = points[x2][y2];
                points[x2][y2] = 0;
                movePlayer = (movePlayer + 1) % 2;
            }
            else
            {
                ChessPlayers[movePlayer]->addPoints(points[x][y]);
                emit refreshPoints(ChessPlayers[movePlayer]->getPoints(), movePlayer);
                delete prizes[x][y];
                prizes[x][y] = nullptr;
                count_prizes--;
                points[x][y] = points[x2][y2];
                points[x2][y2] = 0;
                movePlayer = (movePlayer + 1) % 2;
            }
        }
    }

    if(count_prizes == 0) emit finishGame(ChessPlayers);
}
