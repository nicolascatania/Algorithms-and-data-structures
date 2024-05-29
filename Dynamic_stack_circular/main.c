#include "circular_stack.h"

int main()
{
    Stack s;
    int n[] = {1,2,3,4,5},i, buffer;
    initializeStack(&s);
    for(i=0;i<sizeof(n)/sizeof(n[0]);i++){
        if(!push(&s,n+i, sizeof(n[i]))){
            puts("ERROR pushing");
        }
    }

    Peek(&s, &buffer, sizeof(buffer));
    printf("PEEKED: %d\n", buffer);
    pop(&s, &buffer, sizeof(buffer));
    printf("Poped: %d\n", buffer);
    Peek(&s, &buffer, sizeof(buffer));
    printf("PEEKED: %d\n", buffer);
    destroyStack(&s);
    if(!isEmpty(&s)){
        puts("ERROR EMPTYING STACK");
    }
    return 0;
}
