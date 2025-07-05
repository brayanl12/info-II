#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QRectF>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
class Pacman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    //CONSTRUCCION PACMAN
    Pacman(qreal x0 , qreal y0);
    QRectF boundingRect() const override;
    QPainterPath shape() const override;
protected:
    void keyPressEvent(QKeyEvent *event)override;
private:
    QTimer *timer;
    QTimer* timerAnimacion;

    qreal dx= 0;
    qreal dy= 0;
    int velocidad= 2.5;

    QString direccion = "right";
    int spriteIndex = 0;
    QVector<QPixmap> spritesDerecha, spritesIzquierda, spritesArriba, spritesAbajo;

    void cargarSprites();
    void actualizarSprite();
    void mover();

signals:
    void puntoComido();


};

#endif // PACMAN_H
