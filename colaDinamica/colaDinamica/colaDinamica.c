#include "colaDinamica.h"

/*void crearCola(tCola* cola)
{

    cola->ult=NULL;
    cola->pri=NULL;

}

int colaVacia(const tCola* cola)
{

    return cola->pri==NULL;

}

int colaLlena(const tCola* cola, unsigned tamElem)
{

    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tamElem);
    free(aux);
    free(info);

    return aux==NULL || info == NULL;

    return 0;

}


int encolar(tCola* cola,const void* elem, unsigned tamElem)
{

    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));

    if(!aux)
    {
        return 0;
    }

    aux->info = malloc(tamElem);

    if(!aux->info)
    {
        free(aux);
        return 0;
    }

    memcpy(aux->info, elem, tamElem);

    aux->tamDato = tamElem;

    aux->sig=NULL;

    if(cola->ult)
    {
        (cola->ult)->sig = aux;
    }
    else
    {
        cola->pri = aux;
    }

    cola->ult = aux;

    return 1;

}


int desencolar(tCola* cola, void* buffer, unsigned tamElem)
{

    tNodo* aux = cola->pri;
    if(!aux)
    {
        return 0;
    }

    cola->pri = aux->sig;

    memcpy(buffer,aux->info,MINIMO(aux->tamDato, tamElem));

    free(aux->info);

    free(aux);

    if(cola->pri==NULL)
    {
        cola->ult==NULL;
    }


    return 1;


}


void vaciarCola(tCola* cola)
{

    tNodo* aux;

    while(cola->pri)
    {
        aux = cola->pri;
        cola->pri = aux->sig;
        free(aux->info);
        free(aux);
    }

    cola->ult = NULL;

}


int verPrimero(const tCola* cola, void* buffer, unsigned tamElem)
{

    if(cola->pri==NULL)
    {
        return 0;
    }
    memcpy(buffer,cola->pri->info, MINIMO(cola->pri->tamDato,tamElem));
    return 1;

}*/
void crearCola(tCola * cola)
{
    cola->prim = NULL;
    cola->ult = NULL;
}

int colaVacia(const tCola * cola)
{
    return cola->prim == NULL;
}

int colaLlena(const tCola * cola, unsigned tam)
{
    tNodo * temp = malloc(sizeof(tNodo));

    if(!temp)
        return 1;

    temp->dato = malloc(sizeof(tam));

    if(!temp->dato)
    {
        free(temp);
        return 1;
    }

    free(temp->dato);
    free(temp);

    return 0;
}

int encolar(tCola * cola, const void * dato, unsigned tam)
{
    tNodo * nue = malloc(sizeof(tNodo));

    if(!nue)
        return 0;

    nue->dato = malloc(sizeof(tam));

    if(!nue->dato)
    {
        free(nue);
        return 0;
    }

    nue->tam = tam;
    memcpy(nue->dato, dato, tam);
    nue->sig = NULL;

    if(cola->prim == NULL)
    {
        cola->prim = nue;
        cola->ult = nue;

    }
    else
    {
        cola->ult->sig = nue;

    }


    cola->ult = nue;

    return 1;

}

int desencolar(tCola * cola,  void * dato, unsigned tam)
{
    tNodo * elim;

    if(!cola->prim)
        return 0;

    elim = cola->prim;

    cola->prim = elim->sig;

    memcpy(dato, elim->dato, MINIMO(tam, elim->tam));

    free(elim->dato);
    free(elim);

    return 1;
}

int verTope (const tCola * cola, void * dato, unsigned tam)
{

    if(!cola->prim)
        return 0;

    memcpy(dato, cola->prim->dato, MINIMO(tam, cola->prim->tam));

    return 1;


}

void vaciarCola(tCola * cola)
{
    tNodo * elim = cola->prim;

    while(elim)
    {
        cola->prim = elim->sig;
        free(elim->dato);
        free(elim);
        elim = cola->prim;
    }

    cola->ult = NULL;
}

