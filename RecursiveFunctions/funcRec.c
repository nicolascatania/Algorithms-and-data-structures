#include "funRec.h"

void triangle_remainder(int n)
{
    triangle_remainder_i(n, 10);
}
void triangle_remainder_i(int n, int d)
{
    if(!(n/d))
    {
        printf("%d\n",n%d);
        return;
    }
    printf("%d\n",n%d);
    triangle_remainder_i(n, d*10);
}

void printStairNumber(int n)
{
    if(!(n/10))
    {
        printf("%d\n",n);
        return;
    }
    printf("%d\n",n);
    printStairNumber(n/10);
}

void printReversedStairNumber(int n)
{
    if(!(n/10))
    {
        printf("%d\n",n);
        return;
    }
    printReversedStairNumber(n/10);
    printf("%d\n",n);
}

void printNumberPyramid(int n)
{

    if(!(n/10))
    {
        printf("%d\n",n);
        return;
    }
    printf("%d\n",n);
    printNumberPyramid(n/10);
    printf("%d\n",n);
}

void printNumberReverse(int n)
{
    int r;
    if(!(n/10))
    {
        printf("%d\n",n);
        return;
    }
    r= n%10;
    printf("%d\n", r);
    printNumberReverse(n/10);
}


void printNumber(int n)
{
    int r;
    if(!(n/10))
    {
        printf("%d\n", n);
        return;
    }

    printNumber(n/10);
    r= n%10;
    printf("%d\n", r);
}
double rfactorial(unsigned n)
{
    return (!n) ? 1 : rfactorial(n-1)*n;
}

int fibonacci(int n)
{
    return n<=1 ? 1: (fibonacci(n-1) + fibonacci(n-2));
}
/*------------------------------STRINGS------------------------------------*/
void printString(const char* c)
{
    if(!*c)
    {
        return;
    }
    printf("%c", *c);

    printString(c+1);

}

void reversedStringPrint(const char* c)
{
    if(!*c)
    {
        return;
    }
    reversedStringPrint(c+1);
    printf("%c", *c);


}

void doublePyramidString(char* c)
{

    if(!*c)
    {
        return;
    }

    printf("%c",*c);
    doublePyramidString(c+1);
    printf("%c",*c);

}

void pyramidString(char*c)
{
    if(!*c)
    {
        return;
    }

    printf("%s\n", c);
    pyramidString(c+1);
    printf("%s\n",c);
}

void decreasingString(char* c)
{
    decreasingString_i(c,strlen(c));
}

void decreasingString_i(char* c, int len)
{
    if(len<1)
    {
        return;
    }

    printf("%.*s", len,c);
    puts("");
    decreasingString_i(c, len - 1);
}

void raisingStairString(char* c)
{

    raisingStairString_i(c,strlen(c));
}


void raisingStairString_i(char* c, int len)
{
    if(len<1)
    {
        return;
    }

    raisingStairString_i(c, len - 1);
    printf("%.*s", len,c);
    puts("");
}


char* reverseString(char* c)
{
    int len = strlen(c);
    reverseString_i(c, c+len-1);
    return c;
}

void reverseString_i(char* start, char* end)
{
    char aux;
    if(start>=end)
    {
        return;
    }
    aux = *end;
    *end = *start;
    *start = aux;
    return reverseString_i(start+1, end-1);
}

int palindrome(char* c)
{
    return palindrome_i(c, c + strlen(c) - 1);
}

int palindrome_i(char* start, char* end)
{



    if(start>=end)
    {
        return 1;
    }

    if(!ISLETTER(*start) && !ISLETTER(*end))
    {
        return palindrome_i(start +1, end-1);
    }

    if(!ISLETTER(*start))
    {
        return palindrome_i(start+1,end);
    }
    if(!ISLETTER(*end))
    {
        return palindrome_i(start, end-1);
    }

    if(ISLETTER(*start) && ISLETTER(*end) && toupper(*start) != toupper(*end))
    {
        return 0;
    }

    return palindrome_i(start+1, end-1);
}

char* rstrcpy(char* c1, const char* c2)
{
    if(strlen(c1)<strlen(c2))
    {
        //if strings do not acomplish this requierment function ends
        return NULL;
    }
    rstrcpy_i(c1,c2);
    return c1;
}

void rstrcpy_i(char* c1, const char* c2)
{
    if(!*c2)
    {
        *c1 = '\0';
        return;
    }
    *c1= *c2;
    rstrcpy_i(c1+1,c2+1);
}

int rStrlen(const char* c)
{
    if(!*c)
    {
        return 0;
    }

    return (rStrlen(c+1)+1);

}

/*---------------------GENERIC-------------------------------------------*/

void* reverseBytesGeneric(void* e, unsigned len)
{
    reverseBytesGeneric_i(e, e+len-1);
    return e;
}

void reverseBytesGeneric_i(void* start, void* end)
{
    char* a = (char*)start;
    char* b = (char*)end;
    char aux;
    if(start>=end)
    {
        return;
    }
    aux = *a;
    *a = *b;
    *b= aux;

    return reverseBytesGeneric_i((char*)start + sizeof(char), (char*)end - sizeof(char));
}


void* reverseGeneric(void* vec, int elements, unsigned size)
{
    reverseGeneric_i(vec, (char*)vec + (elements - 1) * size, size);
    return vec;
}

void reverseGeneric_i(void* start, void* end, unsigned size)
{
    if (start >= end)
    {
        return;
    }

    changeValuesFromPointers(start, end, size);
    reverseGeneric_i((char*)start + size, (char*)end - size, size);
}

void changeValuesFromPointers(void* a, void* b, unsigned size)
{
    char aux;
    unsigned i;
    for (i = 0; i < size; i++)
    {
        aux = *(char*)a;
        *(char*)a = *(char*)b;
        *(char*)b = aux;
        a+= sizeof(char);
        b+=sizeof(char);
    }
}


void* bSearch(void* vec, void* key, int elements, unsigned size)
{

    int mid = elements / 2, cmp;
    void* pos = vec + (mid * size);
    if (elements <= 0)
    {
        return NULL;
    }

    cmp = memcmp(pos, key, size);

    if (cmp == 0)
    {
        return pos;
    }
    else if (cmp > 0)
    {
        return bSearch(vec, key, mid, size);
    }
    else
    {
        return bSearch(pos + size, key, elements - mid - 1, size);
    }
}

