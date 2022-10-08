#ifndef BOOM_H
#define BOOM_H

#include "generico.h"

class boom:public QObject ,public generico
{
Q_OBJECT
public:
    boom();
    void set_posicion(int posix,int posiy);
    void susecion();


private:
    int  posicionX,posicionY,fase=0;

};
#endif // BOOM_H
