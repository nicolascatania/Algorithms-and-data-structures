#include "dynamic_list.h"
void initializeList(List* pl)
{
    *pl = NULL;
}
int isEmpty(const List* pl)
{
    return *pl==NULL;
}
int isFull(const List* pl, const void* element,unsigned size_element)
{
    return 0;
}
int pushLast(List* pl,const void* element, unsigned size_element)
{
    Node* new_node;
    while(*pl)
    {
        pl = &(*pl)->next;
    }
    new_node = (Node*)malloc(sizeof(Node));
    if(!new_node || !(new_node->info = malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info, element, size_element);
    new_node->size_info = size_element;
    new_node->next = NULL;
    *pl= new_node;
    return 1;
}
int pushFirst(List* pl, const void* element, unsigned size_element)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node || !(new_node->info = malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info, element, size_element);
    new_node->size_info = size_element;
    new_node->next = *pl;
    *pl = new_node;
    return 1;
}
int popLast(List* pl, void* buffer, unsigned size_buffer)
{
    if(!*pl)
    {
        return 0;
    }
    while((*pl)->next)
    {
        pl = &(*pl)->next;
    }
    memcpy(buffer, (*pl)->info, MIN(size_buffer, (*pl)->size_info));
    free((*pl)->info);
    free(*pl);
    *pl = NULL;
    return 1;
}
int popFirst(List* pl, void* buffer, unsigned size_buffer)
{
    Node* aux = *pl;
    if(!*pl)
    {
        return 0;
    }
    *pl = (*pl)->next;
    memcpy(buffer, aux->info, MIN(size_buffer, aux->size_info));
    free(aux->info);
    free(aux);
    return 1;
}
int peekFirst(const List* pl, void* buffer, unsigned size_buffer)
{
    if(!*pl)
    {
        return 0;
    }
    memcpy(buffer, (*pl)->info, MIN(size_buffer, (*pl)->size_info));
    return 1;
}
int peekLast(const List* pl, void* buffer, unsigned size_buffer)
{
    if(!*pl)
    {
        return 0;
    }
    while((*pl)->next)
    {
        pl = &(*pl)->next;
    }
    memcpy(buffer, (*pl)->info, MIN(size_buffer, (*pl)->size_info));
    return 1;
}
void destroyList(List* pl)
{
    Node* aux;
    while(*pl)
    {
        aux = *pl;
        *pl = (*pl)->next;
        free(aux->info);
        free(aux);
    }
    *pl = NULL;
}
void showList(const List* pl, void(*show)(const void*))
{
    while(*pl)
    {
        show((*pl)->info);
        pl= &(*pl)->next;
    }
}

void showListRecursive(const List* pl, void(*show)(const void*))
{
    if(!*pl)
    {
        return;
    }
    show((*pl)->info);
    showListRecursive(&(*pl)->next,show);
}

void showListRecursive_Backwards(const List* pl, void(*show)(const void*))
{
    if(!*pl)
    {
        return;
    }
    showListRecursive_Backwards(&(*pl)->next,show);
    show((*pl)->info);
}

int countItems(const List* pl)
{
    int n=0;
    while(*pl)
    {
        pl= &(*pl)->next;
        n++;
    }
    return n;
}

List* searchNode(const List* pl, const void* key, int (*cmp)(const void*, const void*))
{
    while(*pl)
    {
        if(cmp((*pl)->info, key)==0)
        {
            return ((List*)pl);
        }
        pl = &(*pl)->next;
    }
    return NULL;
}

int insertSorted(List* pl, const void* element, unsigned size_element, int(*cmp)(const void*, const void*), void(*accumulate_item)(void**, unsigned*, const void*, unsigned))
{
    Node* new_node;
    while(*pl && cmp(element, (*pl)->info)>0)
    {
        pl= &(*pl)->next;
    }
    if(*pl && cmp(element,(*pl)->info)==0)
    {
        if(accumulate_item)
        {
            accumulate_item(&(*pl)->info, &(*pl)->size_info, element,size_element);
        }

        return DUPLICATED_ITEM;
    }
    if(!(new_node = (Node*)malloc(sizeof(Node))) || !(new_node->info = malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info, element, size_element);
    new_node->size_info = size_element;
    new_node->next = *pl;
    *pl = new_node;
    return 1;
}

Node* findMin(List* pl, int(*cmp)(const void*, const void*))
{
    Node* min = *pl;
    pl = &(*pl)->next;
    while(*pl)
    {
        if(cmp(min->info, (*pl)->info)>0)
        {
            min = *pl;
        }
        pl = &(*pl)->next;
    }
    return min;
}

int sortList(List* pl, int(*cmp)(const void*, const void*))
{
    Node* aux = *pl, *min;
    void* info;
    unsigned tam;
    if(!aux)
    {
        return 0;
    }
    while(aux->next)
    {
        if((min = findMin(&aux,cmp)) && min!=aux)
        {
            info = aux->info;
            tam = aux->size_info;
            aux->info = min->info;
            aux->size_info = min->size_info;
            min->info = info;
            min->size_info = tam;
        }
        aux = aux->next;
    }
    return 1;
}


int remove_First_Occurrence(List* pl, const void* key, int (*cmp)(const void*, const void*))
{
    Node* aux;
    Node* prev = NULL;

    if (!*pl)
    {
        return 0;
    }

    while (*pl)
    {
        if (cmp((*pl)->info, key) == 0)
        {
            aux = *pl;
            if (prev)
            {
                prev->next = (*pl)->next;
            }
            else
            {
                *pl = (*pl)->next;
            }
            free(aux->info);
            free(aux);
            return 1;
        }
        prev = *pl;
        pl = &(*pl)->next;
    }
    return 0;
}
int remove_All_Ocurrences(List* pl, const void* key, int (*cmp)(const void*, const void*))
{
    Node* aux;
    Node* prev = NULL;
    int count=0;
    if (!*pl)
    {
        return 0;
    }

    while (*pl)
    {
        if (cmp((*pl)->info, key) == 0)
        {
            aux = *pl;
            if (prev)
            {
                prev->next = (*pl)->next;
            }
            else
            {
                *pl = (*pl)->next;
            }
            free(aux->info);
            free(aux);
            count++;
            if(aux->next == NULL)
            {
                //this line is to avoid infinite loop when the last node is eliminated
                //because when *pl (aux) is destroyed and the condition in the while is evaluated
                //*pl is not null, but it is not something with any memory address associated.
                return count;
            }
        }
        prev = *pl;
        pl = &(*pl)->next;
    }
    return count;
}

int remove_Last_N_Ocurrences(List* pl, int n)
{
    Node* aux, *actual = *pl;
    while(n>0 && actual){
        n--;
        actual = actual->next;
    }
    while(actual){
        pl = &(*pl)->next;
        actual = actual->next;
    }
    while(*pl){
        aux = *pl;
        *pl = aux->next;
        free(aux->info);
        free(aux);
    }
    return 1;
}

void remove_at_position(List* pl, int position){
    Node* aux;
    while((*pl)->next && position>0){
        position--;
        pl = &(*pl)->next;
    }

    aux = *pl;
    *pl = aux->next;

    free(aux->info);
    free(aux);
}

int insert_at_position(List* pl, const void* element, unsigned size_element, int position)
{
    Node* new_node;

    if(!*pl || position<1)
    {
        if(!(new_node = (Node*)malloc(sizeof(Node))) || !(new_node->info= malloc(size_element)))
        {
            free(new_node);
            return 0;
        }
        memcpy(new_node->info, element, size_element);
        new_node->size_info= size_element;
        new_node->next = (*pl);
        *pl = new_node;
        return 1;
    }

    while(*pl && position>0)
    {
        position--;
        pl = &(*pl)->next;
    }

    if(!(new_node = (Node*)malloc(sizeof(Node))) || !(new_node->info= malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info, element, size_element);
    new_node->size_info= size_element;


    new_node->next = (*pl);
    *pl = new_node;
    return 1;
}


void mapC(List* pl, void (*mapFunction)(void*))
{
    while(*pl){
        mapFunction((*pl)->info);
        pl = &(*pl)->next;
    }

}
void filterC(List* pl, void* filter_parameter, int(*filterFunction)(const void*, const void*)){
    Node* aux;
    while(*pl){
        //if the node does not meet the filter requirements it will be removed
        if(!filterFunction((*pl)->info, filter_parameter)){
            aux = *pl;
            *pl = (*pl)->next;
            free(aux->info);
            free(aux);
        }
        else{
            pl = &(*pl)->next;
        }
    }
}
void reduce(List* pl, void* result, void(*reduceFunction)(const void*, void*)){
    while(*pl){
        reduceFunction((*pl)->info,result);
        pl = &(*pl)->next;
    }
}


