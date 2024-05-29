#include "queue.h"

int main()
{
    Queue q;
    int n[] = {1,2,3,4,5},i, buffer;
    initializeQueue(&q);
    for(i=0;i<sizeof(n)/sizeof(n[0]);i++){
        if(!Enqueue(&q,n+i, sizeof(n[i]))){
            puts("ERROR ENQUEUING");
        }
    }

    Peek(&q, &buffer, sizeof(buffer));
    printf("PEEKED: %d\n", buffer);
    Dequeue(&q, &buffer, sizeof(buffer));
    printf("DEQUEUED: %d\n", buffer);
    Peek(&q, &buffer, sizeof(buffer));
    printf("PEEKED: %d\n", buffer);
    destroyQueue(&q);
    if(!isEmpty(&q)){
        puts("ERROR EMPTYING QUEUE");
    }


    return 0;
}
