#ifndef PROTA_H
#define PROTA_H

#include <QGraphicsScene>
#include "generico.h"

class prota: public generico
{
private:
    int mc=(16*scale_sprite)/4;
    int8_t arriba=0,abajo=0,izquierda=0,derecha=0,muert=0;
    bool bloqueo=true;


public:
    prota();
    void movi_izquierda(int Pbloque1 , int Pbloque2=9);
    void movi_abajo(int Pbloque1 , int Pbloque2=9);
    void movi_derecha(int Pbloque1 , int Pbloque2=9);
    void movi_arriba(int Pbloque1 , int Pbloque2=9);

    bool Mbloqueo();
    void Cbloqueo();


    bool muerte();

    void reset();




};

#endif // PROTA_H
