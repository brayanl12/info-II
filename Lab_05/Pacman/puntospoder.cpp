#include "puntospoder.h"
#include <QBrush>
#include <QPen>

PuntoPoder::PuntoPoder(qreal x, qreal y) {
    setRect(0, 0, 12, 12);
    setBrush(QBrush(Qt::white));
    setPen(QPen(Qt::NoPen));
    setPos(x, y);
    setZValue(0);
    setData(0, "poder");
}

