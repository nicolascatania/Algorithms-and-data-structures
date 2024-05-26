#ifndef DYNAMIC_LIST_H_INCLUDED
#define DYNAMIC_LIST_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(x,y)((x)>(y)?(y):(x))
#define DUPLICATED_ITEM 2

typedef struct sNode{
    void* info;
    unsigned size_info;
    struct sNode* next;
}Node;

typedef Node* List;


void initializeList(List*);
int isEmpty(const List*);
int isFull(const List*, const void*, unsigned);
int pushLast(List*,const void*, unsigned);
int pushFirst(List*, const void*, unsigned);
int popLast(List*, void*, unsigned);
int popFirst(List*, void*, unsigned);
int peekFirst(const List*, void*, unsigned);
int peekLast(const List*, void*, unsigned);
void destroyList(List*);
void showList(const List*, void(*show)(const void*));
void showListRecursive(const List*, void(*show)(const void*));
void showListRecursive_Backwards(const List*, void(*show)(const void*));
int countItems(const List* pl);

List* searchNode(const List*, const void*, int(*cmp)(const void*, const void*));
int insertSorted(List*, const void*, unsigned, int(*cmp)(const void*, const void*), void(*accumulate_item)(void**, unsigned*, const void*, unsigned));
Node* findMin(List*, int(*cmp)(const void*, const void*));
int sortList(List*, int(*cmp)(const void*, const void*));

int remove_First_Occurrence(List*, const void*, int (*cmp)(const void*, const void*));
int remove_All_Ocurrences(List*, const void*, int (*cmp)(const void*, const void*));
int remove_Last_N_Ocurrences(List*, int);
void remove_at_position(List*, int);
int insert_at_position(List*, const void*, unsigned, int);

void mapC(List*, void (*mapFunction)(void*));
void filterC(List*, void*, int(*filterFunction)(const void*, const void*));
void reduce(List*, void*, void(*reduceFunction)(const void*, void*));
#endif // DYNAMIC_LIST_H_INCLUDED
