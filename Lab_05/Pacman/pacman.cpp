#include "pacman.h"
#include "punto.h"

Pacman::Pacman(qreal x0, qreal y0)
{
    setPos(x0,y0);

    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();

    cargarSprites();
    setPixmap(spritesDerecha[0]);

    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this, &Pacman::mover);
    timer->start(30);

    timerAnimacion = new QTimer(this);
    connect(timerAnimacion, &QTimer::timeout, this, &Pacman::actualizarSprite);
    timerAnimacion->start(100);
}


//CREAR OBJETO (pacman)
QRectF Pacman::boundingRect() const {
    return QRectF(0, 0, 30, 15); // Debe coincidir con el tamaño del sprite
}

QPainterPath Pacman::shape() const {
    QPainterPath path;
    path.addRect(0, 0, 22, 20); // Define la forma de colisión como rectángulo
    return path;
}

void Pacman::cargarSprites() {
    QSize tamaño(22, 16); // Tamaño deseado del sprite

    spritesDerecha.append(QPixmap(":/imgPacman/pacman_right_1.png").scaled(tamaño, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    spritesDerecha.append(QPixmap(":/imgPacman/pacman_right_2.png").scaled(tamaño, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    spritesIzquierda.append(QPixmap(":/imgPacman/pacman_left_1.png").scaled(tamaño, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    spritesIzquierda.append(QPixmap(":/imgPacman/pacman_left_2.png").scaled(tamaño, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    spritesArriba.append(QPixmap(":/imgPacman/pacman_up_1.png").scaled(tamaño, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    spritesArriba.append(QPixmap(":/imgPacman/pacman_up_2.png").scaled(tamaño, Qt::KeepAspectRatio, Qt::SmoothTransformation));

    spritesAbajo.append(QPixmap(":/imgPacman/pacman_down_1.png").scaled(tamaño, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    spritesAbajo.append(QPixmap(":/imgPacman/pacman_down_2.png").scaled(tamaño, Qt::KeepAspectRatio, Qt::SmoothTransformation));
}


void Pacman::actualizarSprite() {
    spriteIndex = (spriteIndex + 1) % 2;
    if (direccion == "right")
        setPixmap(spritesDerecha[spriteIndex]);
    else if (direccion == "left")
        setPixmap(spritesIzquierda[spriteIndex]);
    else if (direccion == "up")
        setPixmap(spritesArriba[spriteIndex]);
    else if (direccion == "down")
        setPixmap(spritesAbajo[spriteIndex]);
}



//CONTROL (teclado)
void Pacman::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Z: dx = 0; dy = velocidad; direccion = "down"; break;
    case Qt::Key_S: dx = 0; dy = -velocidad; direccion = "up"; break;
    case Qt::Key_D: dx = velocidad; dy = 0; direccion = "right"; break;
    case Qt::Key_A: dx = -velocidad; dy = 0; direccion = "left"; break;
    default: break;
    }
}

void Pacman::mover() {
    qreal prevX = x();
    qreal prevY = y();
    qreal newX = prevX + dx;
    qreal newY = prevY + dy;

    setPos(newX, newY);

    for (QGraphicsItem* item : collidingItems()) {
        if (dynamic_cast<QGraphicsRectItem*>(item)) {
            setPos(prevX, prevY); // pared
            return;
        }

        Punto* punto = dynamic_cast<Punto*>(item);
        if (punto) {
            scene()->removeItem(punto);
            delete punto;
            emit puntoComido();
             // o tu sistema de puntaje
            // Aquí podrías emitir una señal para actualizar un QLabel
        }
    }
}




