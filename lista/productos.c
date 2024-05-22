#include "productos.h"

int acumularStockProducto(void** elem, unsigned* tamElem, const void* aAcumular, unsigned tamAElemAcumular)
{

    tProducto* prod = *((tProducto**)elem);

    prod->stock+= ((tProducto*)aAcumular)->stock;

    return 1;

}



int cmpProductosCodigo(const void* a, const void* b)
{
    tProducto* pa = (tProducto*)(a);
    tProducto* pb = (tProducto*)(b);

    //hacer el tolower para esta funcion en particular

    return ((pa)->codigo - (pb)->codigo);

}



int comparaProductosXClaveCodigo(const void* info, const void* clave)
{

    char* claveCod = (char*)clave;
    tProducto* prod = (tProducto*)(info);

    return (prod->codigo) - (*claveCod); //siempre a - b;


}

int leerBinAListaEnOrden(const char* nom, tLista* lista)
{

    FILE* a= fopen(nom, "rb");
    tProducto registro;


    if(!a)
    {
        puts("No se puede leer el archivo binario");
        return 0;
    }

    if(!lista)
    {
        puts("No se a proporcionado una direccion a una lista valida");
        return 0;
    }

    while(fread(&registro,sizeof(tProducto),1,a)==1)
    {
        if(!insertarEnOrden(lista, cmpProductosCodigo,&registro,sizeof(registro),acumularStockProducto))
        {
            puts("Error poniendo item en lista");
            return 0;
        }
    }

    fclose(a);
    return 1;


}


int leerBinALista(const char* nom, tLista* lista)
{


    FILE* a= fopen(nom, "rb");
    tProducto registro;


    if(!a)
    {
        puts("No se puede leer el archivo binario");
        return 0;
    }

    if(!lista)
    {
        puts("No se a proporcionado una direccion a una lista valida");
        return 0;
    }

    while(fread(&registro,sizeof(tProducto),1,a)==1)
    {
        if(!ponerEnListaUltimo(lista, &registro, sizeof(registro)))
        {
            puts("Error poniendo item en lista");
            return 0;
        }
    }

    fclose(a);
    return 1;
}



void generarLotePruebas()
{

    FILE* a = fopen("productos.bin","wb");
   tProducto productos[]= {{'w', 100, "Avenax500gr", 358.99, "Marolio"},{'x', 150, "Bebida gaseosa sabor cola", 1000, "Manaos"},{'a', 100, "Lata de tomate", 358.99, "Marolio"},
        {'a', 100, "Lata de tomate", 358.99, "Marolio"},{'e', 50, "Maple Huevo x30 unidades", 2300, "Granja pollos hermanos"},
        {'f', 100, "Botella vidrio salsa de tomate", 899.99, "Marolio"},{'q', 20, "Galletitas Surtido", 658.99, "Bagley"},
        {'f', 100, "Botella vidrio salsa de tomate", 899.99, "Marolio"},{'b', 100, "Pote dulce de leche", 503.99, "La Serenisima"},{'f', 100, "Botella vidrio salsa de tomate", 899.99, "Marolio"},
        {'c', 10, "Agua natural", 580.99, "Villavicencio"},{'f', 100, "Botella vidrio salsa de tomate", 899.99, "Marolio"},
        {'z', 404, "Pate enlatado", 290, "Swift"},{'g', 200, "Lata atun", 599.99, "Gomes"},{'j', 58, "Cerveza", 588.99, "Corona"},{'m', 20, "Paquete fideos", 300.0, "Luchetti"},
        {'f', 100, "Botella vidrio salsa de tomate", 899.99, "Marolio"},{'f', 100, "Botella vidrio salsa de tomate", 899.99, "Marolio"},{'y', 20, "Paquete fideos", 300.0, "Luchetti"}
    };



    if(!a)
    {
        puts("Error abriendo productos.bin para lotes de prueba");
        return;
    }

    fwrite(productos,sizeof(tProducto), sizeof(productos)/sizeof(productos[0]),a);

    fclose(a);



}

void mostrarProducto(const void* prod, FILE* a)
{

    tProducto* p = (tProducto*)prod;

    printf("Producto...\n");
    printf("Codigo: %c\n", p->codigo);
    printf("Stock: %d\n", p->stock);
    printf("Descripcion: %s\n", p->descripcion);
    printf("Precio unitario: %.2f\n", p->precioUnitario);
    printf("Marca: %s\n", p->marca);
    printf("----------------------------------------------------\n");


}
