#include "boom.h"

boom::boom()
{
    cambio(0,4*16,16*10,16*10);
    select_bloc(1,1);
    setPos(-1000,-1000);


}

void boom::set_posicion(int posix,int posiy)
{
    posicionX=posix;
    posicionY=posiy;
}

void  boom::susecion()
{
    switch (fase)
    {
        case 0:

            select_bloc(posicionX,posicionY);
            break;

        case 1:
            select_bloc(posicionX+5,posicionY,false);
            break;

        case 2:
            select_bloc(posicionX,posicionY+5);

            break;

        case 3:

            select_bloc(posicionX+5,posicionY+5,false);
            fase=-1;

            break;
    }

    fase++;

}


