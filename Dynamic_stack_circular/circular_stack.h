#ifndef CIRCULAR_STACK_H_INCLUDED
#define CIRCULAR_STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(x,y)((x)>(y)?(y):(x))

typedef struct sNode{

    void* info;
    unsigned size_info;
    struct sNode* next;
}tNode;

typedef tNode* Stack;

void initializeStack(Stack*);
int isFull(const Stack*, void*, unsigned);
int isEmpty(const Stack*);
int push(Stack*, void*, unsigned);
int pop(Stack*, void*, unsigned);
int Peek(const Stack*, void*, unsigned);
void destroyStack(Stack*);


#endif // CIRCULAR_STACK_H_INCLUDED
