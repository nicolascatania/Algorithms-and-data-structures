#include "listaCircular.h"

void crearLista(tLista *l)
{
    *l = NULL;
}


int listaLLena(const tLista* l)
{
    return 0;
}

int listaVacia(const tLista *l)
{
    return *l==NULL;
}

int ponerEnLista(tLista *l, void* elem, unsigned tam)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
    if (!nue)
    {
        return ERR;
    }
    nue->info = malloc(tam);
    if (!nue->info)
    {
        free(nue);
        return ERR;
    }
    memcpy(nue->info, elem, tam);
    nue->tamInfo = tam;

    if (*l == NULL)
    {
        nue->sig = nue;
    }
    else
    {
        nue->sig = (*l)->sig;
        (*l)->sig = nue;
    }

    *l = nue;

    return OK;
}

int insertarOrdenado(tLista* l,const void* elem, unsigned tam,int(*cmp)(const void*, const void*), void (*acumular)(void**, unsigned*, const void*, unsigned))
{
    tNodo* nue, *act = *l;

    while(act->sig!=*l && cmp(elem,(act)->info)>0)
    {
        act = act->sig;
    }
    if(act && (cmp(elem,act->info)==0))
    {
        if(acumular)
        {
            acumular(&act->info, &act->tamInfo, elem, tam);
            return DUPLICADO;
        }
    }
    if(((nue = (tNodo*)malloc(sizeof(tNodo)))==NULL) || (((nue->info)= malloc(tam))==NULL))
    {
        free(nue);
        return ERR;
    }
    memcpy(nue->info,elem,tam);
    nue->tamInfo = tam;
    nue->sig = act;
    *l = nue;
    return OK;
}
void mostrarLista(const tLista* l, void (*mostrar)(const void*))
{
    if (*l == NULL)
    {
        return;
    }

    tNodo* act = (*l)->sig;

    do
    {
        mostrar(act->info);
        act = act->sig;
    }
    while (act != (*l)->sig);
}


void vaciarLista(tLista* l)
{
    tNodo* act = (*l)->sig;
    tNodo* aux;

    if (*l == NULL)
    {
        return;
    }

    while (act != *l)
    {
        aux = act;
        act = act->sig;
        free(aux->info);
        free(aux);
    }

    free(act->info);
    free(act);

    *l = NULL;
}

