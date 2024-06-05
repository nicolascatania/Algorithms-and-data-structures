#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUPLICADO 2

typedef struct sNodo{
    void*info;
    unsigned tamInfo;
    struct sNodo* izq;
    struct sNodo* der;
}tNodo;

typedef tNodo* Arbol;

/*Crear arbol*/
void crearArbol(Arbol*);

/*Estado del arbol*/
int arbolVacio(const Arbol*);
int arbolLleno(const Arbol*, void*, unsigned, int(*cmp)(const void*, const void*));

/*INSERCION*/
int insertarNodoOrdenado_recursivo(Arbol*, void*, unsigned, int(*cmp)(const void*, const void*));
int insertarNodoOrdenado_iterativo(Arbol*, void*, unsigned, int(*cmp)(const void*, const void*));

/*Altura del arbol*/
unsigned alturaArbolBin(const Arbol*);
/*Cantidad de nodos*/
unsigned cantidadNodosArbolBin(const Arbol*);
/*Recuperacion de datos a un arbol*/
//Archivo
//alguna estructura de datos
/*Recorrido interno RECURSIVO*/
void _RecorrerArbolPreOrden_r(const Arbol*, unsigned , void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolPostOrden_r(const Arbol*, unsigned , void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolOrden_r(const Arbol*, unsigned , void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolPreOrdenInverso_r(const Arbol*, unsigned , void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolPostOrdenInverso_r(const Arbol*, unsigned , void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolOrdenInverso_r(const Arbol*, unsigned , void* , void (*accion)(void*,unsigned, unsigned, void*));

/*Recorrido interno ITERATIVO*/
void _RecorrerArbolPreOrden_I(const Arbol*, unsigned, void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolPostOrden_I(const Arbol*, unsigned, void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolOrden_I(const Arbol*, unsigned, void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolPreOrdenInverso_I(const Arbol*, unsigned, void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolPostOrdenInverso_I(const Arbol*, unsigned, void* , void (*accion)(void*,unsigned, unsigned, void*));
void _RecorrerArbolOrdenInverso_I(const Arbol*, unsigned, void* , void (*accion)(void*,unsigned, unsigned, void*));

/*Recorrido externo RECURSIVO (para uso del usuario)*/
void RecorrerArbolOrden_r(const Arbol* , void* , void (*accion)(void*,unsigned, unsigned, void* ));
void RecorrerArbolOrdenInverso_r(const Arbol* , void* , void (*accion)(void*,unsigned, unsigned, void* ));
void RecorrerArbolPreOrden_r(const Arbol* , void* , void (*accion)(void*,unsigned, unsigned, void* ));
void RecorrerArbolPreOrdenInverso_r(const Arbol* , void* , void (*accion)(void*,unsigned, unsigned, void* ));
void RecorrerArbolPostOrden_r(const Arbol* , void* , void (*accion)(void*,unsigned, unsigned, void* ));
void RecorrerArbolPostOrdenInverso_r(const Arbol*, void*, void (*accion)(void*,unsigned, unsigned, void* ));

/*Ver nodos segun nivel indicado*/
void MostrarEnteroDesdeNivel(void* elem, unsigned tamInfo,unsigned nivel_actual,void* nivel_objetivo);
void MostrarEnteroHastaNivel(void* elem, unsigned tamInfo,unsigned nivel_actual,void* nivel_objetivo);
void MostrarEnteroDeNivel(void* elem, unsigned tamInfo,unsigned nivel_actual,void* nivel_objetivo);

void verTodosLosNodosHastaNivel(const Arbol*,void*, unsigned,void (*accion)(void*,unsigned, unsigned, void* ) );
void verTodosLosNodosHastaNivel_r(const Arbol*,void*, unsigned nivel, unsigned nivel_actual, void (*accion)(void*,unsigned, unsigned, void* ));
void verTodosLosNodosDeUnNivel(const Arbol*,void* , unsigned nivel, void (*accion)(void*,unsigned, unsigned, void* ));
void verTodosLosNodosDeUnNivel_r(const Arbol* pa,void* param, unsigned nivel, unsigned nivel_actual, void (*accion)(void*,unsigned, unsigned, void* ));
void verTodosLosNodosDesdeNivel(const Arbol* pa,void* param, unsigned nivel, void (*accion)(void*,unsigned, unsigned, void* ));
void verTodosLosNodosDesdeNivel_r(const Arbol* pa,void* param, unsigned nivel, unsigned nivel_actual, void (*accion)(void*,unsigned, unsigned, void* ));
/*Manejo de hojas*/
int contarHojas(const Arbol*);
void RecorrerHojas(const Arbol*,void*, void(*accion)(void*, unsigned, unsigned, void*));
/*Manejo de no hojas*/
int contarNoHojas(const Arbol*);
void RecorrerNoHojas(const Arbol*,void*, void(*accion)(void*, unsigned, unsigned, void*));
/*BUSQUEDA*/
tNodo* busquedaArbol_nodo(const Arbol*, void*, int (*cmp)(const void*, const void*));
void* busquedaArbol_info(const Arbol*, void*, int (*cmp)(const void*, const void*));
Arbol* busquedaArbol_subArbol(const Arbol*, void*, int (*cmp)(const void*, const void*));
tNodo* busquedaMayorClaveArbol_ORDENADO(const Arbol*, int (*cmp)(const void*,const void*));
tNodo* busquedaMenorClaveArbol_ORDENADO(const Arbol*, int (*cmp)(const void*,const void*));
tNodo* busquedaMayorNoClaveArbol_ORDENADO(const Arbol*, void*, int(*cmp)(const void*, const void*));
tNodo* busquedaMenorNoClaveArbol_ORDENADO(const Arbol*, void*, int(*cmp)(const void*, const void*));
/*MAP FILTER REDUCE*/
void mapC(Arbol*, void*, void(*map_function)(void*,unsigned,unsigned,void*));
void ReduceC(Arbol*, void*, void(*reduce_function)(void*,unsigned,unsigned,void*));

/*Destruccion*/
void destruirArbol(Arbol*); //hacer


#endif // ARBOL_H_INCLUDED
