#include "listaDoble.h"

void crearLista(tLista* lista)
{
    *lista = NULL;
}

int vaciarLista(tLista* lista)
{

    int cant = 0;
    tNodo* aux = *lista;
    tNodo* elim;
    if(aux)
    {
        while(aux->ant)
        {
            aux = aux->ant;
        }
        while(aux)
        {
            elim = aux->sig;
            free(aux->info);
            free(aux);
            aux = elim;
            cant++;
        }
        *lista = NULL;
    }
    return cant;

}

int listaVacia(const tLista* lista)
{

    return (*lista) == NULL;

}

int listaLlena(const tLista* lista, unsigned tam)
{
    return 0;
}

int insertarAlFinal(tLista* lista, const void* elem, unsigned tam)
{


    tNodo* aux, *act = *lista;
    //puede salir mal la insercion, entonces tengo que manejarme con un puntero auxiliar
    //para que en caso de fallar
    // el puntero original se quede donde estaba, el ultimo elemento insertado
    if(act)
    {
        while(act->sig)
        {
            act = act->sig; //me muevo hasta el ultimo nodo de la lista
        }
    }

    aux = (tNodo*)malloc(sizeof(tNodo));
    if(!aux)
    {
        return 0;
    }
    aux->info = malloc(tam);
    if(!(aux->info))
    {
        free(aux);
        return 0;
    }

    memcpy(aux->info,elem, tam);
    aux->tamInfo = tam;
    aux->sig = NULL;  //aux será el ultimo nodo de la lista
    aux->ant = act;  //act habia quedado en el ultimo nodo de la lista

    if(act)
    {
        act->sig = aux;
    }

    *lista = aux; //apunto el puntero a lista al ultimo insertado
    return 1;
}


int insertarAlComienzo(tLista* lista, const void* elem, unsigned tam)
{


    tNodo* aux, *act=*lista;

    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }
    }

    aux = (tNodo*)malloc(sizeof(tNodo));
    if(!aux)
    {
        return 0;
    }
    aux->info = malloc(tam);
    if(!(aux->info))
    {
        free(aux);
        return 0;
    }

    memcpy(aux->info,elem,tam);
    aux->tamInfo = tam;
    aux->ant = NULL;
    aux->sig = act;

    if(act)
    {
        act->ant = aux;
    }
    *lista = aux;


    return 1;
}


int mostrarIzqDer(const tLista* lista, void(*mostrar)(const void*))
{

    tNodo* act=*lista;
    int cant=0;
    if(act)
    {
        while(act->ant)
        {
            act = act->ant;
        }
        while(act)
        {
            mostrar(act->info);
            act = act->sig;
            cant++;
        }
    }

    return cant;

}


int mostrarDerIzq(const tLista* lista, void(*mostrar)(const void*))
{

    tNodo* act = *lista;
    int cant =0;
    if(act)
    {
        while(act->sig)
        {
            act= act->sig;
        }
        while(act)
        {
            mostrar(act->info);
            act = act->ant;
            cant++;
        }
    }

    return cant;

}


int insertarEnOrden(tLista* lista, const void* elem, unsigned tam, int(*cmp)(const void*, const void*), void (*acumular)(void**, unsigned*, const void*, unsigned))
{

    tNodo* nue, *act = *lista, *sig,*ant;
    int aux;

    if(!act)
    {
        ant= NULL;
        sig = NULL;
    }
    else
    {
        while(act->sig!=NULL && cmp(act->info,elem)<0)
        {
            act = act->sig;
        }
        while(act->ant !=NULL && cmp(act->info,elem)>0)
        {
            act = act->ant;
        }

        aux = cmp(act->info, elem);

        if(aux == 0)
        {
            *lista = act;
            if(acumular)
            {
                acumular(&act->info,&act->tamInfo, elem, tam);

            }
            return DUPLICADO;
        }
        if(aux < 0)
        {
            ant = act;
            sig = act->sig;
        }
        else
        {
            sig = act;
            ant = act->ant;

        }


    }

    nue = (tNodo*)malloc(sizeof(tNodo));
    if(!nue)
    {
        return 0;
    }
    nue->info = malloc(tam);
    if(!nue->info)
    {
        free(nue);
        return 0;
    }

    memcpy(nue->info, elem, tam);
    nue->tamInfo = tam;
    nue->sig = sig;
    nue->ant = ant;

    if(sig)
    {
        sig->ant = nue;
    }
    if(ant)
    {
        ant->sig = nue;
    }

    *lista = nue;

    return 1;

}


void OrdenarLista(tLista* lista, int(*cmp)(const void*, const void*))
{

    tNodo* act= *lista, *menor, *pa;
    void* inf;

    if(!act)
    {
        return;
    }

    while(act->ant)
    {
        act= act->ant;
    }

    while(act)
    {
        pa= act;
        menor = act;

        while(pa)
        {
            if(cmp(pa->info, menor->info)<0)
            {
                menor = pa;
            }
            pa = pa->sig;
        }

        inf = act->info;
        act->info = menor->info;
        menor->info = inf;

        act = act->sig;

    }

}


int eliminarPorClave(tLista* lista, void* clave, unsigned tam, int(*cmp)(const void*, const void*))
{


    tNodo* act = *lista;
    tNodo* ant, *sig;
    int c;
    if(!act)
    {
        return 0;
    }


    while(cmp(act->info,clave)!=0 && act->ant)
    {
        act = act->ant;
    }
    while(cmp(act->info,clave)!=0 && act->sig)
    {
        act = act->sig;
    }

    c= cmp(act->info, clave);
    if(c==0)
    {
        sig = act->sig;
        ant = act->ant;

        if(ant)
        {
            ant->sig = sig;
        }
        if(sig)
        {
            sig->ant = ant;
            *lista = sig;
        }
        else
        {
            *lista = ant;
        }

        free(act->info);
        free(act);

        return 1;
    }

    return 0;

}



tLista* buscarPorClave_desord(tLista* lista, void* clave, int(*cmp)(const void*, const void*))
{

    tNodo* act = *lista;
    int c;
    if(!act)
    {
        return NULL;
    }

    while(cmp(act->info,clave)!=0 && act->ant)
    {
        act = act->ant;
    }

    c= cmp(act->info,clave);
    if(c==0)
    {
        *lista = act;
        return lista;
    }
    else
    {
        act= *lista;
    }

    while(cmp(act->info,clave)!=0 && act->sig)
    {
        act = act->sig;
    }

    c= cmp(act->info, clave);
    if(c==0)
    {
        *lista = act;
        return lista;
    }

    return NULL;


}

tLista* buscarPorClave_ord(tLista* lista, void* clave, int(*cmp)(const void*, const void*))
{
    tNodo* act = *lista;
    int c;
    if(!act)
    {
        return NULL;
    }

    while(cmp(clave, act->info)<0 && act->ant)
    {
        act = act->ant;
    }

    while(cmp(clave, act->info)>0 && act->sig)
    {
        act = act->sig;
    }

    c= cmp(clave, act->info);
    if(c==0)
    {
        *lista = act;
        return lista;
    }

    return NULL;

}

int eliminarClaves(tLista* lista, void* clave, int (*cmp)(const void*, const void*))
{

    tNodo* aux = *lista;
    tNodo* act = *lista;
    tNodo *ant, *sig;
    int eliminados=0;
    while(act)
    {
        if(cmp(act->info, clave)==0)
        {
            sig = act->sig;
            ant = act->ant;
            if(ant)
            {
                ant->sig = sig;
            }
            if(sig)
            {
                sig->ant = ant;
                *lista = sig;
            }
            else
            {
                *lista = ant;
            }

            free(act->info);
            free(act);
            eliminados++;
        }

        act = act->sig;
    }

    act = aux->ant;
    while(act)
    {
        if(cmp(act->info, clave)==0)
        {
            sig = act->sig;
            ant = act->ant;
            if(ant)
            {
                ant->sig = sig;
            }
            if(sig)
            {
                sig->ant = ant;
                *lista = sig;
            }
            else
            {
                *lista = ant;
            }

            free(act->info);
            free(act);
            eliminados++;
        }

        act = act->ant;

    }

    return eliminados;

}


void resumirOcurrencias(tLista* lista, int (*cmp)(const void*, const void*), void (*resumir)(void**, unsigned*,const void*, unsigned))
{

    tNodo* pd, *pi= *lista;
    tNodo* sig, *ant, *aux;
    while(pi)
    {
        pd = pi->sig;
        while(pd)
        {
            if(cmp(pd->info, pi->info)==0)
            {
                if(resumir)
                {
                    resumir(&pi->info, &pi->tamInfo, pd->info, pd->tamInfo);
                }
                sig = pd->sig;
                ant = pd->ant;
                aux = pd;
                if(ant)
                {
                    ant->sig = sig;
                }
                if(sig)
                {
                    sig->ant = ant;
                    *lista = sig;
                }
                else
                {
                    *lista = ant;
                }
                free(aux->info);
                free(aux);
            }

            pd = pd->sig;
        }

        pi = pi->ant;
    }

}

void filter(tLista* l,const void* f, int (*filtro)(const void*, const void*))
{
    tNodo* aux= *l;
    tNodo* act = *l;
    tNodo *sig, *ant;
    while(act)
    {
        if(!filtro(act->info, f))
        {
            sig = act->sig;
            ant = act->ant;
            if(ant)
            {
                ant->sig = sig;
            }
            if(sig)
            {
                sig->ant = ant;
                *l = sig;
            }
            else
            {
                *l = ant;
            }

            free(act->info);
            free(act);
        }

        act = act->ant;
    }
    act = aux->sig;
    while(act)
    {
        if(!filtro(act->info, f))
        {
            sig = act->sig;
            ant = act->ant;
            if(ant)
            {
                ant->sig = sig;
            }
            if(sig)
            {
                sig->ant = ant;
                *l = sig;
            }
            else
            {
                *l = ant;
            }

            free(act->info);
            free(act);
        }
        act = act->sig;
    }
}

void map(tLista* l, const void* elemMapeo, void (*accion)(void**, unsigned*, const void*)){
    tNodo* act = *l;
    while(act){

        accion(&act->info, &act->tamInfo, elemMapeo);
        act = act->sig;
    }
    act = (*l)->ant;
    while(act){

        accion(&act->info, &act->tamInfo, elemMapeo);
        act = act->ant;
    }

}

void reduce(tLista* l, void* resultado, void(*accion)(void**, unsigned*, void*)){

    tNodo* act = *l;
    while(act){

        accion(&act->info, &act->tamInfo, resultado);
        act = act->sig;
    }
    act = (*l)->ant;
    while(act){

        accion(&act->info, &act->tamInfo, resultado);
        act = act->ant;
    }

}
