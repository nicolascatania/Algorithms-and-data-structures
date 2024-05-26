#include "dynamic_list.h"

void doubleNumber(void*);
int filterLargerInteger(const void*, const void*);
void addInteger(const void*, void*);
void accumulate_integer(void**, unsigned*, const void*, unsigned);
void showInteger(const void*);
int cmpInteger(const void*, const void*);
void testNodeSeach();
void testBasicFunctions();
void testInsertSorted();
void testSort();
void testRemoveFunctions();
void testMapFilterReduce();

int main()
{
    testRemoveFunctions();
    return 0;
}
void doubleNumber(void* a)
{
    int* n = (int*)a;
    (*n)*=2;
}
int filterLargerInteger(const void* info, const void* filterParam){
    if(*(const int*)info>*(const int*)filterParam){
        return 1;
    }
    else{
        return 0;
    }
}
void addInteger(const void* info, void* result ){
    const int* i = (const int*)info;
    int* r = (int*)result;
    (*r)+= (*i);
}

void accumulate_integer(void** info, unsigned* size_info, const void* element, unsigned size_element)
{
    int* a = *(int**)info;
    int* b = (int*)element;
    (*a) += (*b);
}
int cmpInteger(const void* a, const void* b)
{
    return (*(int*)a - *(int*)b);
}

void showInteger(const void* n)
{
    printf("%d ", *(const int*)n);
}
void testInsertSorted()
{
    List l;
    int n[]= {1,0,23,6,434,12,55,343,21,67,3,1,0,8,22},i, insertion;
    for(i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        insertion=insertSorted(&l,n+i,sizeof(n[i]), cmpInteger,accumulate_integer);
        if(insertion==0)
        {
            printf("Error pushing %dº element.\n", i);
        }
        else if(insertion==DUPLICATED_ITEM){
            printf("DUPLICATED %d\n", n[i]);
        }
        else{
            puts("INSERTED");
        }
    }
    showList(&l, showInteger);
    destroyList(&l);
}
void testNodeSeach()
{

    Node** founded=NULL;
    List l;
    int search, i, key = 1;
    int n[]= {1,2,3,4,5};
    initializeList(&l);
    for(i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        if(!pushLast(&l,n+i,sizeof(n[i])))
        {
            printf("Error pushing %dº element.\n", i);
        }
    }
    showList(&l,showInteger);
    puts("");
    for(search=0; search<4; search++)
    {
        founded = searchNode(&l, &key, cmpInteger);
        printf("Search: %d. Founded:", key);
        if(founded)
        {
            showInteger((*founded)->info);
            puts("");

        }
        else
        {
            puts("Not founded");
        }
        key+=2;
    }
    puts("Success");
}
void testBasicFunctions()
{
    List l, l2;
    int n[]= {1,2,3,4,5};
    int buffer,i;
    initializeList(&l);
    initializeList(&l2);

    for(i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        if(!pushLast(&l,n+i,sizeof(n[i])))
        {
            printf("Error pushing %dº element.\n", i);
        }
    }

    puts("SHOWING LIST.");
    showList(&l, showInteger);
    puts("");

    puts("SHOWING LIST BACKWARDS");
    showListRecursive_Backwards(&l, showInteger);
    puts("");


    if(!peekLast(&l,&buffer,sizeof(buffer)) || buffer!=n[i-1])
    {
        puts("Error peeking last element\n");
        printf("%d obtained, %d expected\n",buffer, n[i-1]);
    }

    if(!peekFirst(&l, &buffer, sizeof(buffer))|| buffer!=n[0])
    {
        puts("Error peeking first element\n");
        printf("%d obtained, %d expected\n",buffer, n[0]);
    }

    if(countItems(&l)!=sizeof(n)/sizeof(n[0]))
    {
        puts("Error counting list items");
    }

    if(popFirst(&l,&buffer, sizeof(buffer)))
    {
        if(buffer != n[0])
        {
            printf("Error popping first element\n");
        }
    }

    if(popLast(&l,&buffer, sizeof(buffer)))
    {
        if(buffer != n[i-1])
        {
            printf("Error popping first element\n");
        }
    }
    puts("SHOWING LIST AFTER POPPING FIRST AND LAST ELEMENT.");
    showList(&l, showInteger);
    puts("");

    puts("SHOWING LIST WITH RECURSIVE FUNCTION");
    showListRecursive(&l, showInteger);
    puts("");


    insert_at_position(&l,&n[0], sizeof(n[0]), 0);
    puts("SHOWING LIST INSERTING AT FIRST POSITION");
    showList(&l, showInteger);
    puts("");

    insert_at_position(&l,&n[0], sizeof(n[0]), 2);
    puts("SHOWING LIST INSERTING AT THIRD POSITION");
    showList(&l, showInteger);
    puts("");

    insert_at_position(&l,&n[0], sizeof(n[0]), 78);
    puts("SHOWING LIST INSERTING AT LAST POSITION");
    showList(&l, showInteger);
    puts("");

    insert_at_position(&l2,&n[0], sizeof(n[0]), 78);
    puts("SHOWING LIST INSERTING IN N POSITION ON A EMPTY LIST");
    showList(&l2, showInteger);
    puts("");

    destroyList(&l);
    destroyList(&l2);
    if(!isEmpty(&l))
    {
        puts("List was not fully destroyed.");
    }
    else
    {
        puts("\nSuccess");
    }

}
void testSort()
{
    List l;
    int n[]= {1,0,23,6,434,12,55,343,21,67,3,1,0,8,22},i;
    initializeList(&l);

    for(i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        if(!pushFirst(&l,n+i,sizeof(n[i])))
        {
            printf("Error pushing %dº element.\n", i);
        }
    }
    sortList(&l,cmpInteger);
    showList(&l, showInteger);
    destroyList(&l);
    puts("\nSuccess");
}

void testRemoveFunctions()
{

    List l;
    int n[]= {1,0,23,6,434,12,55,343,21,67,3,1,0,8,22,1,78},i;
    int key = 6, removed;

    initializeList(&l);
    for(i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        if(!pushLast(&l,n+i,sizeof(n[i])))
        {
            printf("Error pushing %dº element.\n", i);
        }
    }


    if(!remove_First_Occurrence(&l, &key, cmpInteger))
    {
        puts("ERROR REMOVING FIRST KEY");
        return;
    }
    showList(&l, showInteger);
    puts("");
    key= 78;
    if(!remove_First_Occurrence(&l, &key, cmpInteger))
    {
        puts("ERROR REMOVING SECOND KEY");
        return;
    }
    showList(&l, showInteger);
    puts("");
    key = 1;
    removed = remove_All_Ocurrences(&l, &key, cmpInteger);
    if(!removed)
    {
        puts("ERROR REMOVING VARIOUS KEYS");
        return;
    }
    showList(&l, showInteger);
    printf("\nREMOVED %d nodes.\n", removed);

    puts("\nREMOVING ELEMENT AT LAST POSITION");
    remove_at_position(&l,500);
    showList(&l, showInteger);

    puts("\nREMOVING ELEMENT AT 0 POSITION");
    remove_at_position(&l,0);
    showList(&l, showInteger);

    puts("\nREMOVING ELEMENT AT 7 POSITION");
    remove_at_position(&l,7);
    showList(&l, showInteger);
    puts("");

    puts("LIST AFTER REMOVE 3 LAST ELEMENTS");
    remove_Last_N_Ocurrences(&l, 3);
    showList(&l, showInteger);
    puts("");

    puts("LIST AFTER REMOVE 0 LAST ELEMENTS");
    remove_Last_N_Ocurrences(&l, 0);
    showList(&l, showInteger);

    puts("");
    puts("LIST AFTER REMOVE 333 LAST ELEMENTS");
    remove_Last_N_Ocurrences(&l, 333);
    showList(&l, showInteger);


    destroyList(&l);
}


void testMapFilterReduce(){
    List l;
    int n[]= {1,2,3,4,5},i;
    int filterP = 4, result=0;

    initializeList(&l);
    for(i=0; i<sizeof(n)/sizeof(n[0]); i++)
    {
        if(!pushLast(&l,n+i,sizeof(n[i])))
        {
            printf("Error pushing %dº element.\n", i);
        }
    }

    mapC(&l, doubleNumber);
    showList(&l, showInteger);
    puts("");
    filterC(&l, &filterP, filterLargerInteger);
    showList(&l, showInteger);
    puts("");
    reduce(&l, &result, addInteger);
    printf("REDUCED TO: %d\n", result);

    destroyList(&l);

 }
