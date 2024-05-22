#include "pilaDinamica.h"


#define minimo(X,Y) ((X)<=(Y) ? (X):(Y))

void crearPila(tPila*p){
    *p = NULL;
}

int pilaLlena(const tPila*p, unsigned cantBytes){
    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* dato = malloc(cantBytes);
    free(aux);
    free(dato);

    return aux==NULL || dato==NULL;

}

int apilar(tPila* p, const void*d, unsigned cantBytes){

    tNodo* nue;
    if( (nue=(tNodo*)malloc(sizeof(tNodo)))==NULL || (nue->dato = malloc(cantBytes))==NULL){
        free(nue);
        return 0;
    }
    memcpy(nue->dato,d,cantBytes);
    nue->tamDato= cantBytes;
    nue->sig=*p;
    *p=nue;
    return 1;
}

int verTope(const tPila* p, void* d, unsigned cantBytes){
    if(*p==NULL){
        return 0;
    }
    memcpy(d,(*p)->dato,minimo(cantBytes,(*p)->tamDato));
    return 1;
}

int pilaVacia(const tPila* p){
    return *p==NULL;
}

int desapilar(tPila* p, void* d, unsigned cantBytes){
    tNodo* aux= *p;
    if(aux==NULL){
        return 0;
    }
    *p = aux->sig;
    memcpy(d,aux->dato,minimo(cantBytes,aux->tamDato));
    free(aux->dato);
    free(aux);
    return 1;

}

void vaciarPila(tPila*p){
    tNodo*  aux;
    while(*p){
        aux = *p;
        *p = aux->sig;
        free(aux->dato);
        free(aux);
    }
}

