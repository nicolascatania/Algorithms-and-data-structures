#ifndef DYNAMIC_QUEUE_H_INCLUDED
#define DYNAMIC_QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y)((x)>(y)?(y):(x))

typedef struct sNode{
    void* info;
    unsigned sizeInfo;
    struct sNode* next;
}tNode;

typedef struct{
    tNode *head, *rear;
}tQueue;

void initializeQueue(tQueue*);
int isEmpty(const tQueue*);
int isFull(const tQueue*, const void*, unsigned);
int Enqueue(tQueue*, const void*, unsigned);
int Dequeue(tQueue*, void*, unsigned);
int peek(const tQueue*, void*, unsigned);
void DestroyQueue(tQueue*);


#endif // DYNAMIC_QUEUE_H_INCLUDED
