#include "circular_stack.h"

void initializeStack(Stack* s){
    *s = NULL;
}
int isFull(const Stack* s, void* element, unsigned size_element){
    return 0;
}
int isEmpty(const Stack* s){
    return *s==NULL;
}
int push(Stack* s, void* element, unsigned size_element){
    tNode* new_node;
    if(!(new_node = (tNode*)malloc(sizeof(tNode))) || !(new_node->info = malloc(size_element)))
    {
        free(new_node);
        return 0;
    }
    memcpy(new_node->info, element,size_element);
    new_node->size_info = size_element;
    if(!*s)
    {
        new_node->next = new_node;
        *s = new_node;
    }
    else
    {
        new_node->next = (*s)->next;
        (*s)->next= new_node;
    }
    return 1;
}
int pop(Stack* s, void* buffer, unsigned size_buffer){
    tNode* aux;
    if(!*s)
    {
        return 0;
    }
    aux = (*s)->next;
    memcpy(buffer, aux->info, MIN(size_buffer, aux->size_info));
    if(aux == *s)
    {
        *s = NULL;
    }
    else
    {
        (*s)->next = aux->next;
    }

    free(aux->info);
    free(aux);
    return 1;
}
int Peek(const Stack* s, void* buffer, unsigned size_buffer){
    if(!*s)
    {
        return 0;
    }
    memcpy(buffer, (*s)->next->info, MIN(size_buffer, (*s)->next->size_info));
    return 1;
}
void destroyStack(Stack* s){
    tNode* aux;
    while(*s)
    {
        aux = (*s)->next;
        if(*s == aux)
        {
            *s= NULL;
        }
        else
        {
            (*s)->next = aux->next;
        }
        free(aux->info);
        free(aux);
    }
}
