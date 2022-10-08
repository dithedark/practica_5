#ifndef BLOQUES_H
#define BLOQUES_H



#include "generico.h"

class bloques :public QObject , public generico
{
Q_OBJECT
public:
    bloques();

    ~bloques();

    void llamar_proceso();


private:
    QTimer *timer;
    int secuencia=2;
public slots:
    void destruccion();



};

#endif // BLOQUES_H
