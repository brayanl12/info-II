#ifndef JUEGO_H
#define JUEGO_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "pacman.h"
#include "fantasma.h"
#include <QBrush>

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
    void verificarSalidaFantasmas();
    void reiniciarJuegoParcial();  // <-- ESTA ES LA LÍNEA QUE FALTABA
    void verificarVictoria();
private:
    Ui::Juego *ui;
    QGraphicsScene *scene;
    QGraphicsPixmapItem *mapa;
    QGraphicsTextItem *textoScore;
    Pacman *pacman;
    QTimer *timer;
    int score =0;

    Blinky* blinky;
    Pinky* pinky;
    Clyde* clyde;
    Inky* inky;

    QGraphicsRectItem* puertaSalida;
    int salidasPendientes;
    void iniciarSalidaFantasmas();

    QList<QGraphicsPixmapItem*> iconosVidas;
    int vidas = 3;
    void reiniciarJuego();
    void actualizarVidas();
    void verificarColisiones();
    void reiniciarSoloMapaYPacman();
    void reiniciarPosiciones();
    void reiniciarTrasMuerte();
    void activarModoCazador();
    void desactivarModoCazador();

    int mapaLogico[29][30];


signals:
    void salioDelRefugio();
};

#endif // JUEGO_H
