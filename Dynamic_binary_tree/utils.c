#include "utils.h"


int read_from_bin(void** data, unsigned data_size, void* pf, int position){
    if(!pf)
    {
        return FILE_ERROR;
    }
    *data = malloc(data_size);
    if(!*data)
    {
        return ERROR_MEM;
    }
    fseek((FILE*)pf, position*data_size, SEEK_SET);
    return fread(*data, data_size, 1, pf);


}

int cmpInt(const void* a, const void* b)
{
    int* aa = (int*)a;
    int* bb = (int*)b;

    return (*aa - *bb);
}

void printInt(void** data, unsigned* data_size, const void* stream, const void* param)
{
    int* a = *(int**)data;
    fprintf((FILE*)stream, "%d\n", *a);
}

void print_int_to_bin_file(void** data, unsigned* data_size, const void* stream, const void* param)
{
    int* a = *(int**)data;
    fwrite(a, sizeof(*a),1,(FILE*)stream);
}


void multiply_int_by_n(void** data, unsigned* data_size, const void* n)
{
    int* a = *(int**)data;
    *a *= *(int*)n;
}

int filter_int_greater(const void* data, const void* param)
{
    if((*(int*)data)>(*(int*)param))
    {
        return 1;
    }
    return 0;
}
