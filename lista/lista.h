#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MINIMO(x,y)((x)>(y)?(y):(x))
#define DUPLICADO -5

#define LISTA_VACIA -1
#define ERROR_MEMORIA -2
#define n_CERO -3
#define FALTAN_ULTIMOS_N_NODOS -4

typedef struct sNodo{

    void* info;
    unsigned tamInfo;
    struct sNodo* sig;

}tNodo;

typedef tNodo* tLista;



void crearLista(tLista*);
int listaVacia(const tLista*);
int listaLlena(const tLista*, unsigned);
int ponerEnListaUltimo(tLista*,const void*, unsigned);
int ponerEnListaPrimero(tLista*, const void*, unsigned);
int sacarUltimoLista(tLista*, void*, unsigned);
int sacarPrimerLista(tLista*, void*, unsigned);
int verPrimeroLista(const tLista*, void*, unsigned);
int verUltimoLista(const tLista*, void*, unsigned);
void vaciarLista(tLista*);

void* buscarInfoPorClave(const tLista* ,const void*, unsigned, int(*cmp)(const void*, const void*));
tLista* buscarNodoPorClave(const tLista*, const void*, unsigned, int(*cmp)(const void*, const void*));//puede eliminar el elemento presente en sig, lo que retorna *lista, y linkear a otro nodo desreferenciando sig

int ordenarLista(tLista*, int (*cmp)(const void*, const void*));
tNodo* buscarMenor(tLista*, int(*cmp)(const void*, const void*));
int insertarEnOrden(tLista* lista, int(*cmp)(const void*, const void*), const void* elem, unsigned tam, int(*acumular)(void**, unsigned*, const void*, unsigned));

int eliminarPrimeraOcurrenciaClave(tLista*, const void*, int (*cmp)(const void*, const void*));
int eliminarTodasOcurrenciasClave(tLista*, const void*, int (*cmp)(const void*, const void*));
int eliminarUltimaOcurrenciaClave(tLista*, const void*, int (*cmp)(const void*, const void*));
int eliminarNoDuplicados(tLista*, int(*cmp)(const void*, const void*), void (*accion)(tNodo*));
int eliminarNUltimosNodos(tLista*, int);
int eliminarNUltimosNodosRecursiva(tLista* lista, int* n);

int insertarEnPosicion(tLista*, const void*, unsigned, int);
int EliminarEnPosicion(tLista*, int); //si pos >cantNodos, elimina la ultima posicion.


int insertarDespuesClaveNNodos(tLista*, const void*, const void* , unsigned, int (*cmp)(const void*, const void*), int);
int insertarDespuesClaveNNodosV2(tLista*, const void*, const void* , unsigned, int (*cmp)(const void*, const void*), int);
int eliminarDespuesClaveNNodos(tLista*, const void*, int (*cmp)(const void*, const void*), int);


int mostrarLista(const tLista*, void(*mostrar)(const void*, FILE*), FILE*);


void mapC(tLista*, void (*mapeo)(void*));
tLista mapPy(tLista*, void(*mapeo)(void*));

void filterC(tLista*, void*, int(*cmp)(const void*, const void*));
tLista filterPy(tLista*, void*, int(*cmp)(const void*, const void*));

void reduce(tLista*, void*, void(*reduccion)(const void*, void*));

#endif // LISTA_H_INCLUDED
