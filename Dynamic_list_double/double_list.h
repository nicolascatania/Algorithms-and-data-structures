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

/*===================================Creation===================================*/
void initializeList(List*);

/*===================================Status===================================*/
int  isEmpty(const List*);
int  isFull(const List*, unsigned );

/*===================================Insertion===================================*/
int insertLast(List*, const void*, unsigned);
int insertFirst(List*, const void*, unsigned);
int insertSorted(List*, const void* , unsigned , int(*cmp)(const void*, const void*), void (*accumulate_function)(void**, unsigned*, const void*, unsigned));
int insertInPosition(List*, const void*, unsigned, int);
/*===================================Traverse===================================*/
//those count the number of nodes as well
int GoLeftRight(const List*, void(*action)(const void*));
int GoRightLeft(const List*, void(*action)(const void*));

/*===================================Sorting===================================*/
void SortList(List*, int(*cmp)(const void*, const void*));


/*===================================Search===================================*/
List* findByKey_sortedList(List*, void*, int(*cmp)(const void*, const void*));
List* finByKey_unsortedList(List*,void*, int(*cmp)(const void*, const void*));

/*===================================Deletion===================================*/
int removeByKey(List*  , void*, int(*cmp)(const void*, const void*));
int removeAllKeys(List*, void*, int (*cmp)(const void*, const void*));
/*===================================Misc===================================*/
void resumeOccurences(List*, int (*cmp)(const void*, const void*), void (*resum)(void**, unsigned*,const void*, unsigned));

/*===================================Map filter & reduce===================================*/
void filterList(List*,const void*, int (*filter_function)(const void*, const void*));
void mapList(List*, const void*, void(*map_function)(void**,unsigned*, const void*));
void reduceList(const List*, void*, void(*reduce_function)(const void*,unsigned*, void*));

/*===================================Destruction===================================*/
int destroyList(List*);
#endif // DOUBLE_LIST_H_INCLUDED
