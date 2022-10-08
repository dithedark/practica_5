#ifndef BOMBA_H
#define BOMBA_H

#include "generico.h"


class bomba: public QObject , public generico
{
Q_OBJECT
public:
    bomba();
    ~bomba();

    void secuencia(int x ,int y);
    bool fin();
    int coordenadas(bool cor);

private:
    int corx,cory;
    int rutina=0, ciclo =0;
    bool salir=true;
    QTimer *timer;
public slots:
    void animacion();
};

#endif // BOMBA_H
