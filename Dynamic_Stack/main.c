#include "dynamic_stack.h"

int main()
{
    tStack stack;
    int n[]={1,2,3,4,5,6,7,8,9},i, buffer;
    createStack(&stack);

    if(!isEmpty(&stack)){
        puts("Error");
    }
    if(isFull(&stack, &n[0], sizeof(n[0]))){
        puts("Error");
    }
    for(i=0;i<sizeof(n)/sizeof(n[0]);i++){
        if(!push(&stack,n+i, sizeof(n[i]))){
            printf("ERROR pushing %d element.\n", i);
        }
    }
    if(!peek(&stack,&buffer,sizeof(buffer))){
        puts("ERROR PEEKING");
    }
    else{
        printf("PEEKED: %d\n", buffer);
    }

    if(!pop(&stack, &buffer, sizeof(buffer))){
        puts("ERROR POPING");
    }
    else{
        printf("POPED: %d\n", buffer);
    }

    if(!peek(&stack,&buffer,sizeof(buffer))){
        puts("ERROR PEEKING");
    }
    else{
        printf("PEEKED: %d\n", buffer);
    }
    destroy(&stack);
    if(!isEmpty(&stack)){
        puts("ERROR EMPTYING STACK AFTER DESTROYING IT");
    }

    return 0;
}
