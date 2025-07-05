#include "juego.h"
#include "ui_juego.h"
#include "punto.h"

Juego::Juego(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Juego)
{
    ui->setupUi(this);

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
    int mapa[29][30] = {
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
        {1,1,1,1,1,0,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1},
        {0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0},
        {1,1,1,1,1,0,1,1,0,1,0,0,0,0,0,1,0,1,1,0,1,1,1,1,1},
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

    for (int i = 0; i < 40; ++i) {
        for (int j = 0; j < 40; ++j) {
            if (mapa[i][j] == 1) {
                QGraphicsRectItem* pared = new QGraphicsRectItem(j * anchoBloque, i * altoBloque, anchoBloque, altoBloque);
                pared->setBrush(Qt::darkBlue);
                scene->addItem(pared);
            }
        }
    }

    for (int i = 0; i < 25; ++i) {
        for (int j = 0; j < 25; ++j) {
            if (mapa[i][j] == 0) { // solo en caminos
                qreal x = j * anchoBloque + (anchoBloque - 8) / 2;
                qreal y = i * altoBloque + (altoBloque - 8) / 2;
                Punto* punto = new Punto(x, y);
                scene->addItem(punto);
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
