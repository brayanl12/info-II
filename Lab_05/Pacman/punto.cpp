#include "punto.h"

Punto::Punto(qreal x, qreal y) {
    setPixmap(QPixmap(":/imgPacman/punto.png").scaled(20,40,Qt::KeepAspectRatio,Qt::SmoothTransformation));
    setPos(x,y);
}
