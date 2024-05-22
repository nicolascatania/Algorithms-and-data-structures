#ifndef LISTADOBLE_H_INCLUDED
#define LISTADOBLE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUPLICADO 2

typedef struct sNodo{

    void* info;
    unsigned tamInfo;
    struct sNodo *sig, *ant;

}tNodo;


//este puntero apunta siempre al ultimo nodo INSERTADO
typedef tNodo* tLista;

void crearLista(tLista* lista);
int vaciarLista(tLista* lista);
int listaVacia(const tLista* lista);
int listaLlena(const tLista* lista, unsigned tam);
int insertarAlFinal(tLista* lista, const void* elem, unsigned tam);
int insertarAlComienzo(tLista* lista, const void* elem, unsigned tam);
int mostrarIzqDer(const tLista* lista, void(*mostrar)(const void*));
int mostrarDerIzq(const tLista* lista, void(*mostrar)(const void*));
int insertarEnOrden(tLista* lista, const void* elem, unsigned tam, int(*cmp)(const void*, const void*), void (*acumular)(void**, unsigned*, const void*, unsigned));
void OrdenarLista(tLista* lista, int(*cmp)(const void*, const void*));
int eliminarPorClave(tLista* lista, void* elem, unsigned tam, int(*cmp)(const void*, const void*));
tLista* buscarPorClave_ord(tLista* lista, void* clave, int(*cmp)(const void*, const void*));
tLista* buscarPorClave_desord(tLista* lista, void* clave, int(*cmp)(const void*, const void*));
int eliminarClaves(tLista* lista, void* clave, int (*cmp)(const void*, const void*));
void resumirOcurrencias(tLista* lista, int (*cmp)(const void*, const void*), void (*resumir)(void**, unsigned*,const void*, unsigned));
void filter(tLista* l,const void* f, int (*filtro)(const void*, const void*));
#endif // LISTADOBLE_H_INCLUDED
