#include "double_list.h"

/*===================================Creation===================================*/
void initializeList(List* l)
{
    *l = NULL;
}

/*===================================Status===================================*/
int  isEmpty(const List* l)
{
    return *l == NULL;
}
int  isFull(const List* l, unsigned size_element)
{
    return 0;
}

/*===================================Insertion===================================*/
int insertLast(List* l, const void* element, unsigned size_element)
{
    tNode *new_node, *current=*l;
    if(current)
    {
        while(current->next)
        {
            current = current->next;
        }
    }
    if(!(new_node = (tNode*)malloc(sizeof(tNode)))||!(new_node->info = malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info, element, size_element);
    new_node->size_info = size_element;
    new_node->next= NULL;
    new_node->prev = current;
    if(current)
    {
        current->next = new_node;
    }
    *l = new_node;
    return 1;
}
int insertFirst(List* l, const void* element, unsigned size_element)
{
    tNode *new_node, *current=*l;
    if(current)
    {
        while(current->prev)
        {
            current = current->prev;
        }
    }
    if(!(new_node = (tNode*)malloc(sizeof(tNode)))||!(new_node->info = malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info, element, size_element);
    new_node->size_info = size_element;
    new_node->next= current;
    new_node->prev = NULL;
    if(current)
    {
        current->prev = new_node;
    }
    *l = new_node;
    return 1;
}

int insertSorted(List* l, const void* element, unsigned size_element, int(*cmp)(const void*, const void*), void (*accumulate_function)(void**, unsigned*, const void*, unsigned))
{
    tNode* new_node, *current = *l, *aux_next, *aux_prev;
    int comparison;
    if(!current)
    {
        aux_next=NULL;
        aux_prev=NULL;
    }
    else
    {
        while(current->next!=NULL && cmp(current->info,element)<0)
        {
            current = current->next;
        }
        while(current->prev!=NULL && cmp(current->info,element)>0)
        {
            current = current->prev;
        }
        comparison = cmp(current->info, element);

        if(comparison==0)
        {
            *l =current;
            if(accumulate_function)
            {
                accumulate_function(&current->info, &current->size_info, element,size_element);
            }
            return DUPLICATED;
        }

        if(comparison<0)
        {
            aux_prev= current;
            aux_next = current->next;
        }
        else
        {
            aux_prev = current->prev;
            aux_next = current;
        }
    }
    if(!(new_node = (tNode*)malloc(sizeof(tNode)))||!(new_node->info = malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info,element,size_element);
    new_node->size_info= size_element;
    new_node->next= aux_next;
    new_node->prev = aux_prev;
    if(aux_next)
    {
        aux_next->prev = new_node;
    }
    if(aux_prev)
    {
        aux_prev->next = new_node;
    }
    *l = new_node;
    return 1;
}

int insertInPosition(List* l, const void* data, unsigned data_size, int position)
{
    tNode *new_node, *cur = *l;
    if(!*l)
    {
        if(!(new_node = (tNode*)malloc(sizeof(tNode))) || !(new_node->info= malloc(data_size)))
        {
            free(new_node);
            return 0;
        }
        memcpy(new_node->info, data, data_size);
        new_node->size_info= data_size;
        new_node->prev = NULL;
        new_node->next = NULL;
    }
    else
    {
        while(cur->prev)
        {
            cur= (cur)->prev;
        }
        while(position>0 && (cur)->next)
        {
            position--;
            cur = (cur)->next;
        }


        if(!(new_node = (tNode*)malloc(sizeof(tNode))) || !(new_node->info= malloc(data_size)))
        {
            free(new_node);
            return 0;
        }
        memcpy(new_node->info, data, data_size);
        new_node->size_info= data_size;

        if(!cur->prev && position < 1)
        {
            //inserting at position 0
            new_node->prev = NULL;
            new_node->next = cur;

            cur->prev = new_node;

        }
        else if(!cur->next && position > 0)
        {
            //inserting in last position
            new_node->prev = cur;
            new_node->next = NULL;

            cur->next = new_node;

        }
        else
        {
            //Inserting in between nodes, always on the left side where cur is pointing to.
            new_node->next = cur;
            new_node->prev = cur->prev;

            cur->prev->next = new_node;
            cur->prev = new_node;
        }

    }
    *l = new_node;
    return 1;
}

/*===================================Traverse===================================*/
int GoLeftRight(const List* l, void(*action)(const void*))
{
    int count = 0;
    tNode* current = *l;
    if(current)
    {
        while(current->prev)
        {
            current = current->prev;
        }
        while(current)
        {
            action(current->info);
            current = current->next;
            count++;
        }
    }
    return count;
}
int GoRightLeft(const List* l, void(*action)(const void*))
{
    int count = 0;
    tNode* current = *l;
    if(current)
    {
        while(current->next)
        {
            current = current->next;
        }
        while(current)
        {
            action(current->info);
            current = current->prev;
            count++;
        }
    }
    return count;
}


/*===================================Sorting===================================*/
void SortList(List* l, int(*cmp)(const void*, const void*))
{
    tNode* current = *l, *minor, *pl;
    void* info;
    if(!current)
    {
        return;
    }
    while(current->prev)
    {
        current = current->prev;
    }
    while(current)
    {
        pl = current;
        minor = current;
        while(pl)
        {
            if(cmp(pl->info, minor->info)<0)
            {
                minor= pl;
            }
            pl = pl->next;
        }
        info = current->info;
        current->info = minor->info;
        minor->info = info;
        current = current->next;
    }
}

/*===================================Search===================================*/
List* findByKey_sortedList(List* l, void* key, int(*cmp)(const void*, const void*))
{
    tNode* current = *l;
    int comparison;
    if(!current)
    {
        return NULL;
    }
    while(cmp(key, current->info)<0 && current->prev)
    {
        current = current->prev;
    }
    while(cmp(key,current->info)>0 && current->next)
    {
        current = current->next;
    }
    comparison = cmp(key, current->info);
    if(comparison==0)
    {
        *l = current;
        return l;
    }
    return NULL;
}
List* finByKey_unsortedList(List* l,void* key, int(*cmp)(const void*, const void*))
{
    tNode* current = *l;
    int comparison;
    if(!current)
    {
        return NULL;
    }
    while(cmp(key, current->info)!=0 && current->prev)
    {
        current = current->prev;
    }

    comparison = cmp(key, current->info);
    if(comparison==0)
    {
        *l = current;
        return l;
    }
    else
    {
        current = *l;
    }

    while(cmp(key, current->info)!=0 && current->next)
    {
        current = current->next;
    }
    comparison = cmp(key, current->info);
    if(comparison==0)
    {
        *l = current;
        return l;
    }
    return NULL;
}

/*===================================Deletion===================================*/

int removeByKey(List* l, void* key, int(*cmp)(const void*, const void*))
{
    tNode* current = *l, *aux_next, *aux_prev;
    int comparison;
    if(!current)
    {
        return 0;
    }
    while(cmp(current->info, key)!=0 && current->prev)
    {
        current = current->prev;
    }
    while(cmp(current->info, key)!=0 && current->next)
    {
        current = current->next;
    }
    comparison = cmp(current->info, key);
    if(comparison==0)
    {
        aux_next = current->next;
        aux_prev = current->prev;
        if(aux_prev)
        {
            aux_prev->next = aux_next;
        }
        if(aux_next)
        {
            aux_next->prev = aux_prev;
            *l = aux_next;
        }
        else
        {
            *l = current;
        }
        free(current->info);
        free(current);
        return 1;
    }
    return 0;
}

int removeAllKeys(List* l, void* key, int (*cmp)(const void*, const void*))
{
    tNode* current = *l, *aux = *l, *aux_next, *aux_prev;
    int removed=0;
    while(current)
    {
        if(cmp(current->info,key)==0)
        {
            aux_next= current->next;
            aux_prev = current->prev;
            if(aux_prev)
            {
                aux_prev->next = aux_next;
            }
            if(aux_next)
            {
                aux_next->prev = aux_prev;
            }
            else
            {
                *l = aux_prev;
            }
            free(current->info);
            free(current);
            removed++;
        }
        current = current->next;
    }
    current = aux->prev; //go back to where the list originally was

    while(current)
    {
        if(cmp(current->info,key)==0)
        {
            aux_next= current->next;
            aux_prev = current->prev;
            if(aux_prev)
            {
                aux_prev->next = aux_next;
            }
            if(aux_next)
            {
                aux_next->prev = aux_prev;
            }
            else
            {
                *l = aux_prev;
            }
            free(current->info);
            free(current);
            removed++;
        }
        current = current->prev;
    }

    return removed;
}

/*===================================Misc===================================*/
void resumeOccurences(List* l, int (*cmp)(const void*, const void*), void (*resum)(void**, unsigned*, const void*, unsigned))
{
    tNode* current = *l;
    tNode* pl, *aux_next, *aux_prev;

    if (!current) {
        return;
    }
    while (current->prev) {
        current = current->prev;
    }
    while (current) {
        pl = current->next;
        while (pl) {
            if (cmp(pl->info, current->info) == 0) {
                if (resum) {
                    resum(&current->info, &current->size_info, pl->info, pl->size_info);
                }

                aux_next = pl->next;
                aux_prev = pl->prev;

                if (aux_prev) {
                    aux_prev->next = aux_next;
                }
                if (aux_next) {
                    aux_next->prev = aux_prev;
                }
                free(pl->info);
                free(pl);
                pl = aux_next;
            } else {
                pl = pl->next;
            }
        }
        current = current->next;
    }
}


/*===================================Map filter & reduce===================================*/
void filterList(List* l,const void* filter_param, int (*filter_function)(const void*, const void*))
{

    tNode* current = *l, *aux = *l, *aux_next, *aux_prev;
    while(current)
    {
        if(!filter_function(current->info, filter_param))
        {
            aux_next= current->next;
            aux_prev = current->prev;
            if(aux_prev)
            {
                aux_prev->next = aux_next;
            }
            if(aux_next)
            {
                aux_next->prev = aux_prev;
            }
            else
            {
                *l = aux_prev;
            }
            free(current->info);
            free(current);
        }
        current= current->prev;
    }
    current = aux->next;
    while(current)
    {
        if(!filter_function(current->info, filter_param))
        {
            aux_next= current->next;
            aux_prev = current->prev;
            if(aux_prev)
            {
                aux_prev->next = aux_next;
            }
            if(aux_next)
            {
                aux_next->prev = aux_prev;
            }
            else
            {
                *l = aux_prev;
            }
            free(current->info);
            free(current);
        }
        current= current->next;
    }
}

void mapList(List* l, const void* map_param, void(*map_function)(void**, unsigned*, const void*))
{
    tNode* current = *l;
    while(current){

        map_function(&current->info, &current->size_info, map_param);
        current = current->next;
    }
    current = (*l)->prev;
    while(current){

        map_function(&current->info, &current->size_info, map_param);
        current = current->prev;
    }
}

void reduceList(const List* l, void* result, void(*reduce_function)(const void*,unsigned*, void*)){
    tNode* current = *l;
    while(current){
        reduce_function(&current->info, &current->size_info, result);
        current = current->next;
    }
    current = (*l)->prev;
    while(current){
        reduce_function(&current->info, &current->size_info, result);
        current = current->prev;
    }
}

/*===================================Destruction===================================*/
int destroyList(List* l)
{
    int count = 0;
    tNode* aux = *l, *rem;
    if(aux)
    {
        while(aux->prev)
        {
            aux = aux->prev;
        }
        while(aux)
        {
            rem = aux->next;
            free(aux->info);
            free(aux);
            aux = rem;
            count++;
        }
        *l=NULL;
    }
    return count;
}
