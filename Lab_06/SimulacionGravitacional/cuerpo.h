#ifndef CUERPO_H
#define CUERPO_H

#include <QGraphicsEllipseItem>
#include <QBrush>

class Cuerpo : public QGraphicsEllipseItem
{
public:
    Cuerpo(double x, double y, double vx, double vy, double masa, double radio);

    void actualizarFuerza(Cuerpo* otro);
    void mover(double dt);
    void resetFuerza();

    double getX() const { return x(); }
    double getY() const { return y(); }

private:
    double masa;
    double radio;
    double fx, fy;
    double vx, vy;
};

#endif // CUERPO_H
