#include "lista.h"
#include "productos.h"

#define ARCHIVOBIN "productos.bin"

/*TEST DE LISTA DINAMICA*/
void testRecursive();
void testReduce();
void testFilterPy();
void testFilterC();
void testMapEnPy();
void testMapEnC();
void testInsertarNNodosDespuesClaveV2();
void testInsertarNNodosDespuesClave();
void testEliminarNUltimosNodos(); //falta terminar la recursiva
void testEliminarNNodos();
void testEliminarNoDuplicados();
void testInsercionEliminacionxPosicion();
void testEliminacionxClave();
void testListaOrdenamientos();
void testLista();
void testProducto();
void mostrarEntero(const void*, FILE*);
int compararClaveNumeros(const void* nodo, const void* clave);
void sumarAElementoEntero(void* nodo);
int filtrarEnterosMayores(const void* info, const void* filtro);
int filtrarEnterosMenores(const void* info, const void* filtro);
void acumulaEnteros(const void* info, void* resultado);

int main()
{
    generarLotePruebas();
    testRecursive();

    return 0;
}

void testRecursive()
{
    tLista list;
    int n[]= {1,2,3,4,5,6,7,8,9,10},i;
    for(i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        ponerEnListaUltimo(&list,n + i, sizeof(int));
    }

    showRecursiveList(&list,mostrarEntero);

    puts("NOW BACKWARDS");
    showRecursiveListBackwards(&list, mostrarEntero);

    vaciarLista(&list);
}

void testReduce()
{
    tLista lista;
    int resultado = 0;
    int numeros[]= {1,2,3,4,5,6,7,8,9,10}, i;
    crearLista(&lista);
    for(i=0; i<sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        ponerEnListaUltimo(&lista,numeros + i, sizeof(int));
    }

    reduce(&lista, &resultado, acumulaEnteros);

    printf("RESULTADO DE LA ACUMULACION: %d", resultado);

    vaciarLista(&lista);
}

void testFilterPy()
{

    tLista lista, resultado;
    int numeros[]= {1,2,3,4,5,6,7,8,9,10}, i;
    int filtro = 6;
    crearLista(&lista);
    for(i=0; i<sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        ponerEnListaUltimo(&lista,numeros + i, sizeof(int));
    }

    resultado = filterPy(&lista, &filtro, filtrarEnterosMenores);

    mostrarLista(&resultado, mostrarEntero, stdout);

    vaciarLista(&lista);
    vaciarLista(&resultado);

}


void testFilterC()
{
    tLista lista;
    int filtro = 4;
    int numeros[]= {1,2,3,4,5,6,7,8,9,10}, i;
    crearLista(&lista);
    for(i=0; i<sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        ponerEnListaUltimo(&lista,numeros + i, sizeof(int));
    }

    filterC(&lista, &filtro, filtrarEnterosMayores);

    mostrarLista(&lista, mostrarEntero, stdout);



    vaciarLista(&lista);
}

void testMapEnPy()
{
    tLista lista, resultado;

    int numeros[]= {1,2,3,4,5,6,7,8,9,10}, i;
    crearLista(&lista);
    for(i=0; i<sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        ponerEnListaUltimo(&lista,numeros + i, sizeof(int));
    }
    resultado = mapPy(&lista, sumarAElementoEntero);

    mostrarLista(&resultado,mostrarEntero,stdout);



    vaciarLista(&lista);
    vaciarLista(&resultado);
}

void testMapEnC()
{

    tLista lista;

    int numeros[]= {1,2,3,4,5,6,7,8,9,10}, i;
    crearLista(&lista);
    for(i=0; i<sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        ponerEnListaUltimo(&lista,numeros + i, sizeof(int));
    }

    mapC(&lista, sumarAElementoEntero);

    mostrarLista(&lista, mostrarEntero,stdout);


    vaciarLista(&lista);


}

void testInsertarNNodosDespuesClaveV2()
{

    tLista lista;
    tProducto prod[]= {{'h',55,"PRUEBAAAAA", 350.99, "AAAAAAAAAAAAAAA"}, {'y',55,"PRUEBAAAAABBBBB", 350.99, "AAAAAAAAAAAAAAA"},{'o',55,"AAPRUEBAAAAA", 350.99, "AAAAAAAAAAAAAAA"}};
    char clave = 'y';
    int res;
    crearLista(&lista);

    leerBinALista(ARCHIVOBIN, &lista);
    res = insertarDespuesClaveNNodosV2(&lista,&prod, &clave, sizeof(tProducto),comparaProductosXClaveCodigo,sizeof(prod)/sizeof(prod[0]));
    if(res == 1)
    {
        mostrarLista(&lista, mostrarProducto, stdout);
    }
    else if (res == ERROR_MEMORIA)
    {
        puts("ERROR MEMO");
    }
    else if (res == LISTA_VACIA)
    {
        puts("MEMO VACIA");
    }

    ponerEnListaUltimo(&lista, &prod, sizeof(tProducto));

    mostrarLista(&lista, mostrarProducto, stdout);
    vaciarLista(&lista);
}


void testInsertarNNodosDespuesClave()
{

    tLista lista;
    tProducto prod= {'h',55,"PRUEBAAAAA", 350.99, "AAAAAAAAAAAAAAA"};
    char clave = 'y';
    int res;
    crearLista(&lista);

    leerBinALista(ARCHIVOBIN, &lista);
    res = insertarDespuesClaveNNodos(&lista,&prod, &clave, sizeof(tProducto),comparaProductosXClaveCodigo,3);
    if(res == 1)
    {
        mostrarLista(&lista, mostrarProducto, stdout);
    }
    else if (res == ERROR_MEMORIA)
    {
        puts("ERROR MEMO");
    }
    else if (res == LISTA_VACIA)
    {
        puts("MEMO VACIA");
    }

    ponerEnListaUltimo(&lista, &prod, sizeof(tProducto));

    mostrarLista(&lista, mostrarProducto, stdout);

    vaciarLista(&lista);

}

void testEliminarNUltimosNodos()
{
    tLista lista;
    int numeros[]= {1,2,3,4,5,6,7,8,9,10};
    int numNuevo = 33;
    crearLista(&lista);
    for(int i=0; i< sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        ponerEnListaUltimo(&lista, numeros+i, sizeof(numeros[i]));
    }

    int eliminados = eliminarNUltimosNodos(&lista, 3);
    printf("ELIMINADOS %d\n",eliminados);

    ponerEnListaPrimero(&lista,&numNuevo,sizeof(numNuevo));
    ponerEnListaUltimo(&lista,&numNuevo,sizeof(numNuevo));
    mostrarLista(&lista,mostrarEntero,stdout);

    vaciarLista(&lista);

}


void testEliminarNNodos()
{

    tLista lista;
    char clave = 'x';
    crearLista(&lista);

    leerBinALista(ARCHIVOBIN, &lista);

    if(eliminarDespuesClaveNNodos(&lista,&clave,comparaProductosXClaveCodigo,3))
    {
        mostrarLista(&lista,mostrarProducto,stdout);
    }
    else
    {
        puts("Error eliminando o pos==0");
    }

    vaciarLista(&lista);
}

void testEliminarNoDuplicados()
{

    tLista lista;

    crearLista(&lista);

    leerBinALista(ARCHIVOBIN, &lista);

    int eliminadas = eliminarNoDuplicados(&lista, comparaProductosXClaveCodigo,NULL);

    mostrarLista(&lista, mostrarProducto,stdout);

    printf("ELIMINADOS: %d\n", eliminadas);


    vaciarLista(&lista);

}

void testInsercionEliminacionxPosicion()
{
    tLista lista;
//    tProducto prodNuevo = {'N', 10, "Agua gasificada", 580.99, "No se me quede sin ideas"};
    int pos= 2;
    crearLista(&lista);

    leerBinALista(ARCHIVOBIN,&lista);
    /*if(insertarEnPosicion(&lista, &prodNuevo,sizeof(tProducto), pos)){
        mostrarLista(&lista, mostrarProducto,stdout);
    }
    else{
        puts("Error");
    }*/
    mostrarLista(&lista, mostrarProducto,stdout);
    puts("LUEGO BORRAR--------------------------------------------------------------------------");
    if(EliminarEnPosicion(&lista, pos))
    {
        mostrarLista(&lista, mostrarProducto,stdout);
    }
    else
    {
        puts("Error");
    }


    vaciarLista(&lista);

}


void testEliminacionxClave()
{
    tLista lista;
    char clave = 'a';
//    int ocurrenciasEliminadas;
    crearLista(&lista);


    leerBinALista(ARCHIVOBIN,&lista);
    mostrarLista(&lista,mostrarProducto,stdout);
    puts("\nPOST ELIMINACION DE CLAVE---------------------------------------------------------------------------------------------------");
    eliminarUltimaOcurrenciaClave(&lista, &clave, comparaProductosXClaveCodigo);
    mostrarLista(&lista, mostrarProducto,stdout);


//    leerBinAListaEnOrden(ARCHIVOBIN, &lista);
//    eliminarPrimeraOcurrenciaClave(&lista,&clave,comparaProductosXClaveCodigo);
//    mostrarLista(&lista,mostrarProducto,stdout);

    /*   leerBinALista(ARCHIVOBIN,&lista);
       mostrarLista(&lista, mostrarProducto,stdout);
       puts("\nPOST ELIMINACION DE CLAVE---------------------------------------------------------------------------------------------------");
       ocurrenciasEliminadas= eliminarTodasOcurrenciasClave(&lista,&clave, comparaProductosXClaveCodigo);
       mostrarLista(&lista, mostrarProducto,stdout);
       printf("OCURRENCIAS ELIMINADAS: %d\n", ocurrenciasEliminadas);*/

    vaciarLista(&lista);
}

void testListaOrdenamientos()
{


    tLista lista;
    tLista lista2;

    crearLista(&lista);
    crearLista(&lista2);

    leerBinALista(ARCHIVOBIN,&lista);
    ordenarLista(&lista,cmpProductosCodigo);
    mostrarLista(&lista, mostrarProducto, stdout);

    puts("LISTA INSERTAR EN ORDEN");
    leerBinAListaEnOrden(ARCHIVOBIN,&lista2);
    mostrarLista(&lista2,mostrarProducto,stdout);


    vaciarLista(&lista);
}

void testLista()
{


    tLista lista;
    tLista* nodoBuscado;
    int numeros[]= {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
    int i, clave =15;
    void* info_ptr;

    crearLista(&lista);


    for(i=0; i<sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        ponerEnListaUltimo(&lista, (numeros + i), sizeof(numeros + i));
    }

    info_ptr = buscarInfoPorClave(&lista, &clave, sizeof(int), compararClaveNumeros);

    if (!info_ptr)
    {
        printf("No encontrado");
    }
    else
    {
        int* info = (int*)info_ptr;
        printf("INFO : %d\n", *info);
    }

    nodoBuscado = buscarNodoPorClave(&lista, &clave, sizeof(int), compararClaveNumeros);

    if(!nodoBuscado)
    {
        printf("Nodo no encontrado");
    }
    else
    {
        int* n = (int*)((*nodoBuscado)->info);
        printf("NODO INFO %d", *n);
    }

    testProducto();

    vaciarLista(&lista);
}

void testProducto()
{

    tProducto prod= {'b',10,"lata tomate", 350.99, "Marolio"};
    char clave = 'c';
    int cmp;
    tNodo nodo;
    nodo.info = malloc(sizeof(tProducto));
    if (nodo.info == NULL)
    {
        printf("Error: no se pudo asignar memoria para nodo.info\n");
        return;
    }
    memcpy((nodo.info), &prod, sizeof(tProducto));
    nodo.tamInfo= sizeof(tProducto);
    nodo.sig=NULL;
    cmp = comparaProductosXClaveCodigo(&nodo,&clave);

    printf("\nCMP CODIGO PROD: %d", cmp);


}




void mostrarEntero(const void* elem, FILE* fp)
{
    int* num = ((int*)elem);
    fprintf(fp,"Elemento de lista: %d\n", *num);
}


int compararClaveNumeros(const void* nodo, const void* clave)
{
    const int* num = (const int*)clave;
    int* infoNum = (int*)((nodo));
    int resul = ((*num)-(*infoNum));
    return resul;
}

void sumarAElementoEntero(void* nodo)
{

    int* num = (int*)nodo;

    *num = (*num) + 10;
}

int filtrarEnterosMayores(const void* info, const void* filtro)
{

    int* a = (int*)info;
    int* f = (int*)filtro;

    if((*a)>(*f))
    {
        return 1;
    }
    else
    {
        return 0;
    }

}


int filtrarEnterosMenores(const void* info, const void* filtro)
{


    int* a = (int*)info;
    int* f = (int*)filtro;

    if((*a)<(*f))
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

void acumulaEnteros(const void* info, void* resultado)
{
    int* a = (int*)info;
    int* res = (int*)resultado;

    (*res)+= *a;

}
