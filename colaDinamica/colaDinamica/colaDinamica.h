#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(X,Y)(((X)>(Y))?(Y):(X))


/*typedef struct sNodo{

    void* info;
    unsigned tamDato;
    struct sNodo* sig;
}tNodo;


typedef struct {
    tNodo* pri;
    tNodo* ult;
}tCola;


void crearCola(tCola* cola);
int colaVacia(const tCola* cola);
int colaLlena(const tCola* cola, unsigned tamElem);
int encolar(tCola* cola, const void* elem, unsigned tamElem);
int desencolar(tCola* cola, void* buffer, unsigned tamElem);
void vaciarCola(tCola* cola);
int verPrimero(const tCola* cola, void* buffer, unsigned tamElem);*/

typedef struct sNodo
{
    unsigned tam;
    void * dato;
    struct sNodo * sig;

}tNodo;

typedef struct sCola
{
    tNodo * prim;
    tNodo * ult;
}tCola;

void crearCola(tCola * cola);
int colaVacia(const tCola * cola);
int colaLlena(const tCola * cola, unsigned tam);
int encolar(tCola * cola, const void * dato, unsigned tam);
int desencolar(tCola * cola,  void * dato, unsigned tam);
int verTope (const tCola * cola, void * dato, unsigned tam);
void vaciarCola(tCola * cola);

#endif // COLADINAMICA_H_INCLUDED
