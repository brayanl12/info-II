#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "pacman.h"

namespace Ui {
class Juego;
}

class Juego : public QWidget
{
    Q_OBJECT

public:
    explicit Juego(QWidget *parent = nullptr);
    ~Juego();

public slots:
    void aumentarScore();
private:
    Ui::Juego *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *mapa;
    QGraphicsTextItem *textoScore;
    Pacman *pacman;
    QTimer *timer;
    int score =0;
};

#endif // JUEGO_H
