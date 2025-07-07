#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include "cuerpo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void actualizar();
    void cargarSistema1();
    void cargarSistema2();
    void crearSistemaDesdeTabla();
    void limpiarTabla();
    void agregarCuerpoDesdeInputs();

private:
    Ui::Widget *ui;
    QGraphicsScene *scene;
    QTimer *timer;
    QList<Cuerpo*> cuerpos;

    int sistemaActivo;

    void guardarPosiciones();
    void limpiarSistema();
};

#endif // WIDGET_H
