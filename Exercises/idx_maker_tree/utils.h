#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_MEM -1
#define OK 1
#define DUPLICATE 2
#define EMPTY_TREE -2
#define FILE_ERROR -10

#define MIN(x,y)((x)>(y)?(y):(x))

//this one is to read data from a binary file
int read_from_bin(void** data, unsigned data_size, void* pf, int position);
void printInt(void** data, unsigned* data_size, const void* stream, const void* param);
int cmpInt(const void* a, const void* b);
void print_int_to_bin_file(void** data, unsigned* data_size, const void* stream,const void* param);
void multiply_int_by_n(void** data, unsigned* data_size, const void* n);
int filter_int_greater(const void* data, const void* param);
#endif // UTILS_H_INCLUDED
