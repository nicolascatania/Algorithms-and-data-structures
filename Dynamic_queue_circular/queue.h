#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y)((x)>(y)?(y):(x))

typedef struct sNode{

    void* info;
    unsigned size_info;
    struct sNode* next;
}tNode;

typedef tNode* Queue;

void initializeQueue(Queue*);
int isFull(const Queue*, void*, unsigned);
int isEmpty(const Queue*);
int Enqueue(Queue*, void*, unsigned);
int Dequeue(Queue*, void*, unsigned);
int Peek(const Queue*, void*, unsigned);
void destroyQueue(Queue*);

#endif // QUEUE_H_INCLUDED
