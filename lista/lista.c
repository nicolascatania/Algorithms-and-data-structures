#include "lista.h"



void crearLista(tLista* lista)
{
    *lista=NULL;
}

int listaVacia(const tLista* lista)
{
    return *lista==NULL;
}

int listaLlena(const tLista* lista, unsigned tamElem)
{

    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));
    void* info = malloc(tamElem);

    free(aux);
    free(info);

    return aux==NULL || info==NULL;
}

int ponerEnListaUltimo(tLista* lista,const void* elem, unsigned tamElem)
{

    tNodo* aux;

    while(*lista)
    {
        lista = &(*lista)->sig;
    }
    if((aux= (tNodo*)malloc(sizeof(tNodo)))==NULL || (aux->info=malloc(tamElem))==NULL)
    {
        free(aux);
        return 0;
    }

    memcpy(aux->info, elem, tamElem);
    aux->tamInfo = tamElem;
    aux->sig= NULL;
    *lista= aux;
    return 1;

}

int ponerEnListaPrimero(tLista* lista, const void* elem, unsigned tamElem)
{

    tNodo* aux = (tNodo*)malloc(sizeof(tNodo));

    if(aux==NULL || (aux->info= malloc(tamElem))==NULL)
    {
        return 0;
    }

    memcpy(aux->info, elem, tamElem);
    aux->tamInfo= tamElem;
    aux->sig = *lista;
    *lista = aux;

    return 1;
}

int sacarUltimoLista(tLista* lista, void* buffer, unsigned tamBuffer)
{
    if(*lista==NULL)
    {
        return 0;
    }
    while((*lista)->sig)
    {
        lista = &(*lista)->sig;
    }

    memcpy(buffer,(*lista)->info, MINIMO(tamBuffer,(*lista)->tamInfo));
    free((*lista)->info);
    free(*lista);
    *lista = NULL;
    return 1;

}
int sacarPrimeroLista(tLista* lista, void* buffer, unsigned tamBuffer)
{
    tNodo* aux = *lista;

    if(!aux)
    {
        return 0;
    }

    *lista = aux->sig;
    memcpy(buffer, aux->info, MINIMO(tamBuffer, aux->tamInfo));
    free(aux->info);
    free(aux);
    return 1;

}
int verPrimeroLista(const tLista* lista, void* buffer, unsigned tamBuffer)
{
    if(*lista==NULL)
    {
        return 0;
    }
    memcpy(buffer,(*lista)->info, MINIMO(tamBuffer, (*lista)->tamInfo));
    return 1;

}
int verUltimoLista(const tLista* lista, void* buffer, unsigned tamBuffer)
{
    if(*lista==NULL)
    {
        return 0;
    }
    while((*lista)->sig)
    {
        lista = &(*lista)->sig;
    }
    memcpy(buffer, (*lista)->info, MINIMO(tamBuffer, (*lista)->tamInfo));

    return 1;

}

void vaciarLista(tLista* lista)
{

    while(*lista)
    {
        tNodo* aux= *lista;
        *lista = aux->sig;
        free(aux->info);
        free(aux);
    }


}

int mostrarLista(const tLista* lista, void(*mostrar)(const void*, FILE*), FILE* stream)
{

    int cant=0;
    while(*lista)
    {
        mostrar((*lista)->info, stream);
        lista= &(*lista)->sig;
        cant++;
    }
    return cant;

}

void* buscarInfoPorClave(const tLista* lista,const void* clave, unsigned tam, int(*cmp)(const void*, const void*))
{

    while(*lista)
    {

        if(cmp((*lista)->info, clave)==0)
        {
            return (*lista)->info;
        }
        lista = &(*lista)->sig;
    }

    return NULL;
}


tLista* buscarNodoPorClave(const tLista* lista,const void* clave, unsigned tam, int(*cmp)(const void*, const void*))
{
    tNodo* aux;
    if(cmp((*lista)->info, clave)==0)
    {
        return (tLista*)lista;
    }

    while((*lista)->sig)
    {
        aux = (*lista)->sig;
        if(cmp((aux)->info, clave)==0)
        {
            return &(*lista)->sig;
        }
        lista = &(*lista)->sig;
    }

    return NULL;
}

int ordenarLista(tLista* lista, int (*cmp)(const void* a, const void* b))
{
    tLista* ini = lista;
    tNodo* pmenor;
    void* aux;
    unsigned tamI;
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    while((*ini)->sig)
    {

        if((pmenor = buscarMenor(ini, cmp))!=*ini)
        {
            aux = (*ini)->info;
            tamI = (*ini)->tamInfo;

            (*ini)->info = pmenor->info;
            pmenor->info = aux;

            (*ini)->tamInfo = pmenor->tamInfo;
            pmenor->tamInfo = tamI;
        }

        ini = &(*ini)->sig;
    }

    return 1;
}

tNodo* buscarMenor(tLista* lista, int(*cmp)(const void*, const void*))
{
    tNodo* pmenor= *lista;
    lista = &(*lista)->sig;
    while(*lista)
    {
        if(cmp(pmenor->info, (*lista)->info)>0)
        {
            pmenor = *lista;
        }

        lista = &(*lista)->sig;
    }

    return pmenor;

}

int insertarEnOrden(tLista* lista, int(*cmp)(const void*, const void*), const void* elem, unsigned tam, int(*acumular)(void**, unsigned*, const void*, unsigned))
{

    tNodo* nue;

    while((*lista) && cmp(elem,(*lista)->info)>0)
    {
        lista = &(*lista)->sig;
    }

    if(*lista && (cmp(elem,(*lista)->info)==0))
    {
        if(acumular)
        {
            if(!(acumular(&(*lista)->info, &(*lista)->tamInfo, elem, tam)))
            {
                return 0;
            }
            return DUPLICADO;
        }
    }

    if(((nue = (tNodo*)malloc(sizeof(tNodo)))==NULL) || (((nue->info)= malloc(tam))==NULL))
    {
        free(nue);
        return 0;
    }


    memcpy(nue->info,elem,tam);
    nue->tamInfo = tam;
    nue->sig = *lista;
    *lista = nue;
    return 1;

    /*

    Este es mi codigo original, que funciona bien, pero no es tan eficiente
    ademas, reserva memoria antes de usarla realmente, que se puede solucionar copiando y pegando las respectivas lineas del tema en donde se realiza la insercion,
    pero es mucho copiar y pega y no me gusta, alargaria demasiado el codigo.
    Ese es el mayor problema, por otro lado, no tuve en cuenta el tema de que si habia que acumular el elemento a insertar si ya existia en la lista
    ejemplo-> acumular el stock de un producto si entra repetido.
    ejemplo-> si es una lista de enteros, no hacer nada y pasar NULL a accion.
    Aparte mi logica era manejar la insercion parado desde el nodo anterior al nodo que tiene una clave mayor al elemento a insertar
    supongamos 5 10 en lista y quiero ingresar el 6, bueno
    el codigo de arriba lo soluciona parandose en 10
    yo en un principio lo hice parandome en el 5, que considero que son ambas cosas validas, pero claro
    a mi me hizo primero hacer un if aparte para tener en cuenta el caso donde debo insertar el elemetno en la primer posicion d la lista.


    Tambien incluiria un caso aparte para insertarlo al final de la lista
    Un quilombo mal

    if(cmp(nue->info, (*lista))<0)//evaluo si es menor al primer elemento de la lista.
      {

          nue->sig = (*lista);
          *lista = nue;
          return 1;
      }

      while((*lista)->sig)
      {

          if(cmp(nue->info,(*lista)->sig->info)<0)
          {
              nue->sig = (*lista)->sig;
              (*lista)->sig = nue;
              return 1;
          }
          lista = &(*lista)->sig;
      }

      (*lista)->sig = nue;
      nue->sig = NULL;


      return 1;
      */
}


int eliminarPrimeraOcurrenciaClave(tLista* lista, const void* clave, int (*cmp)(const void*, const void*))
{

    tNodo* aux, *anterior;
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    while((*lista) && (cmp((*lista)->info, clave)!=0))
    {
        anterior = *lista;
        lista = &(*lista)->sig;
    }
    aux = *lista;
    if((*lista)->sig)
    {
        *lista = (*lista)->sig;
    }
    else
    {
        anterior->sig = NULL;
    }

    free(aux->info);
    free(aux);

    return 1;

}

int eliminarTodasOcurrenciasClave(tLista* lista, const void* clave, int (*cmp)(const void*, const void*))
{

    int eliminadas=0;
    tNodo* aux, *anterior;
    tLista* ini = lista;

    if(!*ini)
    {
        return LISTA_VACIA;
    }


    while(*ini)
    {
        while((*lista) && (cmp((*lista)->info, clave)!=0))
        {
            anterior = *lista;
            lista = &(*lista)->sig;
        }
        aux = *lista;
        eliminadas++;
        if((*lista)->sig)
        {
            *lista = (*lista)->sig;
        }
        else
        {
            anterior->sig = NULL;
            return eliminadas;
        }

        free(aux->info);
        free(aux);

        ini = lista;
    }

    return eliminadas;

}

int eliminarUltimaOcurrenciaClave(tLista* lista, const void* clave, int (*cmp)(const void*, const void*))
{
    tNodo* anterior, *aux, *eliminar;
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    if(cmp((*lista)->info, clave)==0)
    {
        eliminar = (*lista);
        anterior=NULL;
    }

    while((aux = (*lista)->sig))
    {
        if((cmp((aux)->info, clave)==0))
        {
            anterior= *lista;
            eliminar = (*lista)->sig; //elemento a eliminar
        }
        lista = &(*lista)->sig;

    }


    lista = &anterior; //me reposiciono sobre el elemento anterior al que debo eliminar, mediante tNodo** para no perder el inicio de la lista
    if(!anterior)
    {
        //la ultima aparicion resulta ser la unica y estar en primer lugar de la lista
        *lista = (*lista)->sig;
    }
    else if((eliminar)->sig)
    {
        (*lista)->sig = (eliminar)->sig;
    }
    else
    {
        anterior->sig = NULL;
    }

    free(eliminar->info);
    free(eliminar);

    return 1;
}


int insertarEnPosicion(tLista* lista, const void* elem,unsigned tam, int pos)
{

    tNodo* nue;

    if(!*lista)
    {
        if(((nue = (tNodo*)malloc(sizeof(tNodo)))== NULL) || ((nue->info = malloc(tam))==NULL))
        {
            return ERROR_MEMORIA;
        }
        else
        {
            memcpy(nue->info, elem, tam);
            nue->tamInfo = tam;
            nue->sig = NULL;
            *lista = nue;
            return 1;
        }
    }

    while((*lista)->sig && pos>0)
    {
        lista = &(*lista)->sig;
        pos--;
    }

    if(!(*lista))
    {
        //si pos > cantidad Nodos , inserto al final
        if(((nue = (tNodo*)malloc(sizeof(tNodo)))== NULL) || ((nue->info = malloc(tam))==NULL))
        {
            return ERROR_MEMORIA;
        }
        else
        {
            memcpy(nue->info, elem, tam);
            nue->tamInfo = tam;
            nue->sig = NULL;
            (*lista)->sig = nue;
            return 1;
        }
    }

    if(((nue = (tNodo*)malloc(sizeof(tNodo)))== NULL) || ((nue->info = malloc(tam))==NULL))
    {
        return ERROR_MEMORIA;
    }
    else
    {
        memcpy(nue->info, elem, tam);
        nue->tamInfo = tam;
        nue->sig = (*lista)->sig;

        *lista = nue;

    }

    return 1;

}


int EliminarEnPosicion(tLista* lista, int pos)
{

    tNodo* aux, *anterior;
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    while((*lista)->sig && pos>0)
    {
        anterior = *lista;
        lista = &(*lista)->sig;
        pos--;
    }

    aux = *lista;
    if((*lista)->sig == NULL)
    {
        anterior->sig = NULL;

    }
    else
    {
        *lista = (*lista)->sig;
    }



    free(aux->info);
    free(aux);
    return 1;


}

int eliminarNoDuplicados(tLista* lista, int(*cmp)(const void*, const void*), void (*accion)(tNodo*))
{
    tLista* ini, *pi = lista;
    tNodo* aux;
    int dup, eliminados=0, posElem=0, posIteracion;
    if(!*lista)
    {
        return LISTA_VACIA;
    }


    while(*pi)
    {

        ini = lista;
        dup=0;
        posIteracion = 0;

        while(*ini)
        {

            if((cmp((*ini)->info, (*pi)->info)==0) && (posElem!=posIteracion))
            {

                if(accion)
                {

                    accion(*pi);

                }
                dup = 1;
                break;
            }


            posIteracion++;
            ini = &(*ini)->sig;
        }
        if (!dup)
        {
            eliminados++;
            aux = *pi;
            *pi = (*pi)->sig;
            free(aux->info);
            free(aux);
        }

        if(dup){
           pi = &(*pi)->sig;
           posElem++;
        }

    }

    return eliminados;
}


int eliminarDespuesClaveNNodos(tLista* lista, const void* clave, int (*cmp)(const void*, const void*), int n)
{

    tNodo* aux;
    int eliminados=0;
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    if(!n)
    {
        return n_CERO;
    }

    while(*lista && cmp(((*lista)->info), clave)!=0)
    {
        lista = &(*lista)->sig;
    }
    //para justo en la clave que buscamos
    lista = &(*lista)->sig;
    while(n>0 && *lista)
    {
        aux = *lista;
        *lista= (*lista)->sig;
        free(aux->info);
        free(aux);
        n--;
        eliminados++;
    }

    return eliminados;
}

int eliminarNUltimosNodos(tLista* lista, int n)
{

    tLista* auxIni = lista;
    tLista* ult = lista;
    tNodo* auxElim;
    int eliminados =0;
    int cant=0;

    while(n && *ult){
        ult = &(*ult)->sig;
        n--;
    }

    while(*ult){
        lista = &(*lista)->sig;
        ult= &(*ult)->sig;
    }

    while(*lista){
        auxElim = *lista;



        free(auxElim->info);
        free(auxElim);
        eliminados++;

        if((*lista)->sig)
        {
            *lista = (*lista)->sig;
        }
        else
        {
            *lista = NULL;
            return eliminados;
        }

    }

    return eliminados;

}


/*int eliminarNUltimosNodosRecursiva(tLista* lista, int* n)
{

    tNodo* aux;
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    if((*lista)->sig)
    {

        return eliminarNUltimosNodosRecursiva(&(*lista)->sig, n);
    }
    else if((*n)>=0)
    {
        aux = *lista;
        free(aux->info);
        free(aux);
        *lista= NULL;
        (*n)--;
    }
    else
    {
        return;
    }

}*/


int insertarDespuesClaveNNodos(tLista* lista, const void* elem, const void* clave,unsigned tam, int (*cmp)(const void*, const void*), int n)
{

    tNodo* aux;
    int i;
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    while(*lista && cmp((*lista)->info, clave)!=0)
    {
        lista = &(*lista)->sig;
    }

    for(i=0; i<n; i++)
    {
        aux=(tNodo*)malloc(sizeof(tNodo));
        if(!aux)
        {
            return ERROR_MEMORIA;
        }
        aux->info = malloc(tam);
        if(!(aux->info))
        {
            free(aux);
            return ERROR_MEMORIA;
        }


        memcpy(aux->info, elem, tam);
        aux->tamInfo = tam;
        aux->sig = (*lista)->sig;

        (*lista)->sig = aux;
        lista = &(*lista)->sig;

    }
    return 1;
}


int insertarDespuesClaveNNodosV2(tLista* lista, const void* vec, const void* clave, unsigned tam, int (*cmp)(const void*, const void*), int n)
{

    tNodo* aux;
    int i;
    if(!*lista)
    {
        return LISTA_VACIA;
    }

    while(*lista && cmp((*lista)->info, clave)!=0)
    {
        lista = &(*lista)->sig;
    }

    for(i=0; i<n; i++)
    {
        aux=(tNodo*)malloc(sizeof(tNodo));
        if(!aux)
        {
            return ERROR_MEMORIA;
        }
        aux->info = malloc(tam);
        if(!(aux->info))
        {
            free(aux);
            return ERROR_MEMORIA;
        }


        memcpy(aux->info, vec, tam);
        aux->tamInfo = tam;
        aux->sig = (*lista)->sig;

        (*lista)->sig = aux;
        lista = &(*lista)->sig;

        vec += tam;
    }
    return 1;

}


void mapC(tLista* lista, void (*mapeo)(void*)){

    while(*lista){
        mapeo((*lista)->info);
        lista = &(*lista)->sig;
    }


}

tLista mapPy(tLista* lista, void(*mapeo)(void*)){

    tLista nuevaLista;

    crearLista(&nuevaLista);
    while(*lista){
        mapeo((*lista)->info);

        ponerEnListaUltimo(&nuevaLista,(*lista)->info, (*lista)->tamInfo);
        lista = &(*lista)->sig;
    }


    return nuevaLista;
}

void filterC(tLista* lista, void* filtro, int(*cmp)(const void*, const void*)){

    tNodo* aux;
    while(*lista){
        if(!(cmp((*lista)->info, filtro))){
            aux = *lista;
            *lista = (*lista)->sig;
            free(aux->info);
            free(aux);
        }
        else{
          lista = &(*lista)->sig;
        }
    }


}

tLista filterPy(tLista* lista, void* filtro, int(*cmp)(const void*, const void*)){


    tLista listaResultado;
    crearLista(&listaResultado);

    while(*lista){
         if((cmp((*lista)->info, filtro))){
            ponerEnListaUltimo(&listaResultado, (*lista)->info,(*lista)->tamInfo);
        }

        lista = &(*lista)->sig;
    }


    return listaResultado;

}


void reduce(tLista* lista, void* resultado, void(*reduccion)(const void*, void*)){

    while(*lista){

        reduccion((*lista)->info,resultado);

        lista = &(*lista)->sig;
    }
}
