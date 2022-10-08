#include "juego.h"

juego::juego()
{


    // cambiamos de color el fondo de la esena
    //de esta forma cuando cambiemos de bloques
    //  no tengo manchones blancos
    QBrush *p = new QBrush;
    QColor l;
    booom = new boom[5];
    l.setRgb(40,156,68);
    p->setColor(l);
    p->setStyle(Qt::BrushStyle::SolidPattern);
    setBackgroundBrush(*p);

    //definimos todas las memorias dinamicas que vamos
    //a usar para todo el juego
    horizon= new bool[num_enemigos];
    verti=new bool[num_enemigos];
    personaje = new prota;
    explocion=new bomba;
    romper= new QTimer;
    muerte = new QTimer;
    revi= new QTimer;
    fin= new QTimer;
    muerteMalo= new QTimer;
    Mmalo = new QTimer;


    //iniciamos semilla para secuencia seudoaleatorio
    srand(time(NULL));

    // añadimos todos los bloques del mapa a la esena en forma de
    // matriz
    setSceneRect(0,0,16*scale_sprite*largo,16*scale_sprite*ancho);
    for(int i=0;i<largo;i++){

        for(int j=0;j<ancho;j++)
        {
            bl[i][j] = new bloques;

            bl[i][j]->cambio();
            bl[i][j]->select_bloc(select_bloc(i,j));


            bl[i][j]->setPos(16*i*scale_sprite,16*j*scale_sprite);
            addItem(bl[i][j]);
        }
    }
    addItem(explocion);
    for(int i =0; i<num_enemigos; i++)
    {
        malitos.push_back(new enemigo);
        addItem(malitos[i]);
    }

    addItem(personaje);

    connect(romper,SIGNAL(timeout()),this,SLOT(organizacion()));
    connect(Mmalo,SIGNAL(timeout()),this,SLOT(se_mueve_el_malo()));
    connect(muerte,SIGNAL(timeout()),this,SLOT(Smuerte()));
    connect(revi,SIGNAL(timeout()),this,SLOT(revivir()));
    connect(fin,SIGNAL(timeout()),this,SLOT(finalizar()));
    connect(muerteMalo,SIGNAL(timeout()),this,SLOT(muerteMal()));

    Mmalo->start(350);
}

juego::~juego()
{
    for(int i=0;i<largo;i++)
    {
        for(int j=0;j<ancho;j++) delete bl[i][j];
    }
    delete personaje;
    delete explocion;
    delete romper;
    delete malitos[num_enemigos];
    delete horizon;
    delete verti;
    delete booom;
    delete muerteMalo;

}


int juego::select_bloc(int i, int j)
{
   int bl=9;


   if(j==0 || j==ancho-1 || i==0 || i==largo-1 || (i%2==0 && j%2==0)) bl = 0;
   else if(aleatorio() && !((i==1 && j==1) || (i==2 && j==1) || (i==1 && j==2))) bl = 1;
   return bl;
}

bool juego::aleatorio()
{
    return rand()<=p*(RAND_MAX+1)-1;
}


void juego::se_mueve_el_malo()
{
    int tam=(16*scale_sprite);

    for (auto var = 0; var < num_enemigos-conmalos; ++var)
    {


            if(bl[int(malitos[var]->x()-1)/tam][int(malitos[var]->y()/tam)]->bloc() ==9 and bl[int(malitos[var]->x()-1)/tam][(int(malitos[var]->y()+tam-1)/tam)]->bloc() ==9 and horizon[var] ==false )
            {
                malitos[var]->movimiento(1);
            }
            else if(bl[int((malitos[var]->x())/tam)][int(malitos[var]->y()+tam+1)/tam]->bloc() ==9 and bl[int(malitos[var]->x()+tam-1)/tam][int(malitos[var]->y()+tam+1)/tam]->bloc() ==9 and verti[var] ==false )
            {
                malitos[var]->movimiento(2);
            }
            else if(bl[int(malitos[var]->x()+tam+1)/tam][int(malitos[var]->y())/tam]->bloc() ==9 and bl[int(malitos[var]->x()+tam+1)/tam][int(malitos[var]->y()+tam-1)/tam]->bloc()==9 and horizon[var] == true )
            {
                malitos[var]->movimiento(3);
            }
            else if ( bl[int(malitos[var]->x())/tam][int(malitos[var]->y()-1)/tam]->bloc()==9 and bl[int(malitos[var]->x()+tam-1)/tam][int(malitos[var]->y()-1)/tam]->bloc() == 9 and verti[var] == true )
            {
                malitos[var]->movimiento(4);
            }
            else
            {
                malitos[var]->movimiento(5);
                if(horizon[var] ==false)
                {
                    horizon[var]= true;
                    verti[var]=true;
                }
                else
                {
                    horizon[var]= false;
                    verti[var]=false;

                }

            }
            if(malitos[var]->collidesWithItem(personaje) and personaje->Mbloqueo() ==true)
            {

                muerte->start(200);
            }
            for(int e=0; e < 5;e++)
            {
               if(malitos[var]->collidesWithItem(&booom[e]))
                {
                    kill=var;
                    desaparece.setPos(malitos[var]->x(),malitos[var]->y());
                    removeItem(malitos[var]);
                    malitos.remove(var);
                    addItem(&desaparece);
                    muerteMalo->start(200);
                    conmalos++;
                    break;

                }
            }

    }
}

void juego::Smuerte()
{
    personaje->muerte();
    if(personaje->Mbloqueo() )
    {

        muerte->stop();
        personaje->reset();
        personaje->Cbloqueo();
        revi->start(100);
    }

}

void juego::revivir()
{
    if(parpadeo < 8)
    {
        if(desaparecer)
        {
            addItem( personaje);
            desaparecer=false;
            revi->stop();
            revi->start(100);
        }
        else
        {
            removeItem(personaje);
            desaparecer=true;
            revi->stop();
            revi->start(100);
        }
        parpadeo++;
     }
     else
    {
        revi->stop();
        parpadeo=0;
        personaje->Cbloqueo();
    }


}


void juego::organizacion()
{
    int tam=(16*scale_sprite);
    bl[explocion->coordenadas(false)/tam][(explocion->coordenadas(true)/tam)]->select_bloc(7);

    if(explocion->fin() )
    {
        //esconde la bomba
        bl[explocion->coordenadas(false)/tam][(explocion->coordenadas(true)/tam)]->select_bloc(9);

        //analiza y si es necesario lo cambia izquierda
        bl[(explocion->coordenadas(false)/tam)-1][(explocion->coordenadas(true)/tam)]->llamar_proceso();

        bl[(explocion->coordenadas(false)/tam)][(explocion->coordenadas(true)/tam)-1]->llamar_proceso();

        bl[(explocion->coordenadas(false)/tam)+1][(explocion->coordenadas(true)/tam)]->llamar_proceso();

        bl[(explocion->coordenadas(false)/tam)][(explocion->coordenadas(true)/tam)+1]->llamar_proceso();
        romper->stop();


        //booom=new boom [5+(4*tamBomba)];


        for (int var = 0; var < 5; ++var)
        {

            addItem(&booom[var]);

        }

        //addItem(&booom[4]);

        fin->start(130);

    }


}


void juego::finalizar()
{
    if(tamBomba<5)
    {
        if(bl[explocion->coordenadas(false)/(16*scale_sprite)][(explocion->coordenadas(true)/(16*scale_sprite))]->bloc()==9)
        {
            //centro
            booom[0].set_posicion(2,2);
            booom[0].setPos(explocion->coordenadas(false),explocion->coordenadas(true));

        }


        if(bl[(explocion->coordenadas(false)/(16*scale_sprite))-1][(explocion->coordenadas(true)/(16*scale_sprite))]->bloc()==9)
        {
            //esquina izquierda
            booom[1].set_posicion(0,2);
            booom[1].setPos(explocion->coordenadas(false)-(16*scale_sprite),explocion->coordenadas(true));

        }

        if(bl[explocion->coordenadas(false)/(16*scale_sprite)][(explocion->coordenadas(true)/(16*scale_sprite))-1]->bloc()==9)
        {
            //esquina superios
            booom[2].set_posicion(2,0);
            booom[2].setPos(explocion->coordenadas(false),explocion->coordenadas(true)-(16*scale_sprite));

        }

        if(bl[explocion->coordenadas(false)/(16*scale_sprite)][(explocion->coordenadas(true)/(16*scale_sprite))+1]->bloc()==9)
        {
            //esquina inferior
            booom[3].set_posicion(2,4);
            booom[3].setPos(explocion->coordenadas(false),explocion->coordenadas(true)+(16*scale_sprite));

        }

        if(bl[explocion->coordenadas(false)/(16*scale_sprite)+1][(explocion->coordenadas(true)/(16*scale_sprite))]->bloc()==9)
        {
            //esquina derecha
            booom[4].set_posicion(4,2);
            booom[4].setPos(explocion->coordenadas(false)+(16*scale_sprite),explocion->coordenadas(true));

        }

        for(int i=0 ; i<5 ;++i)
        {
            booom[i].susecion();
        }
        tamBomba++;


    }
    else
    {
        for(int i=0 ; i<5 ;++i)
        {
            removeItem(&booom[i]);
            booom[i].setPos(-1000,-1000);
        }

        tamBomba=0;
        fin->stop();
    }
    for (int var = 0; var < 5; ++var)
    {
        if(booom[var].collidesWithItem(personaje))
        {
            muerte->start(200);
            break;
        }
    }
}

void juego::muerteMal()
{
    if(desaparece.muerte());
    else
    {
        removeItem(&desaparece);
        muerteMalo->stop();
    }


}

void juego::keyPressEvent(QKeyEvent *i)
{

    const int e=i->key(),tam=(16*scale_sprite);

    if(personaje->Mbloqueo())
    {
        if(e== Qt::Key_A)
        {
            // se usa la formula donde tenemos la posicion actual de la esquina superior y dependiendo del punto que queramos ver la usamos
            //en este caso el punto de abajo izquierdo seria x= (tamaño de la imagen+posicion-1)/tam el menos uno es para que no tome el bloque siguente si no es bloque actual
            //hay ocaciones que usamos el "1" para que analice el bloque proximo
            personaje->movi_izquierda(bl[int(personaje->x()-1)/tam][int(personaje->y()/tam)]->bloc(),bl[int(personaje->x()-1)/tam][(int(personaje->y()+tam-1)/tam)]->bloc());

        }
        if(e== Qt::Key_S)
        {
            personaje->movi_abajo(bl[int(personaje->x())/tam][int(personaje->y()+tam+1)/tam]->bloc(),bl[int(personaje->x()+tam-1)/tam][int(personaje->y()+tam+1)/tam]->bloc());
        }
        if(e== Qt::Key_D)
        {
            personaje->movi_derecha(bl[int(personaje->x()+tam+1)/tam][int(personaje->y())/tam]->bloc(),bl[int(personaje->x()+tam+1)/tam][int(personaje->y()+tam-1)/tam]->bloc());
        }
        if(e== Qt::Key_W)
        {
            personaje->movi_arriba(bl[int(personaje->x())/tam][int(personaje->y()-1)/tam]->bloc(),bl[int(personaje->x()+tam-1)/tam][int(personaje->y()-1)/tam]->bloc());
        }
        if(e == Qt::Key_P)
        {
            if(explocion->fin())
            {
                explocion->secuencia(int((personaje->x()+(tam/2))/tam)*tam,int((personaje->y()+(tam/2))/tam)*tam);
                romper->start(200);
            }

        }
    }
}







