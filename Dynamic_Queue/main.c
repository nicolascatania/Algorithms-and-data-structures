#include "dynamic_queue.h"
int main()
{
    tQueue q;
    int n[]={1,2,3,4,5},i,buffer;

    initializeQueue(&q);

    if(!isEmpty(&q))
    {
        puts("ERROR, Q MUST BE EMPTY");
    }

    if(isFull(&q, &buffer, sizeof(buffer))){
        puts("ERROR, Q CANNOT BE FULL");
    }

    for(i=0;i<sizeof(n)/sizeof(n[0]);i++){
        if(!Enqueue(&q, n+i, sizeof(n[0]))){
            printf("ERROR ENQUEUEING %d element\n", i);
        }
    }

    if(!peek(&q,&buffer, sizeof(buffer))){
        puts("ERROR PEEKING");
    }
    else{
        printf("PEEKED: %d\n", buffer);
    }

    if(!Dequeue(&q, &buffer, sizeof(buffer))){
        puts("ERROR DEQUEUEING");
    }
    else{
        printf("DEQUEUED: %d\n", buffer);
    }
    if(!peek(&q,&buffer, sizeof(buffer))){
        puts("ERROR PEEKING");
    }
    else{
        printf("PEEKED AFTER DEQUEUE: %d\n", buffer);
    }
    DestroyQueue(&q);
    if(!isEmpty(&q))
    {
        puts("ERROR, Q MUST BE EMPTY AFTER DESTROYING IT");
    }




    return 0;
}
