#ifndef DYNAMIC_STACK_H_INCLUDED
#define DYNAMIC_STACK_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y)((x)>(y)?(y):(x))

typedef struct sNode{
    void* info;
    unsigned sizeInfo;
    struct sNode* next;
}tNode;

typedef tNode* tStack;


void createStack(tStack*);
int isFull(const tStack*, const void*, unsigned);
int isEmpty(const tStack*);
int push(tStack*, const void*, unsigned);
int pop(tStack*, void*, unsigned);
int peek(const tStack*, void*, unsigned);
void destroy(tStack*);

#endif // DYNAMIC_STACK_H_INCLUDED
