#include "prota.h"

void prota::reset()
{
    cambio(0,0,112,48);
    select_bloc(3);
    setPos(16*scale_sprite,16*scale_sprite);
}

prota::prota()
{
   reset();
}

void prota::movi_izquierda(int Pbloque1, int Pbloque2)
{
    if(izquierda<2)
    {
        izquierda++;
    }
    else izquierda=0;
    select_bloc(izquierda,0);


    if(Pbloque1 ==9 and Pbloque2 ==9 )
    {
        setPos(x()-mc,y());
    }

}

void prota::movi_abajo(int Pbloque1 , int Pbloque2)
{
    if(abajo<2)
    {


        abajo++;

    }
    else abajo=0;

    select_bloc(abajo+3,0);
    if(Pbloque1 ==9 and Pbloque2 == 9  )
    {
        setPos(x(),y()+mc);
    }

}

void prota::movi_derecha(int Pbloque1 , int Pbloque2)
{
    if(derecha<2)
    {

        derecha++;
    }
    else derecha=0;
    select_bloc(derecha,1);

    if(Pbloque1 == 9 and  Pbloque2 ==9)
    {
        setPos(x()+mc,y());
    }

}

void prota::movi_arriba(int Pbloque1 , int Pbloque2)
{
    if(arriba<2)
    {


        arriba++;

    }
    else arriba=0;
    select_bloc(arriba+3,1);
    if(Pbloque1 == 9 and Pbloque2 == 9)
    {
        setPos(x(),y()-mc);
    }

}

bool prota::muerte()
{
    if(muert<7)
    {
        select_bloc(muert,2);
        muert++;
        bloqueo=false;
        return true;
    }
    else
    {
        bloqueo=true;
        muert=0;
    }

    return false;

}

bool prota::Mbloqueo()
{
    return bloqueo;
}

void prota::Cbloqueo()
{
    if(bloqueo)
    {
        bloqueo=false;
    }
    else
    {
        bloqueo=true;
    }

}
