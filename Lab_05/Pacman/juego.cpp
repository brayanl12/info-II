#include "juego.h"
#include "ui_juego.h"
#include "punto.h"
#include "puntospoder.h"

Juego::Juego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Juego)
{
    ui->setupUi(this);

    vidas = 3;
    //CREAR ESCENA
    scene = new QGraphicsScene(this);
    scene->setSceneRect(ui->graphicsView->rect());
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setScene(scene);

    //AÑADIR FONDO
    scene->setSceneRect(0, 0, 800, 600);

    QPixmap mapaPacman(":/imgPacman/mapaPacman.png");
    mapaPacman = mapaPacman.scaled(800,600);
    mapa= new QGraphicsPixmapItem(mapaPacman);
    mapa->setPos(0, 0);
    scene->addItem(mapa);

    // Crear mapa con matriz
    int mapa[25][35] = {
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,0,1},
        {1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1},
        {1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1},
        {1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,1,1},
        {1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1},
        {1,1,1,1,1,0,1,1,0,1,1,1,2,1,1,1,0,1,1,0,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,1,2,2,2,2,2,1,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,0,1,1,0,1,2,2,2,2,2,1,0,1,1,0,1,1,1,1,1},
        {1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1},
        {1,1,1,1,1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1,1,1,1,1},
        {1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,1,1,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,0,1,1,1,0,1,1,1,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1},
        {1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,0,1},
        {1,0,0,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,0,0,1},
        {1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1,1,0,1,1},
        {1,0,0,0,0,0,1,1,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0,1},
        {1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
   };



    int anchoBloque = 32;
    int altoBloque = 24;

    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 25; ++j) {
            if (mapa[i][j] == 1) {
                QGraphicsRectItem* pared = new QGraphicsRectItem(j * anchoBloque, i * altoBloque, anchoBloque, altoBloque);
                pared->setBrush(Qt::NoBrush);
                pared->setPen(Qt::NoPen);
                pared->setData(0, "pared");
                pared->setZValue(0); // Están por debajo de los puntos
                scene->addItem(pared);

            }
        }
    }

    //CREAR PUNTOS
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 25; ++j) {
            if (mapa[i][j] == 0){
                qreal x = j * anchoBloque + (anchoBloque - 8) / 2;
                qreal y = i * altoBloque + (altoBloque - 8) / 2;

                // Esquinas: puedes ajustar las posiciones
                if ((i == 1 && j == 1) || (i == 1 && j == 23) || (i == 22 && j == 1) || (i == 22 && j == 23)) {
                    PuntoPoder* poder = new PuntoPoder(x - 2, y - 2);
                    poder->setZValue(1);  // Encima de las paredes
                    scene->addItem(poder);

                } else {
                    Punto* punto = new Punto(x, y);
                    punto->setZValue(1);  // Encima de las paredes
                    scene->addItem(punto);

                }
            }
        }
    }

    // CREAR PACMAN
    int fila = 14;
    int columna = 12;
    int x = columna * anchoBloque + (anchoBloque - 24) / 2;
    int y = fila * altoBloque + (altoBloque - 24) / 2;

    pacman = new Pacman(x, y);
    scene->addItem(pacman);
    pacman->setFlag(QGraphicsItem::ItemIsFocusable);
    pacman->setFocus();

    // Crear marcador
    score = 0;
    textoScore = new QGraphicsTextItem("Puntos: 0");
    scene->addItem(textoScore);
    textoScore->setPos(10, 10);

    // Conectar señal para incrementar puntuación
    connect(pacman, &Pacman::puntoComido, this, &Juego::aumentarScore);
    connect(pacman, &Pacman::puntoComido, this, &Juego::verificarVictoria);
    connect(pacman, &Pacman::poderActivado, this, &Juego::activarModoCazador);

    //CREAR FANTASMA

    int tileSize = 24;
    int fx = 16 * tileSize;
    int fy = 12 * tileSize;

    Blinky* blinky = new Blinky(fx, fy, scene);
    scene->addItem(blinky);

    Pinky* pinky = new Pinky(fx, fy, scene);
    scene->addItem(pinky);

    Clyde* clyde = new Clyde(fx, fy, scene);
    scene->addItem(clyde);

    Inky* inky = new Inky(fx, fy, scene, blinky);
    scene->addItem(inky);

    pinky->setZValue(2);
    clyde->setZValue(2);
    inky->setZValue(2);

    this->blinky = blinky;
    this->pinky = pinky;
    this->inky = inky;
    this->clyde = clyde;

    iniciarSalidaFantasmas();
    // Variable para contar fantasmas que deben salir
    salidasPendientes = 4;

    // Conectar señales de salida de los fantasmas
    connect(blinky, &Fantasma::salioDelRefugio, this, &Juego::verificarSalidaFantasmas);
    connect(pinky, &Fantasma::salioDelRefugio, this, &Juego::verificarSalidaFantasmas);
    connect(clyde, &Fantasma::salioDelRefugio, this, &Juego::verificarSalidaFantasmas);
    connect(inky, &Fantasma::salioDelRefugio, this, &Juego::verificarSalidaFantasmas);

    puertaSalida = nullptr;

    //CREAR (vidas)
    for (int i = 0; i < vidas; ++i) {
        QGraphicsPixmapItem* vidaIcono = new QGraphicsPixmapItem(QPixmap(":/imgPacman/pacman_right_2.png").scaled(20, 20));
        vidaIcono->setPos(700 + i * 24, 10);
        scene->addItem(vidaIcono);
        iconosVidas.append(vidaIcono);
    }

    QTimer* colisionTimer = new QTimer(this);
    connect(colisionTimer, &QTimer::timeout, this, &Juego::verificarColisiones);
    colisionTimer->start(100);

    memcpy(mapaLogico, mapa, sizeof(mapa));
 }

void Juego::activarModoCazador() {
    blinky->activarVulnerable();
    pinky->activarVulnerable();
    clyde->activarVulnerable();
    inky->activarVulnerable();

    QTimer::singleShot(8000, this, &Juego::desactivarModoCazador);
}
void Juego::desactivarModoCazador() {
    blinky->desactivarVulnerable();
    pinky->desactivarVulnerable();
    clyde->desactivarVulnerable();
    inky->desactivarVulnerable();
}

void Juego::iniciarSalidaFantasmas() {
    blinky->iniciarSalida();
    pinky->iniciarSalida();
    inky->iniciarSalida();
    clyde->iniciarSalida();
}

void Juego::verificarSalidaFantasmas() {
    salidasPendientes--;
    if (salidasPendientes == 0 && puertaSalida == nullptr) {
        int filaPuerta = 10;
        int columnaPuerta = 12;
        int anchoBloque = 32;
        int altoBloque = 24;
        int x = columnaPuerta * anchoBloque;
        int y = filaPuerta * altoBloque;

        puertaSalida = new QGraphicsRectItem(x, y, anchoBloque, 4);  // altura de 4 píxeles
        puertaSalida->setBrush(Qt::gray);
        puertaSalida->setData(0, "pared");
        scene->addItem(puertaSalida);
    }
}

void Juego::verificarColisiones() {
    QList<QGraphicsItem*> colisiones = pacman->collidingItems();
    for (QGraphicsItem* item : colisiones) {
        if (Fantasma* fantasma = dynamic_cast<Fantasma*>(item)) {
            if (fantasma->estaVulnerable()) {
                scene->removeItem(fantasma);  // o fantasma->resetPosicion()
                score += 100;
                textoScore->setPlainText(QString("Puntos: %1").arg(score));
            } else {
                // Desactivar movimientos
                pacman->setEnabled(false);
                blinky->setEnabled(false);
                pinky->setEnabled(false);
                clyde->setEnabled(false);
                inky->setEnabled(false);

                vidas--;
                actualizarVidas();

                if (vidas <= 0) {
                    scene->clear();
                    scene->setBackgroundBrush(Qt::black);

                    QGraphicsTextItem* gameOverText = new QGraphicsTextItem("GAME OVER");
                    QFont font;
                    font.setPointSize(40);
                    font.setBold(true);
                    gameOverText->setFont(font);
                    gameOverText->setDefaultTextColor(Qt::red);
                    gameOverText->setPos(250, 250);
                    scene->addItem(gameOverText);
                    return;
                }

                QTimer::singleShot(500, this, &Juego::reiniciarJuegoParcial);
            }
            return;
        }
    }
}






void Juego::actualizarVidas() {
    for (int i = 0; i < iconosVidas.size(); ++i) {
        iconosVidas[i]->setVisible(i < vidas);
    }
}

void Juego::reiniciarJuego() {
    // Eliminar todos los puntos actuales
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<Punto*>(item)) {
            scene->removeItem(item);
            delete item;
        }
    }

    // Volver a crear puntos
    int anchoBloque = 32;
    int altoBloque = 24;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 25; ++j) {
            if (mapaLogico[i][j] == 0) {
                qreal x = j * anchoBloque + (anchoBloque - 8) / 2;
                qreal y = i * altoBloque + (altoBloque - 8) / 2;
                Punto* punto = new Punto(x, y);
                punto->setZValue(0);
                scene->addItem(punto);
            }
        }
    }

    // Posición inicial Pacman
    int fila = 14;
    int columna = 12;
    int x = columna * anchoBloque + (anchoBloque - 24) / 2;
    int y = fila * altoBloque + (altoBloque - 24) / 2;

    pacman->setPos(x, y);
    pacman->setDireccion(QPointF(0, 0));
    pacman->setEnabled(true);
    pacman->setFocus();

    // Fantasmas
    int tileSize = 24;
    int fx = 16 * tileSize;
    int fy = 12 * tileSize;

    blinky->setPos(fx, fy);
    pinky->setPos(fx - 24, fy);
    clyde->setPos(fx + 24, fy);
    inky->setPos(fx, fy);

    blinky->setEnabled(true);
    pinky->setEnabled(true);
    clyde->setEnabled(true);
    inky->setEnabled(true);

    blinky->iniciarSalida();
    pinky->iniciarSalida();
    clyde->iniciarSalida();
    inky->iniciarSalida();

    salidasPendientes = 4;
}

void Juego::reiniciarJuegoParcial() {
    // 1. Eliminar Pacman y fantasmas anteriores
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<Pacman*>(item) ||
            dynamic_cast<Blinky*>(item) ||
            dynamic_cast<Pinky*>(item) ||
            dynamic_cast<Inky*>(item) ||
            dynamic_cast<Clyde*>(item)) {
            scene->removeItem(item);
            delete item;
        }
    }

    // 2. Crear nuevo Pacman
    int anchoBloque = 32;
    int altoBloque = 24;
    int fila = 14;
    int columna = 12;
    int x = columna * anchoBloque + (anchoBloque - 24) / 2;
    int y = fila * altoBloque + (altoBloque - 24) / 2;

    pacman = new Pacman(x, y);
    scene->addItem(pacman);
    pacman->setFlag(QGraphicsItem::ItemIsFocusable);
    pacman->setFocus();

    connect(pacman, &Pacman::puntoComido, this, &Juego::aumentarScore);

    // 3. Crear nuevos fantasmas
    int tileSize = 24;
    int fx = 16 * tileSize;
    int fy = 12 * tileSize;

    Blinky* blinky = new Blinky(fx, fy, scene);
    scene->addItem(blinky);

    Pinky* pinky = new Pinky(fx - 24, fy, scene);
    scene->addItem(pinky);

    Clyde* clyde = new Clyde(fx + 24, fy, scene);
    scene->addItem(clyde);

    Inky* inky = new Inky(fx, fy + 24, scene, blinky);
    scene->addItem(inky);
}

void Juego::verificarVictoria() {
    QList<QGraphicsItem*> items = scene->items();
    bool quedanPuntos = false;

    for (QGraphicsItem* item : items) {
        if (dynamic_cast<Punto*>(item) || dynamic_cast<PuntoPoder*>(item)) {
            quedanPuntos = true;
            break;
        }
    }

    if (!quedanPuntos) {
        // El jugador ha ganado
        scene->clear();
        scene->setBackgroundBrush(Qt::black);

        QGraphicsTextItem* textoVictoria = new QGraphicsTextItem("¡Ganaste!");
        textoVictoria->setDefaultTextColor(Qt::green);
        textoVictoria->setFont(QFont("Arial", 36, QFont::Bold));
        textoVictoria->setPos(250, 250);
        scene->addItem(textoVictoria);
    }
}





void Juego::reiniciarSoloMapaYPacman() {
    // Eliminar todos los puntos
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem* item : items) {
        if (dynamic_cast<Punto*>(item)) {
            scene->removeItem(item);
            delete item;
        }
    }

    // Volver a crearlos según mapaLogico
    int anchoBloque = 32;
    int altoBloque = 24;
    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 25; ++j) {
            if (mapaLogico[i][j] == 0){
                qreal x = j * anchoBloque + (anchoBloque - 8) / 2;
                qreal y = i * altoBloque + (altoBloque - 8) / 2;
                Punto* punto = new Punto(x, y);
                scene->addItem(punto);
            }
        }
    }

    // Y reiniciar posiciones
    reiniciarPosiciones();
}


void Juego::reiniciarPosiciones() {
    // Posición inicial de Pacman
    int fila = 14;
    int columna = 12;
    int anchoBloque = 32;
    int altoBloque = 24;
    int x = columna * anchoBloque + (anchoBloque - 24) / 2;
    int y = fila * altoBloque + (altoBloque - 24) / 2;

    pacman->setPos(x, y);
    pacman->setDireccion(QPointF(0, 0));
    pacman->setEnabled(true);
    pacman->setFocus();

    // Posiciones iniciales de los fantasmas
    int tileSize = 24;
    int fx = 16 * tileSize;
    int fy = 12 * tileSize;

    blinky->setPos(fx, fy);
    pinky->setPos(fx - 24, fy);
    clyde->setPos(fx + 24, fy);
    inky->setPos(fx, fy);

    blinky->setEnabled(true);
    pinky->setEnabled(true);
    clyde->setEnabled(true);
    inky->setEnabled(true);

    blinky->iniciarSalida();
    pinky->iniciarSalida();
    clyde->iniciarSalida();
    inky->iniciarSalida();

    salidasPendientes = 4;
}

void Juego::reiniciarTrasMuerte() {
    // Reactivar Pac-Man y fantasmas
    pacman->setEnabled(true);
    pacman->setFocus();

    blinky->reanudar();
    pinky->reanudar();
    clyde->reanudar();
    inky->reanudar();

    // Reiniciar posiciones iniciales
    reiniciarPosiciones();  // Ya tienes esta función hecha
}



Juego::~Juego()
{
    delete ui;
}

void Juego::aumentarScore()
{
    score += 10;
    textoScore->setPlainText(QString("Puntos: %1").arg(score));
}
