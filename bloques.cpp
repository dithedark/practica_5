#include "bloques.h"

bloques::bloques()
{
    timer= new QTimer;
    connect(timer,SIGNAL(timeout()),this,SLOT(destruccion()));
}

bloques::~bloques()
{
    delete timer;
}

void bloques::llamar_proceso()
{
    if(bloc()!=0 and bloc() !=9)
        timer->start(100);
}

void bloques::destruccion()
{
    if(secuencia<8)
        select_bloc(secuencia);
    else
    {
        select_bloc(9);
        timer->stop();
    }
    secuencia++;
}




