#include "funRec.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main()
{
    char key = '1';
    int vec[] = {1,2,3,4,5,6};
    int* numR;
    char cad[] = {"123456"}, cad2[]= {"arriba"};
    char* cadR;
    unsigned n = 5;

    cadR = rstrcpy(cad2,cad);
    if(!cadR)
    {
        puts("Error");
    }
    else
    {
        printf("%s",cadR);
    }

    printf("\n%d\n", rStrlen(cad));

    cadR = (char*)bSearch(cad,&key,6,sizeof(char));
    if(!cadR)
    {
        puts("NOT FOUND");
    }
    else
    {
        printf("%c", *cadR);
    }

    return 0;
}
