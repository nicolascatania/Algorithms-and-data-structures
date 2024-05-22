#include "pilacircular.h"


void crearPila(tPila* p)
{
    *p=NULL;
}


int pilaVacia(const tPila* p)
{
    return *p==NULL;
}

int pilaLlena(const tPila* p, const void* elem, unsigned tam)
{
    return 0;
}

int ponerEnPila(tPila* p, const void* elem, unsigned tam)
{

    tNodo* nue;
    nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
    {
        return 0;
    }
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, elem, tam);
    nue->tamInfo = tam;
    if(!(*p))
    {

        nue->sig = nue;
        *p = nue;
    }
    else
    {
        nue->sig = (*p)->sig;
        (*p)->sig = nue;
    }


    return 1;
}


int sacarDePila(tPila* p, void* elem, unsigned tam)
{
    tNodo* aux;
    if(!(*p))
    {
        return 0;
    }

    aux = (*p)->sig;

    memcpy(elem, aux->info, MIN(tam, aux->tamInfo));

    if(aux == *p)
    {
        *p=NULL;
    }
    else
    {
        (*p)->sig = aux->sig;
    }


    free(aux->info);
    free(aux);

    return 1;
}

void vaciarPila(tPila* p)
{

    tNodo* aux;
    while(*p)
    {
        aux = (*p)->sig;
        if(aux == *p)
        {
            *p = NULL;
        }
        else
        {
            (*p)->sig = aux->sig;
        }
        free(aux->info);
        free(aux);
    }

}


int verTope(const tPila* p, void* elem, unsigned tam)
{
    if(!(*p))
    {
        return 0;
    }

    memcpy(elem, (*p)->sig->info, MIN(tam,(*p)->sig->tamInfo));
    return 1;

}
