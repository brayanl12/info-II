#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}


//INICIAR JUEGO
void Widget::on_jugar_clicked()
{
    Juego *juego= new Juego;
    juego->setAttribute(Qt::WA_DeleteOnClose); // S borra solo al cerrarse
    juego->show();
    hide(); //oculta el menu
}

//CERRAR MENÚ
void Widget::on_cerrar_clicked()
{
    close();
}


