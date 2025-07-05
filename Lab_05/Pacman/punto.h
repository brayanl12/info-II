#ifndef PUNTO_H
#define PUNTO_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class Punto:public QGraphicsPixmapItem
{
public:
    Punto(qreal x, qreal y);
};

#endif // PUNTO_H
