#include "widget.h"
#include "ui_widget.h"
#include <QFile>
#include <QTextStream>

const double DT = 1.0;

Widget::Widget(QWidget *parent)
    : QWidget(parent), ui(new Ui::Widget)
{
    ui->setupUi(this);

    scene = new QGraphicsScene(this);
    scene->setSceneRect(-4000, -4000, 8000, 8000);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->centerOn(0, 0);
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // Conexión de botones
    connect(ui->btnSistema1, &QPushButton::clicked, this, &Widget::cargarSistema1);
    connect(ui->btnSistema2, &QPushButton::clicked, this, &Widget::cargarSistema2);
    connect(ui->btnCrearSistema, &QPushButton::clicked, this, &Widget::crearSistemaDesdeTabla);
    connect(ui->btnLimpiarTabla, &QPushButton::clicked, this, &Widget::limpiarTabla);
    connect(ui->btnAgregarCuerpo, &QPushButton::clicked, this, &Widget::agregarCuerpoDesdeInputs);

    // Timer
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &Widget::actualizar);
    timer->start(10);

    cargarSistema1();  // Por defecto
}

Widget::~Widget()
{
    delete ui;
}

void Widget::actualizar()
{
    for (auto* c : cuerpos)
        c->resetFuerza();

    for (int i = 0; i < cuerpos.size(); ++i) {
        for (int j = i + 1; j < cuerpos.size(); ++j) {
            cuerpos[i]->actualizarFuerza(cuerpos[j]);
            cuerpos[j]->actualizarFuerza(cuerpos[i]);
        }
    }

    for (auto* c : cuerpos)
        c->mover(DT);

    guardarPosiciones();

    if (!cuerpos.isEmpty())
        ui->graphicsView->centerOn(cuerpos[0]);

    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Widget::guardarPosiciones()
{
    QString nombreArchivo = (sistemaActivo == 1) ? "sistema1.txt" :
                                (sistemaActivo == 2) ? "sistema2.txt" :
                                "sistema_tabla.txt";

    QFile archivo(nombreArchivo);
    if (archivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&archivo);
        for (Cuerpo* c : cuerpos)
            out << c->x() << "\t" << c->y() << "\t";
        out << "\n";
        archivo.close();
    }
}

void Widget::limpiarSistema()
{
    for (Cuerpo* c : cuerpos) {
        scene->removeItem(c);
        delete c;
    }
    cuerpos.clear();
}

void Widget::cargarSistema1()
{
    sistemaActivo = 1;
    limpiarSistema();

    cuerpos.append(new Cuerpo(0, -7000, 2, 0, 70, 120));
    cuerpos.append(new Cuerpo(0, 0, 0, 0, 70000, 300));
    cuerpos.append(new Cuerpo(4000, 5000, -1.6, 1.2, 25, 100));

    for (Cuerpo* c : cuerpos) {
        scene->addItem(c);
        c->setBrush(Qt::green);
    }

    QFile archivo("sistema1.txt");
    archivo.open(QIODevice::WriteOnly | QIODevice::Text);
    archivo.close();
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void Widget::cargarSistema2()
{
    sistemaActivo = 2;
    limpiarSistema();

    cuerpos.append(new Cuerpo(0, 0, 0, 0, 50000, 200));
    cuerpos.append(new Cuerpo(-5000, 0, 0, -2, 70, 70));
    cuerpos.append(new Cuerpo(5000, 0, 0, 2, 70, 70));
    cuerpos.append(new Cuerpo(0, -5000, 2, 0, 70, 70));
    cuerpos.append(new Cuerpo(0, 5000, -2, 0, 70, 70));

    for (Cuerpo* c : cuerpos) {
        scene->addItem(c);
        c->setBrush(Qt::magenta);
    }

    QFile archivo("sistema2.txt");
    archivo.open(QIODevice::WriteOnly | QIODevice::Text);
    archivo.close();
    ui->graphicsView->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
}

void Widget::crearSistemaDesdeTabla()
{
    sistemaActivo = 3;
    limpiarSistema();

    int filas = ui->tablaCuerpos->rowCount();

    for (int i = 0; i < filas; ++i) {
        auto leerCelda = [this, i](int col) {
            return ui->tablaCuerpos->item(i, col) ? ui->tablaCuerpos->item(i, col)->text().toDouble() : 0.0;
        };

        double x = leerCelda(0);
        double y = leerCelda(1);
        double masa = leerCelda(2);
        double radio = leerCelda(3);
        double vx = leerCelda(4);
        double vy = leerCelda(5);

        Cuerpo* c = new Cuerpo(x, y, vx, vy, masa, radio);
        scene->addItem(c);
        c->setBrush(Qt::cyan);
        cuerpos.append(c);
    }

    QFile archivo("sistema_tabla.txt");
    archivo.open(QIODevice::WriteOnly | QIODevice::Text);
    archivo.close();
    ui->graphicsView->fitInView(scene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void Widget::limpiarTabla()
{
    ui->tablaCuerpos->setRowCount(0);
}

void Widget::agregarCuerpoDesdeInputs()
{
    bool ok[6];
    double x     = ui->inputX->text().toDouble(&ok[0]);
    double y     = ui->inputY->text().toDouble(&ok[1]);
    double masa  = ui->inputMasa->text().toDouble(&ok[2]);
    double radio = ui->inputRadio->text().toDouble(&ok[3]);
    double vx    = ui->inputVx->text().toDouble(&ok[4]);
    double vy    = ui->inputVy->text().toDouble(&ok[5]);

    if (ok[0] && ok[1] && ok[2] && ok[3] && ok[4] && ok[5]) {
        int row = ui->tablaCuerpos->rowCount();
        ui->tablaCuerpos->insertRow(row);
        ui->tablaCuerpos->setItem(row, 0, new QTableWidgetItem(QString::number(x)));
        ui->tablaCuerpos->setItem(row, 1, new QTableWidgetItem(QString::number(y)));
        ui->tablaCuerpos->setItem(row, 2, new QTableWidgetItem(QString::number(masa)));
        ui->tablaCuerpos->setItem(row, 3, new QTableWidgetItem(QString::number(radio)));
        ui->tablaCuerpos->setItem(row, 4, new QTableWidgetItem(QString::number(vx)));
        ui->tablaCuerpos->setItem(row, 5, new QTableWidgetItem(QString::number(vy)));

        // Limpiar entradas
        ui->inputX->clear();
        ui->inputY->clear();
        ui->inputMasa->clear();
        ui->inputRadio->clear();
        ui->inputVx->clear();
        ui->inputVy->clear();
    }
}
