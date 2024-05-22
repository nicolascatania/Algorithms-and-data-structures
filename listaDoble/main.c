#include "utilidades.h"
#include "listaDoble.h"
#include "testLD.h"
#include "productos.h"


int testProd();
int actualizarProductos();

int main()
{
    tLista l;
    crearLista(&l);
    _probarEliminarTodasCLaves(&l);
    vaciarLista(&l);

}

int testProd()
{

    if(actualizarProductos())
    {
        puts("Actualizacion exitosa.");
        return 0;
    }


    return 1;


}


int actualizarProductos()
{

    tLista listaIndices;
    crearLista(&listaIndices);

    genMaestroYMovimientos();

    if(!obtenerIndices(ARCHMAESTRO, &listaIndices))
    {
        puts("FALLA OBTENIENDO INDICES.");
        vaciarLista(&listaIndices);
        return 0;
    }

//    mostrarIzqDer(&listaIndices,mostrarProdIndice);
    puts("MOSTRANDO ARCHIVO MAESTRO");
    if(!mostrarMaestro(ARCHMAESTRO))
    {
        puts("FALLA EN MOSTRAR MAESTRO.");
        vaciarLista(&listaIndices);
        return 0;
    }

    if(!actualizarMaestro(ARCHMAESTRO, ARCHMOVIMIENTOS, &listaIndices))
    {
        puts("FALLA ACTUALIZANDO MAESTRO.");
        vaciarLista(&listaIndices);
        return 0;
    }


    puts("\n\n\nMOSTRANDO ARCHIVO MAESTRO LUEGO ACTUALIZACION");
    if(!mostrarMaestro(ARCHMAESTRO))
    {
        puts("FALLA EN MOSTRAR MAESTRO.");
        vaciarLista(&listaIndices);
        return 0;
    }

    vaciarLista(&listaIndices);
    return 1;

}
