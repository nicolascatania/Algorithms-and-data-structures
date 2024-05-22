#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "listaDoble.h"
#include "utilidades.h"

#define ARCHMAESTRO "maestro.bin"
#define ARCHMOVIMIENTOS "movimientos.txt"



typedef struct{
    char cod;
    int idx;
}tIndice;

typedef struct{
    char codProd;
    int cant;
    char tipoOp;
}tProducto;

void mostrarProdIndice(const void*);
void mostrarProducto(const void*);
int genMaestroYMovimientos();
int obtenerIndices(const char*, tLista*);
int actualizarMaestro(const char*, const char*, tLista*);
int mostrarMaestro(const char*);
int productosALista(const char* arch, tLista* lista);
void acumularProductoMenorStock(void** a, unsigned* tama, const void* b, unsigned tamb);
#endif // PRODUCTOS_H_INCLUDED
