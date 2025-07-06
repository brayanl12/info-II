#include "fantasma.h"
#include <QPixmap>
#include <cstdlib>
#include <ctime>
#include <QGraphicsItem>

Fantasma::Fantasma(int x, int y, QGraphicsScene* escena, QGraphicsItem *parent)
    : QGraphicsPixmapItem(parent), escena(escena)
{
    setPixmap(QPixmap(":/imgPacman/fantasma.png").scaled(20, 16));
    setPos(x, y);

    srand(time(nullptr));
    direccionX = 0;
    direccionY = 0;
    objetivo = pos(); // inicializa objetivo

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Fantasma::mover);
    timer->start(200);
}

void Fantasma::calcularDireccion(Pacman* pacman) {
    // Comportamiento por defecto: ir directamente hacia Pacman
    objetivo = pacman->pos();
}

void Fantasma::mover() {
    if (!escena) return;

    // Animación de salida inicial
    if (saliendo) {
        setPos(x(), y() - 4);
        acumulado += 4;

        if (acumulado >= 24 * pasosSalida) {
            saliendo = false;
            acumulado = 0;
            emit salioDelRefugio();
        }
        return;
    }




    // Buscar a Pacman en la escena
    Pacman* pacman = nullptr;
    for (QGraphicsItem* item : escena->items()) {
        pacman = dynamic_cast<Pacman*>(item);
        if (pacman) break;
    }
    if (!pacman) return;

    // Calcular objetivo según tipo de fantasma
    calcularDireccion(pacman);

    // Calcular dirección preferida hacia el objetivo
    QPointF dir = objetivo - pos();
    if (qAbs(dir.x()) > qAbs(dir.y())) {
        direccionX = (dir.x() > 0) ? 1 : -1;
        direccionY = 0;
    } else {
        direccionX = 0;
        direccionY = (dir.y() > 0) ? 1 : -1;
    }

    // Calcular siguiente posición
    QRectF siguiente = mapToScene(boundingRect()).boundingRect().translated(direccionX * 4, direccionY * 4);
    QList<QGraphicsItem*> posibles = escena->items(siguiente);

    bool hayPared = false;
    for (auto item : posibles) {
        if (item == this) continue;
        if (item->data(0) == "pared") {
            hayPared = true;
            break;
        }
    }

    if (!hayPared) {
        // Movimiento válido
        setPos(x() + direccionX * 4, y() + direccionY * 4);
    } else {
        // Movimiento alternativo aleatorio (evita quedarse atascado)
        QList<QPoint> direcciones = { {1,0}, {-1,0}, {0,1}, {0,-1} };
        std::random_shuffle(direcciones.begin(), direcciones.end());

        for (const QPoint& dirAlt : direcciones) {
            QRectF intento = mapToScene(boundingRect()).boundingRect().translated(dirAlt.x() * 4, dirAlt.y() * 4);
            QList<QGraphicsItem*> colisiones = escena->items(intento);

            bool choca = false;
            for (auto item : colisiones) {
                if (item == this) continue;
                if (item->data(0) == "pared") {
                    choca = true;
                    break;
                }
            }

            if (!choca) {
                direccionX = dirAlt.x();
                direccionY = dirAlt.y();
                setPos(x() + direccionX * 4, y() + direccionY * 4);
                break;
            }
        }
    }
}

void Fantasma::iniciarSalida() {
    saliendo = true;
}



// BLINKY
void Blinky::calcularDireccion(Pacman* pacman) {
    objetivo = pacman->pos();
}

// PINKY
void Pinky::calcularDireccion(Pacman* pacman) {
    QPointF adelante = pacman->pos() + pacman->getDireccion() * 4 * 4; // 4 tiles
    objetivo = adelante;
}

// INKY
Inky::Inky(int x, int y, QGraphicsScene* escena, Blinky* blinky)
    : Fantasma(x, y, escena), blinky(blinky) {}

void Inky::calcularDireccion(Pacman* pacman) {
    if (!pacman || !blinky) return;
    QPointF frente = pacman->pos() + pacman->getDireccion() * 4 * 2;
    QPointF delta = frente - blinky->pos();
    objetivo = frente + delta;
}

// CLYDE
void Clyde::calcularDireccion(Pacman* pacman) {
    qreal dist = QLineF(pos(), pacman->pos()).length();
    if (dist > 100)
        objetivo = pacman->pos();
    else
        objetivo = QPointF(0, 600); // esquina inferior izquierda
}

void Fantasma::pausar() {
    if (timer) timer->stop();
}

void Fantasma::reanudar() {
    if (timer) timer->start(velocidad);
}

void Fantasma::activarVulnerable() {
    vulnerable = true;
    setPixmap(QPixmap(":/imgPacman/fantasma_vulnerable.png").scaled(20, 16));
}

void Fantasma::desactivarVulnerable() {
    vulnerable = false;
    setPixmap(QPixmap(":/imgPacman/fantasma.png").scaled(20, 16));
}

bool Fantasma::estaVulnerable() const {
    return vulnerable;
}

void Fantasma::resetPosicion()
{
    setPos(16 * 24, 12 * 24);  // posición central de la jaula
    iniciarSalida();
}
