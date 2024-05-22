#ifndef COLACIRCULAR_H_INCLUDED
#define COLACIRCULAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y)((x)>(y)?(y):(x))

typedef struct sNodo{

    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tCola;

void crearCola(tCola*);
int colaLlena(const tCola*, void*, unsigned);
int colaVacia(const tCola*);
int encolar(tCola*, void*, unsigned);
int desencolar(tCola*, void*, unsigned);
int verPrimero(const tCola*, void*, unsigned);
void vaciarCola(tCola*);

#endif // COLACIRCULAR_H_INCLUDED
