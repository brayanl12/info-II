#include "cuerpo.h"
#include <cmath>

const double G = 1.0; // Constante gravitacional unificada como dice la guía

Cuerpo::Cuerpo(double x, double y, double vx, double vy, double masa, double radio)
    : masa(masa), radio(radio), vx(vx), vy(vy), fx(0), fy(0)
{
    // Dibujo del cuerpo: círculo centrado
    setRect(-radio, -radio, 2 * radio, 2 * radio);
    setPos(x, y);
    setBrush(Qt::blue); // Color por defecto (lo puedes cambiar en main)
}

void Cuerpo::resetFuerza()
{
    fx = 0;
    fy = 0;
}

void Cuerpo::actualizarFuerza(Cuerpo* otro)
{
    double dx = otro->x() - x();
    double dy = otro->y() - y();
    double dist = std::sqrt(dx * dx + dy * dy) + 1e-5;  // evitar división por 0

    double fuerza = (G * masa * otro->masa) / (dist * dist);
    fx += fuerza * dx / dist;
    fy += fuerza * dy / dist;
}

void Cuerpo::mover(double dt)
{
    double ax = fx / masa;
    double ay = fy / masa;

    vx += ax * dt;
    vy += ay * dt;

    double nuevoX = x() + vx * dt;
    double nuevoY = y() + vy * dt;

    setPos(nuevoX, nuevoY);
}
