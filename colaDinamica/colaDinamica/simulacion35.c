#include "simulacion35.h"


/*
tATENCION 135
tLLEGADA 159

Puedo calcular el t en el que llega la primer persona, tA=0 y tL = 5 por ejemplo,
Pasan 5 minutos entonces llega alguien a la cola, se le asigna tA= 3 por ejemplo
Se agrega un tL= 1, entonces en un minuto pasa algo, llega un cliente.
Ttotal = 6 pq 5 + 1
tA = 2 pq paso un minuto. Encolamos el tA del que llego pq sé que tramite tiene por asi decirlo.
El proximo tarda un minuot en llegar, ocurre otro salto de un minuto.
tA= 1 pq paso otro minuto.
tL = 5, pasa otro minuto pq es el que le queda de atencion al actual
tA=0 -> desencolo

tL= 4 por ese minuto que pasó.
Pasan 4 minutos del tL y tA= 1 que es lo que está en la cola
llega alguien nuevo en 9 minutos
pasa un minuto , entonces tL=8
tA = 0 desencolo ....



*/


int simulacion()
{

    tCola cola;
    crearCola(&cola);

    int tiemposCaja[]= {1,3,5}, tiemposLlegada[]= {1,5,9};
    int tLlegada=0, tCaja=0,personasAtendidas =0, vecesVacia =0, tTotal=0, tTranscurrido, tTramite;

    puts("---------SIMULACION CAJERO AUTOMATICO---------");

    tTotal += tiemposLlegada[rand()%3];
    tTramite = tiemposCaja[rand()%3];
    encolar(&cola,&tTramite,sizeof(tTramite));

    tLlegada = tiemposLlegada[rand()%3];

    verTope(&cola, &tCaja,sizeof(tCaja));
    while(vecesVacia<5)
    {

        tTranscurrido = MINIMO(tCaja, tLlegada);

        tCaja-= tTranscurrido;
        tLlegada -= tTranscurrido;
        tTotal+= tTranscurrido;

        if(!tCaja)
        {
            personasAtendidas++;
            desencolar(&cola,&tTramite,sizeof(tTramite));

            if(colaVacia(&cola) && tLlegada>0)
            {
                tTranscurrido+=tLlegada;
                tLlegada=0;
                vecesVacia++;
            }
            else if (!colaVacia(&cola))
            {
                verTope(&cola, &tCaja,sizeof(tCaja));
            }



        }

        if(!tLlegada)
        {
            tTramite = tiemposCaja[rand()%3];
            encolar(&cola,&tTramite,sizeof(tTramite));


            tLlegada = tiemposLlegada[rand()%3];

            if(!tCaja)
            {
                verTope(&cola, &tCaja,sizeof(tCaja));
            }

        }
    }

    printf("Personas atendidas: %d, tiempo total %d.\n", personasAtendidas, tTotal);

    return 1;
}
