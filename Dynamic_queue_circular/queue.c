#include "queue.h"



void initializeQueue(Queue* q)
{
    *q = NULL;
}
int isFull(const Queue* q, void* element, unsigned size_element)
{
    return 0;
}
int isEmpty(const Queue* q)
{
    return *q==NULL;
}
int Enqueue(Queue* q, void* element, unsigned size_element)
{

    tNode* new_node;
    if(!(new_node = (tNode*)malloc(sizeof(tNode))) || !(new_node->info = malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info, element,size_element);
    new_node->size_info = size_element;
    if(!*q)
    {
        new_node->next = new_node;
    }
    else
    {
        new_node->next = (*q)->next;
        (*q)->next= new_node;
    }
    *q = new_node;
    return 1;
}
int Dequeue(Queue* q, void* buffer, unsigned size_buffer)
{
    tNode* aux;
    if(!*q)
    {
        return 0;
    }
    aux = (*q)->next;
    memcpy(buffer, aux->info, MIN(size_buffer, aux->size_info));
    if(aux == *q)
    {
        *q = NULL;
    }
    else
    {
        (*q)->next = aux->next;
    }

    free(aux->info);
    free(aux);
    return 1;
}
int Peek(const Queue* q, void* buffer, unsigned size_buffer)
{
    if(!*q)
    {
        return 0;
    }
    memcpy(buffer, (*q)->next->info, MIN(size_buffer, (*q)->next->size_info));
    return 1;
}
void destroyQueue(Queue* q)
{
    tNode* aux;
    while(*q)
    {
        aux = (*q)->next;
        if(*q == aux)
        {
            *q= NULL;
        }
        else
        {
            (*q)->next = aux->next;
        }
        free(aux->info);
        free(aux);
    }
}
