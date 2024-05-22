#include "colaCircular.h"

int main()
{
    tCola c;
    int i=10, tope;
    crearCola(&c);
    while(i)
    {
        if(!encolar(&c,&i,sizeof(i)))
        {
            puts("ERROR ENCOLANDO");
        }
        i--;
    }
    if(!verPrimero(&c,&tope,sizeof(tope)))
    {
        puts("ERROR VIENDO TOPE");
    }
    else
    {
        printf("TOPE: %d\n", tope);
    }

    if(!desencolar(&c, &tope, sizeof(tope)))
    {
        puts("ERROR DESENCOLANDO");
    }


    if(!verPrimero(&c,&tope,sizeof(tope)))
    {
        puts("ERROR VIENDO TOPE");
    }
    else
    {
        printf("TOPE LUEGO DE DESENCOLAR: %d\n", tope);
    }


    vaciarCola(&c);

    if(!colaVacia(&c)){
        puts("ERROR VACIANDO COLA");
    }
    else{
        puts("COLA VACIADA CON EXITO.");
    }

    return 0;
}
