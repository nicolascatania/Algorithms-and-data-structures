#include "dynamic_stack.h"

void createStack(tStack* stack){
    *stack=NULL;
}
int isFull(const tStack* stack, const void* element, unsigned size_element){
    return 0;
}
int isEmpty(const tStack* stack){
    return *stack == NULL;
}
int push(tStack* stack, const void* element, unsigned size_element){
    tNode* new_node;

    new_node = (tNode*)malloc(sizeof(tNode));
    if(!new_node){
        return 0;
    }
    new_node->info = malloc(size_element);
    if(!new_node->info){
        free(new_node);
        return 0;
    }
    memcpy(new_node->info,element,size_element);
    new_node->sizeInfo = size_element;
    new_node->next = *stack;
    *stack = new_node;
    return 1;

}
int pop(tStack* stack, void* buffer, unsigned size_buffer){
    tNode* aux;
    if(!*stack){
        return 0;
    }
    memcpy(buffer, (*stack)->info, MIN(size_buffer, (*stack)->sizeInfo));
    aux = *stack;
    *stack = (*stack)->next;
    free(aux->info);
    free(aux);
    return 1;
}
int peek(const tStack* stack, void* buffer, unsigned size_buffer){
    if(!*stack){
        return 0;
    }
    memcpy(buffer, (*stack)->info, MIN(size_buffer, (*stack)->sizeInfo));
    return 1;
}
void destroy(tStack* stack){
    tNode* aux;
    while(*stack){
        aux = *stack;
        *stack = (*stack)->next;
        free(aux->info);
        free(aux);
    }
}
