#include "listaCircular.h"
void mostrarEntero(const void* a);
int cmpEnteros(const void*a, const void*b);
int main()
{
    int n[] = {1,3,0,5,3,7,4,7,2,5,10,2,24,8};
    int i;
    tLista l;


    crearLista(&l);
    for(i=0;i<sizeof(n)/sizeof(n[0]);i++){
        if(!insertarOrdenado(&l, n+i, sizeof(n[i]),cmpEnteros,NULL)){
            puts("ERROR INSERTANDO");
        }
    }

    mostrarLista(&l, mostrarEntero);
    puts("Vaciando");
    vaciarLista(&l);

    mostrarLista(&l, mostrarEntero);
    return 0;
}

int cmpEnteros(const void*a, const void*b){
    return (*(int*)a - *(int*)b);
}

void mostrarEntero(const void* a){
    int* n = (int*)a;
    printf("%d ", *n);
}
