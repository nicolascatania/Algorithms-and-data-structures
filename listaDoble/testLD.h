#ifndef TESTLD_H_INCLUDED
#define TESTLD_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utilidades.h"
#include "listaDoble.h"

void _probarInsercionOrdenada(tLista*);
void _probarInsercionAlFinal(tLista*);
void _probarInsercionAlComienzo(tLista*);
int _probarEliminarLista(tLista*);
int _probarMostrarIzqDer(tLista*, int);
int _probarMostrarDerIzq(tLista*, int);
void _probarOrdenarLista(tLista*);
void _probarEliminarPorClave(tLista*);
void _probarEliminarTodasCLaves(tLista* l);
int _probarBuscarPorClave(); //la funcion anda, pero quiza la prueba en sí no funque porque estaba en el main, me olvide de hacer una prueba en testLD.c.
void _probarResumirLista(tLista *l);
void _probarFiltro(tLista *l);

#endif // TESTLD_H_INCLUDED
