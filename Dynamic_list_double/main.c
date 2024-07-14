#include "double_list.h"

void showInt(const void* a){
    printf("%d ", *(int*)a);
}
int cmpInt(const void*a, const void* b){
    return (*(int*)a - *(int*)b);
}

int filterIntGreaterThan(const void* a, const void * b){
    if(*(int*)a > *(int*)b){
        return 1;
    }
    return 0;
}

int main()
{
    //BASIC TEST
    List l,l2, l3,l4,l5, l_pos;
    int i, count,filter_param = 99,key = 5, n[]={1,2,3,4,5},
    x[]={23,5545,23,5443,213,43,32,67,223,412,11,33,96},
    z[]={1,2,1,1,1,1,3,3,3,3,5,5,2,3,5,8,9,0,3,1,1,1,2};
    initializeList(&l);
    initializeList(&l2);
    initializeList(&l3);
    initializeList(&l4);
    initializeList(&l5);


    puts("Inserting at position");
    initializeList(&l_pos);
    insertInPosition(&l_pos, &n[0], sizeof(n[0]), 10);
    puts("\nInserting in first position");
    GoLeftRight(&l_pos, showInt);
    puts("\nInserting in last position");
    insertInPosition(&l_pos, &n[1], sizeof(n[1]), 10);
    GoLeftRight(&l_pos, showInt);
    puts("\nInserting in middle position");
    insertInPosition(&l_pos, &n[2], sizeof(n[2]), 1);
    GoLeftRight(&l_pos, showInt);
    destroyList(&l_pos);
    puts("\n");




    for(i=0;i<sizeof(n)/sizeof(n[0]);i++){
        insertLast(&l, n+i, sizeof(n[i]));
        insertFirst(&l2, n+i, sizeof(n[i]));
    }
    for(i=0;i<sizeof(x)/sizeof(x[0]);i++){
        if(!insertSorted(&l3, x+i,sizeof(x[i]), cmpInt,NULL)){
            printf("ERROR INSERTING SORTED ELEMENT %d\n", i);
        }
        insertLast(&l4, x+i, sizeof(x[i]));
    }
    for(i=0;i<sizeof(z)/sizeof(z[0]);i++){
        insertLast(&l5,z+i,sizeof(z[i]));
    }

    GoLeftRight(&l, showInt);
    puts("");
    GoLeftRight(&l2,showInt);
    puts("");
    GoLeftRight(&l3,showInt);
    puts("");
    SortList(&l4,cmpInt);
    GoLeftRight(&l4,showInt);
    puts("");

    if(isEmpty(&l) || isEmpty(&l2) || isEmpty(&l3) || isEmpty(&l4) || isEmpty(&l5)){
        puts("ERROR");
    }

    printf("Removing key %d form first list.\n", key);
    removeByKey(&l, &key, cmpInt);
    GoLeftRight(&l, showInt);
    puts("");

    printf("Filtering list 4, keeping only the numbers greater than %d\n",filter_param);
    filterList(&l4,&filter_param, filterIntGreaterThan);
    GoLeftRight(&l4, showInt);
    puts("");

    puts("LIST 5");
    count = GoLeftRight(&(l5),showInt);
    printf("\n%d\n", count);
    printf("\nResuming ocurrences from list 5\n");
    resumeOccurences(&l5,cmpInt,NULL); //it'll remove repeated nodes, and the inner function
                                       //can change the original value node for the repeated one
                                      //if it is something like a more complex data structure
                                      //like a product(name, description, price), well, you cant
                                      //remove repeated products and keep the highest price on the lefmost node.
    puts("LIST RESUMED");
    GoLeftRight(&l5,showInt);
    destroyList(&l);
    destroyList(&l2);
    destroyList(&l3);
    destroyList(&l4);
    destroyList(&l5);


    return 0;
}

