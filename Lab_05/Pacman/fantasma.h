#ifndef FANTASMA_H
#define FANTASMA_H

#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QObject>

#include "pacman.h"

class Fantasma : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    Fantasma(int x, int y, QGraphicsScene* escena, QGraphicsItem* parent = nullptr);

    virtual void calcularDireccion(Pacman* pacman);
    void mover();
    void iniciarSalida();
    void pausar();
    void reanudar();

    void activarVulnerable();
    void desactivarVulnerable();
    bool estaVulnerable() const;
    void resetPosicion();  // NUEVO: para reaparición tras ser comido

signals:
    void salioDelRefugio();

protected:
    QGraphicsScene* escena;
    QTimer* timer;
    QPointF objetivo;
    int direccionX = 0;
    int direccionY = 0;

    bool saliendo = false;
    int acumulado = 0;
    int pasosSalida = 3;
    int velocidad = 200;

    bool vulnerable = false;

    QPixmap imagenNormal;
    QPixmap imagenVulnerable;
};

// BLINKY
class Blinky : public Fantasma {
public:
    using Fantasma::Fantasma;
protected:
    void calcularDireccion(Pacman* pacman) override;
};

// PINKY
class Pinky : public Fantasma {
public:
    using Fantasma::Fantasma;
protected:
    void calcularDireccion(Pacman* pacman) override;
};

// INKY
class Inky : public Fantasma {
public:
    Inky(int x, int y, QGraphicsScene* escena, Blinky* blinky);
protected:
    void calcularDireccion(Pacman* pacman) override;
private:
    Blinky* blinky;
};

// CLYDE
class Clyde : public Fantasma {
public:
    using Fantasma::Fantasma;
protected:
    void calcularDireccion(Pacman* pacman) override;
};

#endif // FANTASMA_H
