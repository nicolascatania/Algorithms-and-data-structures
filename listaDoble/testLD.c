#include "testLD.h"
#include "productos.h"
#include "utilidades.h"


void _probarFiltro(tLista *l)
{

    int numeros[] = {2,6,23,5,10,1,2,16,2,15,2,61,10,2};
    int clave = 10, i ;
    for(i=0; i< sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        insertarAlFinal(l, numeros + i, sizeof(numeros[0]));
    }

    filter(l, &clave, filtrarEnterosMayoresA);

    mostrarIzqDer(l, mostrarEntero);
}

void _probarResumirLista(tLista *l)
{

//    int numeros[]= {0,2,2,3,0,5,1,2,3}; //el algoritmo no funca con numeros pq estoy modificando los mismos valores con los que comparo, ver ejemplo en libreta.

    genMaestroYMovimientos();

    productosALista(ARCHMAESTRO, l);
    puts("LISTA SIN RESUMEN");
    mostrarIzqDer(l, mostrarProducto);

    puts("\nLISTA RESUMIDA");
    resumirOcurrencias(l, strcmp, acumularProductoMenorStock);
    mostrarIzqDer(l,mostrarProducto);

}


int _probarBuscarPorClave()
{

    tLista lista;
    tLista* buscado;
    tNodo* aux;
    int n[]= {777,1,2,54,223,50,50,23,0,5,77,888,999,50};
    int i, clave = 2;

    crearLista(&lista);

    for(i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        insertarEnOrden(&lista, n+i,sizeof(n[i]),cmpEnteros,acumularEnteros);
    }

    mostrarIzqDer(&lista, mostrarEntero);

    buscado = buscarPorClave_ord(&lista, &clave, cmpEnteros);


    if(buscado)
    {
        puts("\nENCONTRAO");
        aux = *buscado;
        if(aux)
        {
            int* encontrado = aux->info;
            printf("ENCONTRAO : %d\n", *encontrado);
            return 1;
        }
        else
        {
            puts("ERROR AUX");
            return 0;
        }
    }
    else
    {
        puts("\nNO ENCONTRAO");
        return 0;
    }

    return 1;
}




void _probarEliminarTodasCLaves(tLista* l)
{
    int numeros[] = {2,6,23,5,10,1,2,16,2,15,2,61,10,2};
    int clave = 2, i ;
    for(i=0; i< sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        insertarAlFinal(l, numeros + i, sizeof(numeros[0]));
    }
    puts("LISTA ORIGINAL");
    mostrarIzqDer(l,mostrarEntero);
    puts("\n\nLISTA CON CLAVE ELIMINADA Y ELEMENTOS AGREGADOS EN INICIO FIN Y ORDENADO");
    i = eliminarClaves(l,&clave,cmpEnteros);
    printf("CLAVE A ELIMINAR: %d\n",clave);
    printf("Insertando %d al inicio, insertando %d en orden relativo e insertando %d al final\n", numeros[5], numeros[7], numeros[2]);
    insertarAlFinal(l,&numeros[2],sizeof(int));
    insertarAlComienzo(l, &numeros[5], sizeof(int));
    insertarEnOrden(l, &numeros[7], sizeof(int), cmpEnteros,NULL);
    mostrarIzqDer(l,mostrarEntero);
    printf("\nCLAVES ELIMINADAS: %d\n", i);
}

void _probarEliminarPorClave(tLista* l)
{

    int numeros[] = {2,6,23,5,10,1,16,61,10};
    int clave = 10, i ;
    for(i=0; i< sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        insertarAlFinal(l, numeros + i, sizeof(numeros[0]));
    }

    eliminarPorClave(l, &clave, sizeof(clave), cmpEnteros);

    mostrarIzqDer(l,mostrarEntero);

}


void _probarOrdenarLista(tLista* l)
{

    int numeros[]= {2,6,23,5,58,10,1,16,61,10};

    int i;

    for(i=0; i< sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        insertarAlFinal(l, numeros + i, sizeof(numeros[0]));
    }
    mostrarIzqDer(l,mostrarEntero);
    puts("\nDESPUES DE ORDENAR");

    OrdenarLista(l,cmpEnteros);

    mostrarIzqDer(l,mostrarEntero);

}

void _probarInsercionOrdenada(tLista* l)
{

//    int numeros[]= {2,3,4,5,7,8,10,11,21};
    int numeros[]= {2,55,2,60,23,1,54,23,6};
//    int insertar[]= {1,15,30,30};
    int i;
//    int i,j;

    for(i=0; i<sizeof(numeros)/sizeof(numeros[0]); i++)
    {

        insertarEnOrden(l,numeros+i, sizeof(numeros[i]),cmpEnteros,acumularEnteros);
        mostrarIzqDer(l,mostrarEntero);
        puts("");
//        if(!insertarAlFinal(l,numeros+i,sizeof(numeros[0])))
//        {
//            printf("Error insertando elemento %d\n", i+1);
//        }
    }

//    for(j=0; j<sizeof(insertar)/sizeof(insertar[0]); j++)
//    {
//        insertarEnOrden(l,insertar+j,sizeof(insertar[0]),cmpEnteros,acumularEnteros);
//        mostrarIzqDer(l,mostrarEntero);
//        puts("");
//    }

}

void _probarInsercionAlComienzo(tLista* l)
{

    int numeros[]= {1,2,3,4,5,6,7,8,9,10,55};
    int i, error =0;


    for(i=0; i< sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        if(!insertarAlComienzo(l,numeros+i,sizeof(numeros[0])))
        {
            printf("Error insertando elemento %d\n", i+1);
            error = 1;
        }

    }

    if(!error)
    {
        puts("Insercion exitosa");
    }

    _probarMostrarIzqDer(l, sizeof(numeros)/sizeof(numeros[0]));
    _probarEliminarLista(l);

}


void _probarInsercionAlFinal(tLista* l)
{


    int numeros[]= {1,2,3,4,5,6,7,8,9,10};
    int i;

    for(i=0; i< sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        if(!insertarAlFinal(l,numeros+i,sizeof(numeros[0])))
        {
            printf("Error insertando elemento %d\n", i+1);
        }

    }

    _probarMostrarIzqDer(l, sizeof(numeros)/sizeof(numeros[0]));
    _probarEliminarLista(l);


}

int _probarMostrarIzqDer(tLista* l, int ce)
{

    int mostrados;

    mostrados= mostrarIzqDer(l,mostrarEntero);
    puts("");
    if(mostrados != ce)
    {
        puts("Cantidad de elementos mostrada es erronea, hubo un error en mostrar elementosIzqDer o en la insercion de los mismos.");
        printf("SE MOSTRARON %d ELEMENTOS.\n", mostrados);
        return 0;
    }

    return 1;

}

int _probarMostrarDerIzq(tLista* l, int ce)
{

    int mostrados;

    mostrados= mostrarDerIzq(l,mostrarEntero);
    puts("");
    if(mostrados != ce)
    {
        puts("Cantidad de elementos mostrada es erronea, hubo un error en mostrar elementosIzqDer o en la insercion de los mismos.");
        printf("SE MOSTRARON %d ELEMENTOS.\n", mostrados);
        return 0;
    }

    return 1;

}

int _probarEliminarLista(tLista* l)
{

    vaciarLista(l);

    if(!mostrarIzqDer(l,mostrarEntero))
    {
        puts("\nLista eliminada con exito.");
        return 1;
    }
    else
    {
        puts("\nProblema eliminando la lista");
        return 0;
    }


}
