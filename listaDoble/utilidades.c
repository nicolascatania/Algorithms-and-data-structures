#include "utilidades.h"
#include "productos.h"

int filtrarEnterosMayoresA(const void*a , const void*b){

    int* pa = (int*)a;
    int* filtro = (int*)b;

    if(*pa > *filtro){
        return 1;
    }
    return 0;

}

void mostrarEntero(const void* a){

    printf("%2d ", *((int*)a));

}

int cmpIndiceChar(const void*a, const void* b){
    tIndice* elem = (tIndice*)a;
    return (elem->cod - *(char*)b);

}

int cmpEnteros(const void*a, const void* b){

    return (*(int*)a - *(int*)b);
}

void acumularEnteros(void** elemLista, unsigned* tamElemLista, const void* elem, unsigned tam){

    int* a = (int*)*elemLista;
    int* b = (int*)elem;

    *a += *b;

}

