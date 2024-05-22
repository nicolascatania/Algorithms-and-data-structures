#include "productos.h"
#include "listaDoble.h"
#include "utilidades.h"


void acumularProductoMenorStock(void** a, unsigned* tama,const void* b, unsigned tamb){

    tProducto *pa = *(tProducto**)a;
    tProducto *pb = (tProducto*)b;
    printf("MOSTRANDO A %c %c %d\n", pa->tipoOp, pa->codProd, pa->cant);
    printf("MOSTRANDO PROD B: %c %c %d\n", pb->tipoOp, pb->codProd, pb->cant);

    if(pa->cant > pb->cant){
        printf("STOCK MENOR DETECTAO : ORIGINAL: %d, MENOR: %d\n", pa->cant, pb->cant);
        pa->cant = pb->cant;
    }

}

int mostrarMaestro(const char* m)
{

    FILE* a= fopen(m,"rb");
    tProducto aux;
    if(!a)
    {
        puts("Error al leer archivo maestro.");
        return 0;
    }

    while(fread(&aux,sizeof(aux),1,a)==1)
    {
        mostrarProducto(&aux);
    }

    fclose(a);
    return 1;
}

int productosALista(const char* arch, tLista* lista){

    tProducto aux;
    FILE* a = fopen(arch, "rb");
    if(!a){
        puts("Error abriendo archivo");
        return 0;
    }


    while(fread(&aux,sizeof(tProducto),1,a)==1)
    {
        if(!insertarAlFinal(lista,&aux, sizeof(aux)))
        {
            puts("Error insertando elemento indice.");
            return 0;
        }
    }

    fclose(a);
    return 1;

}

int actualizarMaestro(const char* archMaestro, const char* archMovimientos, tLista* lista)
{

    FILE* maestro = fopen(archMaestro,"r+b");
    FILE* movimientos = fopen(archMovimientos,"rt");
    tProducto aux, auxMov;
    tIndice elemIndice;
    tLista* elemEncontrado;


    if(!maestro || !movimientos)
    {
        fclose(maestro);
        fclose(movimientos);
    }

    while(fscanf(movimientos,"%c|%d|%c\n", &(auxMov.codProd), &(auxMov.cant), &(auxMov.tipoOp))==3){
        elemEncontrado = buscarPorClave_ord(lista, &(auxMov.codProd),cmpIndiceChar);

        if(elemEncontrado){
            memcpy(&elemIndice, (*elemEncontrado)->info, (*elemEncontrado)->tamInfo);
//          printf("Producto encontrado INDICE: %d, COD PROD %c.\n", elemIndice.idx, elemIndice.cod);
            fseek(maestro, sizeof(tProducto)*(elemIndice.idx),SEEK_SET);
            fread(&aux,sizeof(aux),1,maestro);
            if(auxMov.tipoOp=='V'){

                if(aux.cant - auxMov.cant <0){
                    aux.cant=0;
                }
                else{
                    aux.cant-= auxMov.cant;
                }
                fseek(maestro, (-1)*(int)sizeof(tProducto),SEEK_CUR);
                fwrite(&aux,sizeof(aux),1,maestro);
            }
            else if(auxMov.tipoOp == 'R'){
                aux.cant += auxMov.cant;
                fseek(maestro, (-1)*(int)sizeof(tProducto),SEEK_CUR);
                fwrite(&aux,sizeof(aux),1,maestro);
            }
//            else{
//                printf("OPERACION INVALIDA :%c.\n", auxMov.tipoOp);
//            }
        }
        else
        {
            if(auxMov.tipoOp == 'R'){
                fseek(maestro,0, SEEK_END);
                fwrite(&auxMov,sizeof(auxMov),1,maestro);
            }
        }

    }


    fclose(maestro);
    fclose(movimientos);
    return 1;

}

int obtenerIndices(const char* nomarch, tLista* lista)
{

    FILE* maestro = fopen(nomarch, "rb");
    tProducto aux;
    tIndice elem;
    int indice=0;
    if(!maestro)
    {
        puts("Error leyendo archivo maestro.");
        return 0;
    }


    while(fread(&aux,sizeof(tProducto),1,maestro)==1)
    {
        elem.cod = aux.codProd;
        elem.idx = indice;
        if(!insertarAlFinal(lista,&elem, sizeof(tIndice)))
        {
            puts("Error insertando elemento indice.");
            return 0;
        }

        indice++;
    }

    fclose(maestro);

    return 1;

}


int genMaestroYMovimientos()
{


    FILE* maestro = fopen("maestro.bin", "wb");
    FILE* mov = fopen("movimientos.txt","wt");
    int i;

    tProducto a[]= {{'a',1,' '},{'a',4,' '},{'a',150, ' '},{'x',100, ' '},{'e',150, ' '},{'w',150, ' '},{'b',150, ' '}
        ,{'y',150, ' '},{'q',150, ' '},{'d',150, ' '},{'s',150, ' '},{'n',150, ' '},{'m',150, ' '}
        ,{'t',150, ' '},{'r',150, ' '},{'v',150, ' '},{'c',150, ' '},{'z',150, ' '},{'b',15,' '}
        ,{'o',150, ' '},{'y',0,' '},{'p',150, ' '},{'f',150, ' '},{'a',2,' '}
    };

    tProducto b[]= {{'a',50,'V'},{'k',500,'R'},{'e',150,'V'},{'a',500,'R'},{'p',500,'R'}
        ,{'g',150,'V'},{'q',150,'V'},{'d',150, 'F'},{'s',150, 'e'},{'n',150, ' '},{'m',0,'R'}
        ,{'t',150,'R'},{'t',150,'R'},{'v',200, 'R'},{'c',150, 'R'},{'t',150, 'R'},{'o',150,'R'},
        {'p',150,'R'},{'f',1500,'V'}
    };


    if(!maestro || !mov)
    {
        fclose(maestro);
        fclose(mov);
        puts("Error generando archivos");
        return 0;
    }

    fwrite(a,sizeof(tProducto),sizeof(a)/sizeof(tProducto), maestro);
    fclose(maestro);

    for(i=0; i<sizeof(b)/sizeof(b[0]); i++)
    {
        fprintf(mov,"%c|%d|%c\n", b[i].codProd, b[i].cant, b[i].tipoOp);
    }
    fclose(mov);

    return 1;
}


void mostrarProdIndice(const void* a)
{
    tIndice* i = (tIndice*)a;
    puts("CODIGO\tINDICE");
    printf("%c\t%d\n", i->cod, i->idx);

}

void mostrarProducto(const void* a)
{
    tProducto* prod = (tProducto*)a;
    puts("CODIGO\tCANTIDAD\tTIPO OPERACION");
    printf("%c\t%d\t%c\n", prod->codProd, prod->cant, prod->tipoOp);
    puts("----------------------------------------------------------");

}
