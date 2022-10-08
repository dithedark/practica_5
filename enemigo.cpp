#include "enemigo.h"

enemigo::enemigo()
{
    //timer= new QTimer;
    cambio(0,15*16,160);
    select_bloc(0);

    //connect(timer,SIGNAL(timeout()),this,SLOT(movimiento()));
    setPos(((( 2 + rand() % (15 - 2))*2)-1)* (scale_sprite*16), (4 + rand() % ((ancho-2) +1 - 4)) * (scale_sprite*16));



}

enemigo::~enemigo()
{
    //delete timer;
}


void enemigo::movimiento(int direccion)
{
    if(secuencia<5)
    {
        secuencia++;

    }
    else secuencia=0;

    select_bloc(secuencia,0);

    switch (direccion)
    {
        //direccion= 1 + rand() % (4 +1 - 1);
    case 1:
        setPos(x()-((16*scale_sprite)/4),y());
        break;
    case 2:
        setPos(x(),y()+((16*scale_sprite)/4));
        break;
    case 3:
        setPos(x()+((16*scale_sprite)/4),y());
        break;
    case 4:
        setPos(x(),y()-((16*scale_sprite)/4));
        break;

    default:
        break;
    }
}

bool enemigo::muerte()
{
    if(secuencia>= 6 and secuencia<9)
    {
        secuencia++;
    }
    else
    {
        secuencia=6;
    }

    select_bloc(secuencia,0,false);

    if(secuencia== 9)
    {
        return false;
    }
    return true;
}





