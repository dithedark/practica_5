#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "generico.h"
#include <stdlib.h>
#include <time.h>

class enemigo:public generico
{
//Q_OBJECT
public:
    enemigo();
    ~enemigo();
    void movimiento(int direccion);
    bool muerte();

private:
    int secuencia=0;



};

#endif // ENEMIGO_H
