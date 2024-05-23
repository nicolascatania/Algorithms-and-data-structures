#ifndef FUNREC_H_INCLUDED
#define FUNREC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ISLETTER(c)((c>='a' && c<='z')||(c>='A' && c<='Z'))

/*Number recursive functions*/
void triangle_remainder(int n);
void triangle_remainder_i(int n, int d);
void printStairNumber(int n);
void printReversedStairNumber(int n);
void printNumberPyramid(int n);
void printNumberReverse(int n);
void printNumber(int n);
double rfactorial(unsigned n);
int fibonacci(int n);




/*String recursive functions*/
void printString(const char* c);
void reversedStringPrint(const char* c);
void doublePyramidString(char* c);
void pyramidString(char*c);
void decreasingString(char* c); //wrapper
void decreasingString_i(char* c, int len);//inner function
void raisingStairString(char* c);
void raisingStairString_i(char* c, int len);
char* reverseString(char* c);
void reverseString_i(char* start, char* end);
int palindrome(char* c);
int palindrome_i(char* start, char* end);
char* rstrcpy(char* c1, const char* c2);
void rstrcpy_i(char* c1, const char* c2);
int rStrlen(const char* c);

/*Generic recursive functions*/
void* reverseBytesGeneric(void* e, unsigned len);
void reverseBytesGeneric_i(void* start, void* end);
void* reverseGeneric(void* vec, int elements, unsigned size);
void reverseGeneric_i(void* start, void* end, unsigned size);
void changeValuesFromPointers( void* a, void* b, unsigned size);
void* bSearch(void* vec, void* key, int elements, unsigned size);
#endif // FUNREC_H_INCLUDED
