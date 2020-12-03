#ifndef FIGURE_H
#define FIGURE_H

#include <QObject>
#include <QGraphicsItem>
#include <QPainter>

class Figure : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit Figure(int sizeSquare, QObject *parent = nullptr);
    ~Figure();

private:
    int sizeSquare;

    QRectF boundingRect() const Q_DECL_OVERRIDE;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
};

#endif // FIGURE_H
