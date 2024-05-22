#ifndef LISTACIRCULAR_H_INCLUDED
#define LISTACIRCULAR_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define DUPLICADO 2
#define OK 1
#define ERR 0

typedef struct sNodo{
    void* info;
    unsigned tamInfo;
    struct sNodo* sig;
}tNodo;

typedef tNodo* tLista;


void crearLista(tLista* l);
int listaLLena(const tLista* l);
int listaVacia(const tLista* l);
int ponerEnLista(tLista* l, void* elem, unsigned tam);
void ordenarLista(tLista* l, int (*cmp)(const void*, const void*));
int insertarOrdenado(tLista *l,const void* elem, unsigned tam, int (*cmp)(const void*, const void*), void (*acumular)(void**, unsigned*, const void*, unsigned));
void vaciarLista(tLista* l);
void mostrarLista(const tLista* l, void(*mostrar)(const void*));
int eliminarXPosicion(tLista *l, void* buffer, unsigned tam, int (*cmp)(const void*, const void*));
int filter(tLista* l,void* parametro, int filtrado(const void*, const void*));

#endif // LISTACIRCULAR_H_INCLUDED
