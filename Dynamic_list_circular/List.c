#include "List.h"

/*=============================================Creation=============================================*/

void createList(dsList* p)
{
    *p = NULL;
}

/*=============================================List status=============================================*/
int isEmptyList(const dsList* p)
{
    return *p == NULL;
}
int isFullList(const dsList* p, const void* data, unsigned tam)
{
    return 0;
}

/*=============================================Insertion=============================================*/
int insertAtBegining(dsList* p, const void* data, unsigned data_size)
{
    dsNode* nu;
    if(!(nu = (dsNode*)malloc(sizeof(dsNode))) || !(nu->info = malloc(data_size)))
    {
        free(nu);
        return ERROR_MEM;
    }

    memcpy(nu->info, data, data_size);
    nu->infoSize = data_size;

    if(*p == NULL)
    {
        nu->next = nu;
        *p = nu;
    }
    else
    {
        nu->next = (*p)->next;
        (*p)->next = nu;
    }

    return OK;
}
int insertAtEnd(dsList*p, const void* data, unsigned data_size)
{
    dsNode* nu;
    if(!(nu = (dsNode*)malloc(sizeof(dsNode))) || !(nu->info = malloc(data_size)))
    {
        free(nu);
        return ERROR_MEM;
    }

    memcpy(nu->info, data, data_size);
    nu->infoSize = data_size;

    if(*p == NULL)
    {
        nu->next = nu;
    }
    else
    {
        nu->next = (*p)->next;
        (*p)->next = nu;
    }

    *p = nu;

    return OK;

}
int insertAtPosition(dsList* p, const void* data, unsigned data_size, int pos)
{
    dsNode* nu;
    dsList* cur;

    if(!(*p))
    {
        if(!(nu = (dsNode*)malloc(sizeof(dsNode))) || !(nu->info = malloc(data_size)))
        {
            free(nu);
            return ERROR_MEM;
        }

        memcpy(nu->info, data, data_size);
        nu->infoSize = data_size;
        nu->next = nu;
        *p = nu;
    }
    else
    {
        cur = &(*p)->next;
        while(*cur && *cur != *p && pos>0)
        {
            pos--;
            cur = &((*cur)->next);
        }

        if(!(nu = (dsNode*)malloc(sizeof(dsNode))) || !(nu->info = malloc(data_size)))
        {
            free(nu);
            return ERROR_MEM;
        }

        memcpy(nu->info, data, data_size);
        nu->infoSize = data_size;

        if(*cur == *p && pos>0)
        {
            //completed a lap.
            nu->next = (*p)->next;
            (*p)->next = nu;
            *p = nu;
        }
        else
        {
            //pos == 0 and no lap completed
            nu->next = *cur;
            *cur = nu;
        }
    }

    return OK;

}
int insertSorted(dsList* p, const void* data, unsigned data_size, Cmp cmp, Acc acc)
{
    dsNode* nu;
    dsList* cur = &(*p)->next;
    int comparison;

    if(!(*p))
    {
        if(!(nu = (dsNode*)malloc(sizeof(dsNode))) || !(nu->info = malloc(data_size)))
        {
            free(nu);
            return ERROR_MEM;
        }

        memcpy(nu->info, data, data_size);
        nu->infoSize = data_size;
        nu->next = nu;
        *p = nu;
        return OK;

    }

    while(*cur && *cur != *p && cmp(data, (*cur)->info)>0)
    {
        cur = &((*cur)->next);
    }

    comparison = cmp(data, (*cur)->info);

    if(comparison==0)
    {
        if(acc)
        {
            acc(&(*cur)->info, &(*cur)->infoSize, data, data_size);
        }
        return DUPLICATE;
    }
    else if (comparison >0)
    {
        if(!(nu = (dsNode*)malloc(sizeof(dsNode))) || !(nu->info = malloc(data_size)))
        {
            free(nu);
            return ERROR_MEM;
        }

        memcpy(nu->info, data, data_size);
        nu->infoSize = data_size;
        //we need to insert on the last position.
        nu->next = (*p)->next;
        (*p)->next = nu;
        *p = nu;
    }
    else
    {
        //insertion at any position except the last one.
        if(!(nu = (dsNode*)malloc(sizeof(dsNode))) || !(nu->info = malloc(data_size)))
        {
            free(nu);
            return ERROR_MEM;
        }

        memcpy(nu->info, data, data_size);
        nu->infoSize = data_size;
        nu->next = *cur;
        *cur = nu;
    }

    return OK;
}

/*=============================================Load List With Data Source=============================================*/
//accepts only insertAtBegining and insertAtEnd
int loadListFromSourceData(dsList* p, const void* input, unsigned input_size, int input_number_elements, InsertionType ins_type)
{
    int i;
    if(!input || !input_number_elements || !input_size)
    {
        return 0;
    }

    for ( i=0; i<input_number_elements; i++)
    {
        ins_type(p, input + i*input_size, input_size);
    }

    return OK;
}


/*=============================================Sorting=============================================*/
void sortList(dsList* p, Cmp cmp)
{
    dsList* cur = &(*p)->next, *minor, *mayor, *sublist;
    dsNode* aux;

    int number_elements, i, n=0;

    if(!*p || *p == (*p)->next)
    {
        return;
    }

    number_elements = listLen(p);

    while(*cur != *p)
    {
        sublist = cur;
        minor = cur;
        for(i=0; i<number_elements - n; i++)
        {
            if(cmp((*minor)->info, (*sublist)->info)>0)
            {
                minor = sublist;
            }
            sublist = &(*sublist)->next;
        }
        if(minor != cur)
        {
            aux = *cur;
            *cur = *minor;
            *minor = (*minor)->next;
            (*cur)->next = aux;
        }
        cur = &(*cur)->next;
        n++;
    }

    //i can not use search_mayor_key because the list is not ordered at all yet.
    //so i need to find the mayor key (wich is always in the first position, i dont know why) and make it be the last element.
    mayor = search_mayor_noKey(p, cmp);
    *p = *mayor;
}

/*=============================================Traverse=============================================*/
void traverseList(dsList* p, Action action, void* stream)
{
    dsNode* aux;
    if(!(*p))
    {
        return;
    }
    aux = (*p)->next;
    do
    {
        action(&(aux->info), &(aux->infoSize), stream);
        aux = aux->next;
    }
    while(aux != (*p)->next);
}

/*=============================================Search=============================================*/
dsList* search_minorKey_unordered_subList(dsList* _start, dsList* _end, Cmp cmp)
{
    dsList* minor = _start;
    if(!*_start)
    {
        return NULL;
    }
    do
    {
        if(cmp((*minor)->info, (*_start)->info)>0)
        {
            minor = _start;
        }
        _start = &(*_start)->next;
    }
    while(*_start && *_start != *_end);

    return minor;
}

//Returns first occurence of the matching key, searches all over the whole list.
dsList* search_key(const dsList* p, const void* key, Cmp cmp)
{
    dsList* cur = &(*p)->next;
    if(!*p)
    {
        return NULL;
    }

    while(*cur  && *cur !=*p && cmp(key, (*cur)->info)!=0)
    {
        cur = &(*cur)->next;
    }
    if(cmp(key, (*cur)->info)==0)
    {
        return cur;
    }

    return NULL;
}

//optimized for ordered lists.
dsList* search_mayorKey_ordered_list(const dsList* p, Cmp cmp)
{
    return *p ? (dsList*)p : NULL;
}
dsList* search_minorKey_ordered_list(const dsList* p, Cmp cmp)
{
    return *p ? (dsList*)&(*p)->next : NULL;
}

//searches elements by nokey fields, the list does not have to be ordered.
dsList* search_mayor_noKey(const dsList* p, Cmp cmp)
{
    dsList* cur = &(*p)->next;
    dsList* m;
    if(!*p)
    {
        return NULL;
    }

    m = cur;

    do
    {
        if(cmp((*cur)->info, (*m)->info)>0)
        {
            m = cur;
        }
        cur = &(*cur)->next;
    }
    while(*cur && *cur != (*p)->next);
    return m;
}
dsList* search_minor_noKey(const dsList* p, Cmp cmp)
{
    dsList* cur = &(*p)->next;
    dsList* m;
    if(!*p)
    {
        return NULL;
    }

    m = cur;

    do
    {
        if(cmp((*cur)->info, (*m)->info)<0)
        {
            m = cur;
        }
        cur = &(*cur)->next;
    }
    while(*cur && *cur != (*p)->next);
    return m;
}

//returns a new list with all the matches
dsList search_Mayors_noKey(const dsList* p, Cmp cmp)
{
    dsList nuList;
    dsList* cur = &(*p)->next;
    dsList* m;

    if(!*p)
    {
        return NULL;
    }

    createList(&nuList);
    m = search_mayor_noKey(p, cmp);

    do
    {
        if(cmp((*cur)->info, (*m)->info)==0)
        {
            if(!insertAtBegining(&nuList, (*cur)->info, (*cur)->infoSize))
            {
                destroyList(&nuList);
                return NULL;
            }
        }
        cur = &(*cur)->next;
    }
    while(*cur && *cur != (*p)->next);

    return nuList;
}
dsList search_Minor_noKey(const dsList* p, Cmp cmp)
{
    dsList nuList;
    dsList* cur = &(*p)->next;
    dsList* m;

    if(!*p)
    {
        return NULL;
    }

    createList(&nuList);
    m = search_minor_noKey(p, cmp);

    do
    {
        if(cmp((*cur)->info, (*m)->info)==0)
        {
            if(!insertAtBegining(&nuList, (*cur)->info, (*cur)->infoSize))
            {
                destroyList(&nuList);
                return NULL;
            }
        }
        cur = &(*cur)->next;
    }
    while(*cur && *cur != (*p)->next);

    return nuList;
}
/*=============================================Count items=============================================*/
int listLen(const dsList* p)
{
    int c = 0;
    dsList* cur = (dsList*)p;
    if(!*p)
    {
        return 0;
    }
    do
    {
        c++;
        cur = &(*cur)->next;
    }
    while(*cur && *cur != *p);
    return c;
}

/*=============================================Randomize functions=============================================*/
void randomizePointerToList(dsList* p, int number_elements)
{
    int r = rand()&(number_elements);
    while(r)
    {
        r--;
        *p = (*p)->next;
    }
}

void shuffle_list(dsList* p, int number_elements)
{
    dsList* sublist = &(*p)->next, *rnd, *slStart;
    dsNode* aux;
    int r;

    if(!*p)
    {
        return;
    }

    while(number_elements)
    {
        r= rand()&(number_elements);
        slStart = sublist;
        rnd = sublist;
        while(r)
        {
            rnd = &(*rnd)->next;
            r--;
        }
        if(rnd!= slStart)
        {
            aux = *slStart;
            *slStart = *rnd;
            *rnd = (*rnd)->next;
            (*slStart)->next = aux;
        }
        sublist = &(*sublist)->next;
        number_elements--;
    }
}

//needs cmp to make sure there it is not inserting duplicated items.
dsList generate_random_list_with_n_elements(const dsList* source, int n, int source_number_elements, Cmp cmp)
{
    dsList *cur = &(*source)->next, nuList, *rnd;
    int r;

    if(!*source)
    {
        return NULL;
    }

    if(n>source_number_elements)
    {
        return NULL;
    }

    createList(&nuList);

    while(n)
    {
        r = rand()%source_number_elements;
        rnd = cur;
        while(r)
        {
            rnd = &(*rnd)->next;
            r--;
        }
        if(!search_key(&nuList, (*rnd)->info, cmp))
        {
            if(!insertAtBegining(&nuList, (*rnd)->info, (*rnd)->infoSize))
            {
                destroyList(&nuList);
                return NULL;
            }
            n--;
        }
        cur = &(*cur)->next;
    }

    return nuList;
}

void leave_list_with_random_n_elements(dsList* p, int n, int number_elements)
{
    dsList* cur = &(*p)->next;
    dsNode* del;
    int r;

    if(!*p || !n || !number_elements || n == number_elements)
    {
        return;
    }

    while(number_elements > n)
    {
        r = rand()%number_elements;
        while(r)
        {
            cur = &(*cur)->next;
            r--;
        }
        del = *cur;
        *cur = (*cur)->next;

        if(del == *p)
        {
            *p = (*p)->next;
        }

        free(del->info);
        free(del);
        number_elements--;
    }

}


/*=============================================Map Filter & Reduce (Python like functionality)=============================================*/
dsList map_py(dsList* p, void* param, void(*mapping)(void*, const void*))
{
    dsList nuList, *cur = &(*p)->next;
    void* buffer = malloc((*cur)->infoSize);
    if(!*p || !buffer)
    {
        return NULL;
    }

    createList(&nuList);
    do
    {
        memcpy(buffer, (*cur)->info, (*cur)->infoSize);
        mapping(buffer, param);
        if(!insertAtBegining(&nuList, buffer, (*cur)->infoSize))
        {
            destroyList(&nuList);
            free(buffer);
            return NULL;
        }
        cur = &(*cur)->next;
    }
    while(*cur && *cur !=(*p)->next);

    free(buffer);

    return nuList;
}
dsList filter_py(dsList* p, void* filtr, int(*filter_func)(const void*, const void*))
{
    dsList nuList, *cur = &(*p)->next;
    if(!*p)
    {
        return NULL;
    }
    createList(&nuList);
    do
    {
        if(filter_func((*cur)->info,filtr)==1)
        {
            if(!insertAtBegining(&nuList, (*cur)->info, (*cur)->infoSize))
            {
                return NULL;
            }
        }
        cur = &(*cur)->next;

    }while(*cur && *cur != (*p)->next);

    return nuList;
}
void reduce_py(dsList* p, void* result, void(*reduce_func)(void*, const void*))
{
    dsList *cur = &(*p)->next;
    if(!*p)
    {
        return;
    }
    do
    {
        reduce_func(result, (*cur)->info);
        cur = &(*cur)->next;
    }while(*cur && *cur != (*p)->next);
}


/*=============================================Deletion=============================================*/
int deleteFirst(dsList* p, void* buffer, unsigned buffer_size)
{
    dsNode* del = (*p)->next;
    if(!*p){
        return EMPTY_LIST;
    }

    memcpy(buffer, del->info, del->infoSize);
    if(*p == (*p)->next)
    {
        free((*p)->next);
        free(*p);
        *p = NULL;
    }
    else
    {
        (*p)->next= del->next;
        free(del->info);
        free(del);
    }

    return OK;
}

int deleteLast(dsList* p, void* buffer, unsigned buffer_size)
{
    dsList* cur = &(*p)->next;
    dsNode* del = *p;
    if(!del){
        return EMPTY_LIST;
    }
    memcpy(buffer, del->info, del->infoSize);
    //if just one last item in list
    if(*p == (*p)->next)
    {
        *p = NULL;
    }
    else
    {
        //moving towards second to last element.
        while((*cur)->next != *p)
        {
            cur = &(*p)->next;
        }
        (*cur)->next = del->next;
        *p = *cur;
    }
    free(del->info);
    free(del);

    return OK;
}

int deleteInPosition(dsList *p, void* buffer, unsigned buffer_size, int position)
{
    dsList* cur = &(*p)->next, *prev;
    dsNode* del;
    if(!*p){
        return EMPTY_LIST;
    }

    while(position && *cur !=*p)
    {
        prev = cur;
        cur = &(*cur)->next;
        position--;
    }
    del = *cur;
    memcpy(buffer, del->info, del->infoSize);
    if(*p == *cur)
    {
        free((*p)->info);
        free((*p));
        *p=NULL;
    }
    else
    {
        //if the last item is to be deleted, i just make the pointer to list point to the second to last.
        if(del == *p)
        {
            *p = *prev;
        }
        *cur = del->next;

        free(del->info);
        free(del);
    }
    return OK;
}

/*=============================================Destruction=============================================*/
void destroyList(dsList* p)
{
    dsNode* aux = *p, *del;
    if(!aux)
    {
        return;
    }
    aux = (*p)->next;
    do
    {
        del = aux;
        aux = aux->next;
        free(del->info);
        free(del);
    }while(aux != (*p));
    *p = NULL;
}
