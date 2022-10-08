#ifndef JUEGO_H
#define JUEGO_H


#include <QKeyEvent>
#include "bloques.h"
#include "prota.h"
#include <cstdlib>
#include "bomba.h"
#include "enemigo.h"
#include "boom.h"


class juego :  public QGraphicsScene
{
Q_OBJECT
public:
    juego();
    ~juego();
    void movimiento();
    void keyPressEvent(QKeyEvent *i);




private:
    int select_bloc(int i, int j),titileo=0,vidas=3,parpadeo=0,tamBomba=0,kill=0,conmalos=0;
    bool aleatorio(),*horizon,*verti,desaparecer=false;
    prota *personaje;
    float p = 0.3;
    bloques *bl[largo][ancho];
    bomba *explocion ;
    QTimer *romper,*Mmalo, *muerte,*revi,*fin,*muerteMalo;
    QVector<enemigo*> malitos;
    enemigo desaparece;
    boom *booom;


private slots:
    void organizacion();
    void se_mueve_el_malo();
    void Smuerte();
    void revivir();
    void finalizar();
    void muerteMal();


};

#endif // JUEGO_H
