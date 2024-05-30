#ifndef DOUBLE_LIST_H_INCLUDED
#define DOUBLE_LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DUPLICATED 2

typedef struct sNode{

    void* info;
    unsigned size_info;
    struct sNode *next, *prev;

}tNode;

typedef tNode* List;

void initializeList(List*);
int destroyList(List*);
int  isEmpty(const List*);
int  isFull(const List*, unsigned );
int insertLast(List*, const void*, unsigned);
int insertFirst(List*, const void*, unsigned);
int GoLeftRight(const List*, void(*action)(const void*));
int GoRightLeft(const List*, void(*action)(const void*));
int insertSorted(List*, const void* , unsigned , int(*cmp)(const void*, const void*), void (*accumulate_function)(void**, unsigned*, const void*, unsigned));
void SortList(List*, int(*cmp)(const void*, const void*));
int removeByKey(List*  , void*, int(*cmp)(const void*, const void*));
List* findByKey_sortedList(List*, void*, int(*cmp)(const void*, const void*));
List* finByKey_unsortedList(List*,void*, int(*cmp)(const void*, const void*));
int removeAllKeys(List*, void*, int (*cmp)(const void*, const void*));
void resumeOccurences(List*, int (*cmp)(const void*, const void*), void (*resum)(void**, unsigned*,const void*, unsigned));
void filterList(List*,const void*, int (*filter_function)(const void*, const void*));
void mapList(List*, const void*, void(*map_function)(void**,unsigned*, const void*));
void reduceList(const List*, void*, void(*reduce_function)(const void*,unsigned*, void*));
#endif // DOUBLE_LIST_H_INCLUDED
