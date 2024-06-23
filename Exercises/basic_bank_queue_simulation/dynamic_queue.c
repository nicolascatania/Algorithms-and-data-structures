#include "dynamic_queue.h"

void initializeQueue(tQueue* Q){
    Q->head = NULL;
    Q->rear = NULL;
}
int isEmpty(const tQueue* Q){
    return Q->head==NULL;
}
int isFull(const tQueue* Q, const void* element, unsigned size_element){
    return 0;
}
int Enqueue(tQueue* Q, const void* element, unsigned size_element){
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
    memcpy(new_node->info, element,size_element);
    new_node->sizeInfo = size_element;
    new_node->next=NULL;
    if(Q->rear){
        Q->rear->next = new_node;
    }
    else{
        Q->head = new_node;
    }
    Q->rear = new_node;
    return 1;

}
int Dequeue(tQueue* Q, void* buffer, unsigned size_buffer){
    tNode* aux = Q->head;
    if(!Q->head){
        return 0;
    }
    memcpy(buffer, Q->head->info, MIN(size_buffer, aux->sizeInfo));
    Q->head = aux->next;
    free(aux->info);
    free(aux);
    if(Q->head == NULL){
        Q->rear = NULL;
    }
    return 1;
}
int peek(const tQueue* Q, void* buffer, unsigned size_buffer){
    if(!Q->head){
        return 0;
    }
    memcpy(buffer, Q->head->info, MIN(size_buffer, Q->head->sizeInfo));
    return 1;
}
void DestroyQueue(tQueue* Q){
    tNode* aux;
    while(Q->head){
        aux = Q->head;
        Q->head = aux->next;
        free(aux->info);
        free(aux);
    }
    Q->rear = NULL;
}
