#ifndef UTILIDADES_H_INCLUDED
#define UTILIDADES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void mostrarEntero(const void* a);
int cmpEnteros(const void*a, const void* b);
int cmpIndiceChar(const void*a, const void* b);
void acumularEnteros(void** elemLista, unsigned* tamElemLista, const void* elem, unsigned tam);
int filtrarEnterosMayoresA(const void*a , const void*b);
#endif // UTILIDADES_H_INCLUDED
