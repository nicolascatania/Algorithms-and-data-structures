#include "pilacircular.h"
int main()
{
    tPila pila;
    int num = 5, tope,i;
    int numeros[] = {1,2,3,4,5,6,7};
    crearPila(&pila);

    if(!pilaVacia(&pila))
    {
        puts("PILA VACIA FALLO");
    }

    if(pilaLlena(&pila, &num, sizeof(num)))
    {
        puts("PILA LLENA FALLO");
    }

    ponerEnPila(&pila, &num,sizeof(num));

    if(!verTope(&pila,&tope,sizeof(tope)))
    {
        puts("FALLO VER TOPE");
    }
    else
    {
        printf("ELEMENTO TOPE: %d\n", tope);
    }

    if(pilaVacia(&pila))
    {
        puts("PILA VACIA FALLO");
    }

    for(i=0; i<sizeof(numeros)/sizeof(numeros[0]); i++)
    {
        if(!ponerEnPila(&pila, numeros + i,sizeof(numeros[i])))
        {
            puts("FALLO PONER EN PILA");
        }
        if(!verTope(&pila,&tope,sizeof(tope)))
        {
            puts("FALLO VER TOPE");
        }
        else
        {
            printf("ELEMENTO TOPE: %d\n", tope);
        }

    }


    if(!sacarDePila(&pila, &tope, sizeof(tope)))
    {
        puts("ERROR SACANDO DE PILA");
    }
    else
    {
        printf("ELEMENTO SACADO: %d\n", tope);
    }

    verTope(&pila, &tope, sizeof(tope));
    printf("ELEMENTO TOPE: %d\n", tope);


    vaciarPila(&pila);

    if(!verTope(&pila,&tope,sizeof(tope)))
    {
        puts("PILA VACIA EXITOSO");
    }
    else
    {
        printf("FALLO, NO DEBERIA EXISTIR ELEMENTO TOPE: %d\n", tope);
    }

    return 0;
}
