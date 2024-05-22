#ifndef PRODUCTOS_H_INCLUDED
#define PRODUCTOS_H_INCLUDED

#define TAM_DESCRIPCION 100
#define TAM_MARCA 50
#include "lista.h"





typedef struct{

    char codigo;
    int stock;
    char descripcion[TAM_DESCRIPCION];
    float precioUnitario;
    char marca[TAM_MARCA];
}tProducto;

void mostrarProducto(const void* prod, FILE*);
int comparaProductosXClaveCodigo(const void* info, const void* clave);
void generarLotePruebas();
int leerBinALista(const char* nom, tLista* lista);
int leerBinAListaEnOrden(const char* nom, tLista* lista);
int leerBinInsertarOrdenado(const char* nom, tLista* lista);
int cmpProductosCodigo(const void* a, const void* b);
int acumularStockProducto(void**, unsigned*, const void*, unsigned);
#endif // PRODUCTOS_H_INCLUDED
