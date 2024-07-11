#ifndef LIST_H_INCLUDED
#define LIST_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define ERROR_MEM -1
#define OK 1
#define DUPLICATE 2
#define EMPTY_LIST -2

typedef struct sNode {
    void* info;
    unsigned infoSize;
    struct sNode* next;
} dsNode;

typedef dsNode* dsList;

typedef int(*Cmp)(const void*, const void*);
typedef void(*Acc)(void**, unsigned*, const void*, unsigned);
typedef int(*InsertionType)(dsList*, const void*, unsigned);
//Action used like show a integer (integer**, size*, stream*)
typedef void(*Action)(void**, unsigned*, const void*);


/*=============================================Creation=============================================*/

void createList(dsList* p);

/*=============================================List status=============================================*/
int isEmptyList(const dsList* p);
int isFullList(const dsList* p, const void* data, unsigned tam);

/*=============================================Insertion=============================================*/
int insertAtBegining(dsList* p, const void* data, unsigned data_size);
int insertAtEnd(dsList*p, const void* data, unsigned data_size);
int insertAtPosition(dsList* p, const void* data, unsigned data_size, int pos);
int insertSorted(dsList* p, const void* data, unsigned data_size, Cmp cmp, Acc acc);

/*=============================================Load List With Data Source=============================================*/
//accepts only insertAtBegining and insertAtEnd
int loadListFromSourceData(dsList* p, const void* input, unsigned input_size, int input_number_elements, InsertionType ins_type);


/*=============================================Sorting=============================================*/
void sortList(dsList* p, Cmp cmp);

/*=============================================Traverse=============================================*/
void traverseList(dsList* p, Action action, void* stream);

/*=============================================Search=============================================*/
dsList* search_minorKey_unordered_subList(dsList* _start, dsList* _end, Cmp cmp);

//Returns first occurence of the matching key, searches all over the whole list.
dsList* search_key(const dsList* p, const void* key, Cmp cmp);

//optimized for ordered lists.
dsList* search_mayorKey_ordered_list(const dsList* p, Cmp cmp);
dsList* search_minorKey_ordered_list(const dsList* p, Cmp cmp);

//searches elements by nokey fields, the list does not have to be ordered.
//traverse the whole list.
//you can search for a key field too, being useful in some cases.
dsList* search_mayor_noKey(const dsList* p, Cmp cmp);
dsList* search_minor_noKey(const dsList* p, Cmp cmp);

//returns a new list with all the matches
dsList search_Mayors_noKey(const dsList* p, Cmp cmp);
dsList search_Minor_noKey(const dsList* p, Cmp cmp);

/*=============================================Count items=============================================*/
int listLen(const dsList* p);

/*=============================================Randomize functions=============================================*/
void randomizePointerToList(dsList* p, int number_elements);

void shuffle_list(dsList* p, int number_elements);

//needs cmp to make sure there it is not inserting duplicated items.
dsList generate_random_list_with_n_elements(const dsList* source, int n, int source_number_elements, Cmp cmp);

void leave_list_with_random_n_elements(dsList* p, int n, int number_elements);


/*=============================================Map Filter & Reduce (Python like functionality)=============================================*/
dsList map_py(dsList* p, void* param, void(*mapping)(void*, const void*));
dsList filter_py(dsList* p, void* filtr, int(*filter_func)(const void*, const void*));
void reduce_py(dsList* p, void* result, void(*reduce_func)(void*, const void*));


/*=============================================Deletion=============================================*/
int deleteFirst(dsList* p, void* buffer, unsigned buffer_size);

int deleteLast(dsList* p, void* buffer, unsigned buffer_size);

int deleteInPosition(dsList *p, void* buffer, unsigned buffer_size, int position);

/*=============================================Destruction=============================================*/
void destroyList(dsList* p);

#endif // LIST_H_INCLUDED
