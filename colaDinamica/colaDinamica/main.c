#include "colaDinamica.h"
#include "simulacion35.h"

int _testCola();


int main()
{
    srand(time(NULL));

    simulacion();

    return 0;
}


int _testCola(){


    tCola cola;
    int num = 4, buffer, errores=0;

    crearCola(&cola);

    if(!encolar(&cola,&num,sizeof(num))){
        puts("Error encolando");
        errores++;
    }

    if(!verTope(&cola, &buffer, sizeof(buffer))){
        puts("Error viendo primero");
        errores++;
    }
    else{
        printf("Viendo primero exitoso %d\n", buffer);
    }

    if(!desencolar(&cola,&buffer,sizeof(buffer))){
        puts("Error desencolando");
        errores++;
    }else{
        printf("ELEMENTO: %d\n", buffer);
    }

    if(!desencolar(&cola,&buffer,sizeof(buffer))){
        puts("Desencolando una cola vacia");
    }

    if(colaVacia(&cola)){
        puts("Todo bien");
    }else{
        errores++;
    }

    vaciarCola(&cola);


    return errores;


}
