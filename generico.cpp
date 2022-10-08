#include "generico.h"

generico::generico()
{
        img = new QPixmap;
        im_blq = new QPixmap;
        img->load(":/NES_-_Bomberman_-_General_Sprites-removebg-preview.png");


}

generico::~generico()
{
    delete img;
    delete im_blq;
}

void generico::select_bloc(int bl,int y ,bool susti)
{
    type_block = bl;
    if(bl!=9 or ( bl ==9 and susti == false)) *im_blq = img->copy(16*bl,y*16,16,16);

    else im_blq->load(":/fondo.png");
    *im_blq = im_blq->scaled(im_blq->width()*scale_sprite,im_blq->height()*scale_sprite);
    setPixmap(*im_blq);
}

void generico::cambio(int x, int y, int lonx, int lony)
{
    *img = img->copy(x,y,lonx,lony);
}

int generico::bloc()
{

    return type_block;
}
