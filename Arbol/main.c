#include "arbol.h"
#include <locale.h>
void grabarEntero(void* , unsigned,unsigned, void*);
int cmpEnteros(const void*, const void*);
void map_multiplicarEnteroPorN(void*, unsigned,unsigned,void*);
void acumularEntero(void*, unsigned,unsigned,void*);
int main()
{
    Arbol a;
    tNodo* encontrado;
    FILE* archivo = fopen("arch.txt", "wt");
    int i, n[] = {100,50,75,100,5,105,200,5}, inser, clave =50, map_param = 2, resultado_suma_reduce=0, resultado_suma_hojas=0, resultado_suma_no_hojas=0;
    if (setlocale(LC_ALL, "Spanish_Spain.1252") == NULL) {
        fprintf(stderr, "Error setting locale\n");
        return 1;
    }

    crearArbol(&a);

    if(!archivo){
        puts("ERROR");
        return 1;
    }
    for(i=0;i<sizeof(n)/sizeof(n[0]);i++){
        inser = insertarNodoOrdenado_iterativo(&a, n+i,sizeof(n[i]),cmpEnteros);
        if(inser==0){
            printf("ERROR INSERTANDO NUMERO %dº\n",i);
        }
        else if (inser== 2){
            printf("DUPLICADO ELEMENTO NUMERO %dº\n", i);
        }
        else{
            printf("ELEMENTO INSERTADO CORRECTAMENTE %dº\n", i);
        }
    }
    puts("-------------------------ALTURA DEL ARBOL-------------------------");
    printf("%d\n",alturaArbolBin(&a));

    puts("-------------------------RECORRIDOS RECURSIVOS-------------------------");
    puts("ARBOL PRE ORDEN");
    RecorrerArbolPreOrden_r(&a,stdout, grabarEntero);
    puts("ARBOL POST ORDEN");
    RecorrerArbolPostOrden_r(&a, stdout, grabarEntero);
    puts("ARBOL ORDENADO");
    RecorrerArbolOrden_r(&a, stdout, grabarEntero);
    puts("ARBOL PRE ORDEN INVERSO");
    RecorrerArbolPreOrdenInverso_r(&a,stdout, grabarEntero);
    puts("ARBOL POST ORDEN INVERSO");
    RecorrerArbolPostOrdenInverso_r(&a, stdout, grabarEntero);
    puts("ARBOL ORDEN INVERSO IMPRESO EN TXT");
    RecorrerArbolOrdenInverso_r(&a,(void*)archivo, grabarEntero);

//    puts("-------------------------RECORRIDOS ITERATIVOS-------------------------");

    puts("-------------------------RECORRIDO SEGUN NIVEL-------------------------");
    puts("Ver hasta un nivel particular");
    verTodosLosNodosHastaNivel(&a,stdout, 10, grabarEntero);
    puts("Ver de un nivel en particular");
    verTodosLosNodosDeUnNivel(&a,stdout,2,grabarEntero);
    puts("Ver desde un nivel en particular");
    verTodosLosNodosDesdeNivel(&a,stdout,1,grabarEntero);
    puts("USANDO NIVEL 1");
    puts("Ver desde un nivel en particular con funcion interina para aprovechar todos los recorridos");
    int nivel_objetivo= 1;
    RecorrerArbolOrden_r(&a,&nivel_objetivo,MostrarEnteroDesdeNivel);
    puts("Ver de un nivel en particular con funcion interina para aprovechar todos los recorridos");
    RecorrerArbolPostOrden_r(&a,&nivel_objetivo,MostrarEnteroDeNivel);
    puts("Ver hasta un nivel en particular con funcion interina para aprovechar todos los recorridos");
    RecorrerArbolPreOrdenInverso_r(&a,&nivel_objetivo,MostrarEnteroHastaNivel);

    puts("-------------------------BUSQUEDA DE CLAVE-------------------------");
    printf("BUSCANDO NUMERO (nodo)%d\n", clave);
    if((encontrado= busquedaArbol_nodo(&a, &clave, cmpEnteros))){
        printf("SE ENCONTRO EL NUMERO:");
        grabarEntero(encontrado->info,0, encontrado->tamInfo,stdout);
        puts("");
    }
    else{
        puts("NO SE ENCONTRO EL NUMERO");
    }

    printf("BUSCANDO NUMERO (info)%d\n", clave);
    void* infoBuscada;
    if((infoBuscada = busquedaArbol_info(&a, &clave, cmpEnteros))!=NULL){
        printf("SE ENCONTRO EL NUMERO (info):");
        grabarEntero(infoBuscada,0, 0,stdout);
        puts("");
    }
    else{
        puts("NO SE ENCONTRO EL NUMERO (info)");
    }

    printf("BUSCANDO NUMERO (subarbol)%d\n", clave);
    Arbol* subarbol;
    if((subarbol= busquedaArbol_subArbol(&a, &clave, cmpEnteros))!=NULL){
        puts("SUBARBOL encontrado");
        RecorrerArbolPreOrden_r(subarbol,stdout,grabarEntero);
        puts("");
    }
    else{
        puts("NO SE ENCONTRO EL NUMERO (subarbol)");
    }

    puts("Buscando clave mayor");
    encontrado = busquedaMayorClaveArbol_ORDENADO(&a, cmpEnteros);
    grabarEntero(encontrado->info,0, encontrado->tamInfo,stdout);
    puts("Buscando clave menor");
    encontrado = busquedaMenorClaveArbol_ORDENADO(&a, cmpEnteros);
    grabarEntero(encontrado->info,0, encontrado->tamInfo,stdout);
    puts("Buscando clave mayor que no sea el 200");
    int clav200 = 200;
    encontrado= busquedaMayorNoClaveArbol_ORDENADO(&a,&clav200,cmpEnteros);
    grabarEntero(encontrado->info,0, encontrado->tamInfo,stdout);
    puts("Buscando clave menor que no sea el 5");
    int clav5= 5;
    encontrado = busquedaMenorNoClaveArbol_ORDENADO(&a,&clav5,cmpEnteros);
    grabarEntero(encontrado->info,0, encontrado->tamInfo,stdout);

    puts("-------------------------FUNCIONES DE HOJAS-------------------------");
    printf("CANTIDAD DE HOJAS: %d\n", contarHojas(&a));
    puts("Mostrando hojas");
    RecorrerHojas(&a,stdout,grabarEntero);
    puts("Sumando hojas");
    RecorrerHojas(&a,&resultado_suma_hojas, acumularEntero);
    printf("La suma de las hojas es: %d\n", resultado_suma_hojas);

    puts("-------------------------FUNCIONES DE NO HOJAS-------------------------");
    printf("CANTIDAD DE NO HOJAS: %d\n", contarNoHojas(&a));
    puts("Mostrando No hojas");
    RecorrerNoHojas(&a,stdout,grabarEntero);
    puts("Sumando hojas");
    RecorrerNoHojas(&a,&resultado_suma_no_hojas, acumularEntero);
    printf("La suma de las hojas es: %d\n", resultado_suma_no_hojas);

    puts("-------------------------MAP FILTER REDUCE-------------------------");
    puts("MAPEO DE ARBOL");
    mapC(&a,&map_param,map_multiplicarEnteroPorN);
    RecorrerArbolOrden_r(&a,stdout,grabarEntero);

    puts("REDUCE DEL ARBOL SUMANDO TODOS LOS NODOS");
    ReduceC(&a,&resultado_suma_reduce, acumularEntero);
    printf("RESULTADO: %d\n", resultado_suma_reduce);

    puts("-------------------------DESTRUCCION DEL ARBOL-------------------------");
    destruirArbol(&a);
    RecorrerArbolOrden_r(&a,stdout,grabarEntero);
    if(arbolVacio(&a)){
        puts("El arbol fue correctamente eliminado");
    }
    else{
        puts("Problema eliminando arbol");
    }



    fclose(archivo);
    return 0;
}

void grabarEntero(void*a, unsigned nivel, unsigned tam,  void* out){
    fprintf(out,"%d\n", *(int*)a);
}

int cmpEnteros(const void* a, const void* b){
    return (*((int*)a) - *((int*)b));
}

void map_multiplicarEnteroPorN(void* elem, unsigned nivel,unsigned tam,void* map_Param){
    int* num = (int*)elem;
    *num *= *(int*)map_Param;
}

void acumularEntero(void* elem, unsigned nivel, unsigned tam, void* resultado){
    *(int*)resultado += *(int*)elem;
}
