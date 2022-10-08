#include "bomba.h"

bomba::bomba()
{
    timer =new QTimer;
    cambio(0,3*16,2*16);
    connect(timer,SIGNAL(timeout()),this,SLOT(animacion()));

}

bomba::~bomba()
{
    delete timer;
}

void bomba::secuencia(int x, int y)
{
    corx=x;
    cory=y;
    ciclo=0;
    select_bloc(0);
    setPos(x,y);
    timer->start(300);
    salir=false;





}

bool bomba::fin()
{
    return salir;
}

int bomba::coordenadas(bool cor)
{
    if(cor==false)
    {
        return corx;
    }
    return cory;
}

void bomba::animacion()
{

    if(rutina<2)
    {
        select_bloc(rutina);
        rutina++;
    }
    else
    {
        rutina=0;
        ciclo++;


        if(ciclo == 3  )
        {
            salir=true;
            select_bloc(9);
            timer->stop();
        }
    }


}

