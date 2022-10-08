#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <QGraphicsPixmapItem>
#include "macros.h"
#include "bloques.h"

class personaje: public QGraphicsPixmapItem
{
public:
    personaje();
    ~personaje();


private:

    QPixmap *copia,*movimiento;
    bloques *personaj;

};

#endif // PERSONAJE_H
