#ifndef GENERICO_H
#define GENERICO_H


#include <QGraphicsPixmapItem>
#include "macros.h"
#include <QTimer>
#include <QObject>



class generico : public QGraphicsPixmapItem
{
public:
    generico();
    ~generico();
    void select_bloc(int bl,int y=0,bool susti=true);
    void cambio(int x=48, int y=48 ,int lonx=144,int lony=16);
    int bloc();

private:
    int type_block;
    QPixmap *img, *im_blq;
};

#endif // GENERICO_H
