#include "arbol.h"
/*Creacion del arbol*/
void crearArbol(Arbol* pa){
    *pa = NULL;
}
/*Estado del arbol*/
int arbolVacio(const Arbol* pa){
    return *pa ==NULL;
}
int arbolLleno(const Arbol* pa, void* elem, unsigned tamElem, int(*cmp)(const void*, const void*)){
    return 0;
}
/*Insercion de nodos*/
int insertarNodoOrdenado_recursivo(Arbol* pa, void* elem, unsigned tamElem, int(*cmp)(const void*, const void*)){
    int comparacion;
    //*pa por nue
    tNodo* nue;
    if(!*pa){
        if(!(nue = (tNodo*)malloc(sizeof(tNodo))) || !(nue->info = malloc(tamElem))){
            free(nue);
            return 0;
        }
        memcpy(nue->info, elem, tamElem);
        nue->tamInfo = tamElem;
        nue->der = NULL;
        nue->izq = NULL;
        *pa = nue;
        return 1;
    }
    comparacion = cmp((*pa)->info, elem);
    if(comparacion==0){
        return DUPLICADO;
    }
    if(comparacion > 0){
        return insertarNodoOrdenado_recursivo(&(*pa)->izq, elem, tamElem, cmp);
    }
    return insertarNodoOrdenado_recursivo(&(*pa)->der, elem, tamElem,cmp);
}


int insertarNodoOrdenado_iterativo(Arbol* pa, void* elem, unsigned tamElem, int(*cmp)(const void*, const void*)){
    int comparacion;
    while(*pa){
        comparacion  = cmp((*pa)->info, elem);
        if(comparacion==0){
            return DUPLICADO;
        }
        if(comparacion > 0){
            pa = &(*pa)->izq;
        }
        else
        {
            pa = &(*pa)->der;
        }

    }
    if(!((*pa) = (tNodo*)malloc(sizeof(tNodo))) || !((*pa)->info = malloc(tamElem))){
        free((*pa));
        return 0;
    }
    memcpy((*pa)->info, elem, tamElem);
    (*pa)->tamInfo = tamElem;
    (*pa)->izq = NULL;
    (*pa)->der = NULL;
    return 1;
}


/*Altura del arbol*/
unsigned alturaArbolBin(const Arbol* pa){
    int ai, ad;
    if(!*pa){
        return 0;
    }
    ai = alturaArbolBin(&(*pa)->izq);
    ad = alturaArbolBin(&(*pa)->der);
    return (ai>ad?ai:ad)+1;
}
/*RETORNA CANTIDAD NODOS*/
unsigned cantidadNodosArbolBin(const Arbol* pa){
    if(!*pa){
        return 0;
    }
    return cantidadNodosArbolBin(&(*pa)->izq)
     + cantidadNodosArbolBin(&(*pa)->der) + 1;
}

/*RECORRIDO INTERNO RECURSIVO*/
void _RecorrerArbolPreOrden_r(const Arbol* pa,unsigned nivel, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    if(!*pa){
        return;
    }
    accion((*pa)->info, (*pa)->tamInfo,nivel,param);
    _RecorrerArbolPreOrden_r(&(*pa)->izq,nivel+1,param, accion);
    _RecorrerArbolPreOrden_r(&(*pa)->der,nivel+1,param, accion);
}

void _RecorrerArbolPostOrden_r(const Arbol* pa,unsigned nivel, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    if(!*pa){
        return;
    }
    _RecorrerArbolPostOrden_r(&(*pa)->izq,nivel+1,param, accion);
    _RecorrerArbolPostOrden_r(&(*pa)->der,nivel+1,param, accion);
    accion((*pa)->info, (*pa)->tamInfo,nivel,param);
}
void _RecorrerArbolOrden_r(const Arbol* pa,unsigned nivel, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    if(!*pa){
        return;
    }
    _RecorrerArbolOrden_r(&(*pa)->izq,nivel+1,param, accion);
    accion((*pa)->info, (*pa)->tamInfo,nivel,param);
    _RecorrerArbolOrden_r(&(*pa)->der,nivel+1,param, accion);
}
void _RecorrerArbolPreOrdenInverso_r(const Arbol* pa,unsigned nivel, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    if(!*pa){
        return;
    }
    accion((*pa)->info, (*pa)->tamInfo, nivel, param);
    _RecorrerArbolPreOrdenInverso_r(&(*pa)->der,nivel+1,param, accion);
    _RecorrerArbolPreOrdenInverso_r(&(*pa)->izq,nivel+1,param, accion);
}
void _RecorrerArbolPostOrdenInverso_r(const Arbol* pa,unsigned nivel, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    if(!*pa){
        return;
    }
    _RecorrerArbolPostOrdenInverso_r(&(*pa)->der, nivel+1, param, accion);
    _RecorrerArbolPostOrdenInverso_r(&(*pa)->izq, nivel+1, param, accion);
    accion((*pa)->info,(*pa)->tamInfo, nivel, param);
}
void _RecorrerArbolOrdenInverso_r(const Arbol* pa,unsigned nivel, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    if(!*pa){
        return;
    }
    _RecorrerArbolOrdenInverso_r(&(*pa)->der,nivel+1, param, accion);
    accion((*pa)->info, (*pa)->tamInfo,nivel, param);
    _RecorrerArbolOrdenInverso_r(&(*pa)->izq, nivel+1, param, accion);

}
/*RECORRIDO INTERNO ITERATIVO*/

/*RECORRIDO EXTERNO RECURSIVO PARA USO DE USUARIO*/
void RecorrerArbolOrden_r(const Arbol* pa, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    _RecorrerArbolOrden_r(pa,0,param,accion);
}
void RecorrerArbolOrdenInverso_r(const Arbol* pa, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    _RecorrerArbolOrdenInverso_r(pa,0,param,accion);
}
void RecorrerArbolPreOrden_r(const Arbol* pa, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    _RecorrerArbolPreOrden_r(pa,0,param,accion);
}
void RecorrerArbolPreOrdenInverso_r(const Arbol* pa, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    _RecorrerArbolPreOrdenInverso_r(pa,0,param,accion);
}
void RecorrerArbolPostOrden_r(const Arbol* pa, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    _RecorrerArbolPostOrden_r(pa,0,param,accion);
}
void RecorrerArbolPostOrdenInverso_r(const Arbol* pa, void* param, void (*accion)(void*,unsigned, unsigned, void* )){
    _RecorrerArbolPostOrdenInverso_r(pa,0,param,accion);
}

/*Ver nodos segun nivel indicado*/


void MostrarEnteroDesdeNivel(void* elem, unsigned tamInfo,unsigned nivel_actual,void* nivel_objetivo){
    if(nivel_actual>= *(int*)nivel_objetivo){
        printf("%d\n", *(int*)elem);
    }
}
void MostrarEnteroHastaNivel(void* elem, unsigned tamInfo,unsigned nivel_actual,void* nivel_objetivo){
    if(nivel_actual<= *(int*)nivel_objetivo){
        printf("%d\n", *(int*)elem);
    }
}
void MostrarEnteroDeNivel(void* elem, unsigned tamInfo,unsigned nivel_actual,void* nivel_objetivo){
    if(nivel_actual== *(int*)nivel_objetivo){
        printf("%d\n", *(int*)elem);
    }
}


void verTodosLosNodosHastaNivel(const Arbol* pa,void* param, unsigned nivel, void (*accion)(void*,unsigned, unsigned, void* )){
    verTodosLosNodosHastaNivel_r(pa,param, nivel, 0, accion);
    //estaria bueno calcular la altura para evitar que el usuario ponga nivel 100000000000 y rompa el programa, de manera que se pueda
    //agregar if(nivel>altura) hacer nivel = altura para que se muestre todo el arbol pero no rompa el programa.
}

void verTodosLosNodosHastaNivel_r(const Arbol* pa,void* param, unsigned nivel, unsigned nivel_actual, void (*accion)(void*,unsigned, unsigned, void* )){


    if(nivel_actual>nivel ||!(*pa)){
        return;
    }

    accion((*pa)->info, (*pa)->tamInfo, nivel_actual, param);
    verTodosLosNodosHastaNivel_r(&(*pa)->izq, param,nivel, nivel_actual + 1, accion);
    verTodosLosNodosHastaNivel_r(&(*pa)->der, param,nivel, nivel_actual + 1,accion);
}

void verTodosLosNodosDeUnNivel(const Arbol* pa,void* param, unsigned nivel, void (*accion)(void*,unsigned, unsigned, void* )){
    verTodosLosNodosDeUnNivel_r(pa,param, nivel, 0, accion);
}

void verTodosLosNodosDeUnNivel_r(const Arbol* pa,void* param, unsigned nivel, unsigned nivel_actual, void (*accion)(void*,unsigned, unsigned, void* )){
    //todas estas funciones las podria pasar a los recorridos, y en la funcion interior de mostrar, crear otra como grabarEnteroDesdeNivel y ahi
    //utilizar el param como nivel y mandarle la condicion respecto al nivel necesaria.
    if(!(*pa)){
        return;
    }

    if(nivel==nivel_actual){
        accion((*pa)->info, (*pa)->tamInfo, nivel_actual, param);
    }
    verTodosLosNodosDeUnNivel_r(&(*pa)->izq, param,nivel, nivel_actual + 1, accion);
    verTodosLosNodosDeUnNivel_r(&(*pa)->der, param,nivel, nivel_actual + 1,accion);

}


void verTodosLosNodosDesdeNivel(const Arbol* pa,void* param, unsigned nivel, void (*accion)(void*,unsigned, unsigned, void* )){
    verTodosLosNodosDesdeNivel_r(pa,param, nivel, 0, accion);

}
void verTodosLosNodosDesdeNivel_r(const Arbol* pa,void* param, unsigned nivel, unsigned nivel_actual, void (*accion)(void*,unsigned, unsigned, void* )){


    if(!(*pa)){
        return;
    }

    if(nivel_actual>= nivel){
    accion((*pa)->info, (*pa)->tamInfo, nivel_actual, param);
    }
    verTodosLosNodosDesdeNivel_r(&(*pa)->izq, param,nivel, nivel_actual + 1, accion);
    verTodosLosNodosDesdeNivel_r(&(*pa)->der, param,nivel, nivel_actual + 1,accion);
}

/*Manejo de hojas*/
int contarHojas(const Arbol* p){
    int hojas=0;
    if(!*p){
        return 0;
    }
    if(!(*p)->izq && !(*p)->der){
        return 1;
    }
    hojas += contarHojas(&(*p)->izq);
    hojas+= contarHojas(&(*p)->der);
    return hojas;
}
void RecorrerHojas(const Arbol* p, void* param, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*p){
        return;
    }
    if(!(*p)->izq && !(*p)->der){
        accion((*p)->info,(*p)->tamInfo, 0 , param);
        return;
    }
    RecorrerHojas(&((*p)->izq), param, accion);
    RecorrerHojas(&((*p)->der), param,accion);
}
/*Manejo de no hojas*/
int contarNoHojas(const Arbol* p){
    int nodos=0;
    if(!*p){
        return 0;
    }
    if((*p)->izq || (*p)->der){
         nodos++;
    }
    nodos += contarNoHojas(&(*p)->izq);
    nodos += contarNoHojas(&(*p)->der);
    return nodos;
}
void RecorrerNoHojas(const Arbol* p,void* param, void(*accion)(void*, unsigned, unsigned, void*)){
    if(!*p){
        return;
    }
    if((*p)->izq || (*p)->der){
        accion((*p)->info,(*p)->tamInfo, 0 , param);
    }
    RecorrerNoHojas(&((*p)->izq), param, accion);
    RecorrerNoHojas(&((*p)->der), param,accion);
}

/*FUNCIONES DE BUSQUEDA*/
tNodo* busquedaArbol_nodo(const Arbol* pa, void* clave, int (*cmp)(const void*, const void*)){
    int comparacion;
    while(*pa && (comparacion = cmp((*pa)->info, clave))){
        if(comparacion<0){
            pa = &(*pa)->der;
        }
        else{
            pa = &(*pa)->izq;
        }
    }
    return *pa;
}

void* busquedaArbol_info(const Arbol* pa, void* clave, int (*cmp)(const void*, const void*)){
    int comparacion;
    while(*pa && (comparacion = cmp((*pa)->info, clave))){
        if(comparacion<0){
            pa = &(*pa)->der;
        }
        else{
            pa = &(*pa)->izq;
        }
    }
    return (*pa)->info;
}

Arbol* busquedaArbol_subArbol(const Arbol* pa, void* clave, int (*cmp)(const void*, const void*)){
    Arbol* subArbol = (Arbol*)malloc(sizeof(Arbol));
    if(!subArbol){
        return NULL;
    }
    int comparacion;
    while(*pa && (comparacion = cmp((*pa)->info, clave))){
        if(comparacion<0){
            pa = &(*pa)->der;
        }
        else{
            pa = &(*pa)->izq;
        }
    }
    *subArbol = *pa;
    return subArbol;
}

tNodo* busquedaMayorClaveArbol_ORDENADO(const Arbol* p, int (*cmp)(const void*,const void*)){
    while((*p)->der){
        p = &(*p)->der;
    }
    return *p;
}
tNodo* busquedaMenorClaveArbol_ORDENADO(const Arbol* p, int (*cmp)(const void*,const void*)){
    while((*p)->izq){
        p= &(*p)->izq;
    }
    return *p;
}
tNodo* busquedaMayorNoClaveArbol_ORDENADO(const Arbol* p, void* clave, int(*cmp)(const void*, const void*)){
    while((*p)->der){
        if(cmp((*p)->der->info,clave) == 0 && (*p)->der->der){
            p = &(*p)->der->der;
        }
        else if(cmp((*p)->der->info,clave) == 0 && !(*p)->der->der){
            return *p;
        }
        else{
            p = &(*p)->der;
        }
    }
    return *p;
}
tNodo* busquedaMenorNoClaveArbol_ORDENADO(const Arbol* p , void* clave, int(*cmp)(const void*, const void*)){
    while((*p)->izq){
        if(cmp((*p)->izq->info,clave) == 0 && (*p)->izq->izq){
            p = &(*p)->izq->izq;
        }
        else if(cmp((*p)->izq->info,clave) == 0 && !(*p)->izq->izq){
            return *p;
        }
        else{
            p = &(*p)->izq;
        }
    }
    return *p;
}
/*MAP FILTER REDUCE*/
void mapC(Arbol* pa, void* param_Map, void(*map_function)(void*,unsigned,unsigned,void*)){
    _RecorrerArbolOrden_r(pa,0,param_Map,map_function);
}
void ReduceC(Arbol* pa, void* resultado, void(*reduce_function)(void*,unsigned,unsigned,void*)){
    _RecorrerArbolOrden_r(pa,0,resultado,reduce_function);
}


void destruirArbol(Arbol* pa){
    if(!*pa){
        return;
    }
    destruirArbol(&(*pa)->izq);
    destruirArbol(&(*pa)->der);
    free((*pa)->info);
    free((*pa));
    *pa= NULL;
}
