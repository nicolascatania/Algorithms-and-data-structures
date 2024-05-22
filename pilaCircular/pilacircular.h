#ifndef PILACIRCULAR_H_INCLUDED
#define PILACIRCULAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y)((x)>(y)?(y):(x))

typedef struct sNodo{

    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tPila;


void crearPila(tPila*);
int pilaVacia(const tPila*);
int pilaLlena(const tPila*, const void*, unsigned tam);
int ponerEnPila(tPila*, const void*, unsigned tam);
int sacarDePila(tPila*, void*, unsigned tam);
void vaciarPila(tPila*);
int verTope(const tPila*, void*, unsigned tam);


#endif // PILACIRCULAR_H_INCLUDED
