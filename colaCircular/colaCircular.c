#include "colaCircular.h"



void crearCola(tCola* c)
{
    *c = NULL;
}
int colaLlena(const tCola* c, void* elem, unsigned tam)
{
    return 0;
}
int colaVacia(const tCola* c)
{
    return *c==NULL;
}
int encolar(tCola* c, void* elem, unsigned tam)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));
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

    memcpy(nue->info,elem,tam);
    nue->tamInfo = tam;

    if(!*c)
    {
        nue->sig = nue;
    }
    else
    {
        nue->sig = (*c)->sig;
        (*c)->sig = nue;
    }
    *c= nue;
    return 1;
}
int desencolar(tCola* c, void* elem, unsigned tam){
    tNodo* aux;
    if(!*c){
        return 0;
    }
    aux = (*c)->sig;
    memcpy(elem, aux->info,MIN(tam,aux->tamInfo));
    if(aux==*c){
        *c=NULL;
    }
    else{
        (*c)->sig = aux->sig;
    }

    free(aux->info);
    free(aux);
    return 1;

}
int verPrimero(const tCola* c, void* elem, unsigned tam){

    if(!*c){
        return 0;
    }

    memcpy(elem,(*c)->sig->info, MIN((*c)->sig->tamInfo,tam));

    return 1;
}
void vaciarCola(tCola* c){
    tNodo* aux;
    while(*c){
        aux = (*c)->sig;
        if(*c==aux){
            *c=NULL;
        }
        else{
            (*c)->sig = aux->sig;
        }
        free(aux->info);
        free(aux);
    }

}
