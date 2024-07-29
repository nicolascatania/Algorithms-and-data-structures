#include "btree.h"

/*=============================================Creation=============================================*/
void create_binary_tree(dsBinaryTree* p)
{
    *p = NULL;
}

/*=============================================Status=============================================*/
int is_empty_binary_tree(const dsBinaryTree* p)
{
    return *p == NULL;
}

int binary_tree_height(const dsBinaryTree* p)
{
    int lh, rh;
    if(!*p)
    {
        return 0;
    }
    lh = binary_tree_height(&(*p)->l);
    rh = binary_tree_height(&(*p)->r);
    return ((lh > rh ? lh : rh) + 1);
}


int number_of_nodes(const dsBinaryTree* p)
{
    if(!*p)
    {
        return 0;
    }

    return (number_of_nodes(&(*p)->l) + number_of_nodes(&(*p)->r) + 1);
}

int number_of_nodes_until_level_n(const dsBinaryTree* p, int n)
{
    if(!*p)
    {
        return 0;
    }
    else if(n==0)
    {
        return 1;
    }

    return number_of_nodes_until_level_n(&(*p)->l, n-1) + number_of_nodes_until_level_n(&(*p)->r, n-1) + 1;
}

int number_of_nodes_in_level_n(const dsBinaryTree* p, int n)
{
    if(!*p)
    {
        return 0;
    }
    else if(n > binary_tree_height(p))
    {
        return 0;
    }
    else if(n==0)
    {
        return 1;
    }

    return number_of_nodes_in_level_n(&(*p)->l, n-1) + number_of_nodes_in_level_n(&(*p)->r, n-1);
}

int number_of_leaves(const dsBinaryTree* p)
{
    int l=0;
    if(!*p)
    {
        return 0;
    }
    else if(!(*p)->l && !(*p)->r)
    {
        return 1;
    }

    l+= number_of_leaves(&(*p)->l);
    l+= number_of_leaves(&(*p)->r);
    return l;
}


int is_avl_binary_tree(const dsBinaryTree* p)
{
    int lh, rh;
    if(!*p)
    {
        return 1;
    }

    lh = binary_tree_height(&(*p)->l);
    rh = binary_tree_height(&(*p)->r);
    if(abs(lh-rh) > 1)
    {
        return 0;
    }

    return (is_avl_binary_tree(&(*p)->l) && is_avl_binary_tree(&(*p)->r));


}
int is_balanced_binary_tree(const dsBinaryTree *p)
{
    int h = binary_tree_height(p);
    int cn = number_of_nodes_until_level_n(p, h - 1 - 1); //definition says it is a balanced tree when is complete til the second to last level, that is the first (-1)
                                                          //Second (-1) comes from level = height - 1
    return ((cn == pow(2,h - 1) - 1)? 1:0);


}
int is_complete_binary_tree(const dsBinaryTree *p)
{
    int cn = number_of_nodes(p);
    int h = binary_tree_height(p);
    return ((cn == pow(2,h) - 1)? 1:0);
}



/*=============================================Insertion=============================================*/
int append_recursive(dsBinaryTree* p, const void* data, unsigned data_size, Cmp cmp)
{
    int comparison;
    if(!*p)
    {
        if(!(*p = (dsBinaryTree)malloc(sizeof(dsNode))) || !((*p)->info = malloc(data_size)))
        {

            free(*p);
            return ERROR_MEM;
        }
        memcpy((*p)->info, data, data_size);
        (*p)->infoSize = data_size;
        (*p)->l= NULL;
        (*p)->r= NULL;
    }
    else
    {

        comparison = cmp(data,(*p)->info);

        if(comparison==0)
        {
            return DUPLICATE;
        }
        else if( comparison > 0)
        {
            return append_recursive(&(*p)->r, data, data_size, cmp);
        }
        else
        {
            return append_recursive(&(*p)->l, data, data_size, cmp);
        }
    }

    return OK;
}
int append_iterative(dsBinaryTree* p, const void* data, unsigned data_size, Cmp cmp)
{
    int comparison;

    while(*p)
    {
        comparison = cmp(data, (*p)->info);
        if(comparison == 0)
        {
            return DUPLICATE;
        }
        else if(comparison > 0)
        {
            p = &(*p)->r;
        }
        else
        {
            p = &(*p)->l;
        }
    }
    if(!(*p = (dsBinaryTree)malloc(sizeof(dsNode))) || !((*p)->info = malloc(data_size)))
    {

        free(*p);
        return ERROR_MEM;
    }
    memcpy((*p)->info, data, data_size);
    (*p)->infoSize = data_size;
    (*p)->l= NULL;
    (*p)->r= NULL;

    return OK;
}

/*=============================================Load tree from data source=============================================*/
int load_binary_tree_with_data_source(dsBinaryTree* p, const void* input, unsigned input_size, int input_number_elements, InsertionType ins_type, Cmp cmp)
{
    int i;
    if(!input || !input_number_elements || !input_size)
    {
        return 0;
    }

    for (i=0; i<input_number_elements; i++)
    {
        ins_type(p, input + i*input_size, input_size, cmp);
    }

    return OK;
}

int load_from_sorted_bin_file(dsBinaryTree* p, const char* file_name, unsigned data_size, ReadFunction read_function)
{
    int c, r;
    FILE* pf = fopen(file_name, "rb");
    if(!pf || *p)
    {
        return 0;
    }
    fseek(pf,0, SEEK_END);
    c = ftell(pf)/data_size;

    r = _load_from_sorted_data(p, pf, data_size, read_function, 0, c-1);

    fclose(pf);
    return r;
}

int _load_from_sorted_data(dsBinaryTree* p, void* pf, unsigned data_size, ReadFunction read_function, int inf_limit, int sup_limit)
{
    int m = (inf_limit+sup_limit)/2, r;
    if(inf_limit> sup_limit)
    {
        return 1;
    }

    (*p) = (dsBinaryTree)malloc(sizeof(dsNode));
    if(!*p || !((*p)->infoSize = read_function(&(*p)->info, data_size, pf,m)))
    {
        free(*p);
        return ERROR_MEM;
    }
    (*p)->l = NULL;
    (*p)->r = NULL;

    if((r = _load_from_sorted_data(&(*p)->l, pf, data_size, read_function, inf_limit, m - 1))!= 1)
    {
        return r;
    }

    return _load_from_sorted_data(&(*p)->r, pf, data_size, read_function, m + 1, sup_limit);
}

/*=============================================Traverse=============================================*/
void inorder(dsBinaryTree* p, const void* stream,const void* param, Action action)
{
    if(!*p)
    {
        return;
    }
    else
    {
        inorder(&(*p)->l, stream, param, action);
        action(&(*p)->info, &(*p)->infoSize, stream, param);
        inorder(&(*p)->r, stream,param, action);
    }
}
void preorder(dsBinaryTree* p, const void* stream,const void* param, Action action)
{
    if(!*p)
    {
        return;
    }
    else
    {
        action(&(*p)->info, &(*p)->infoSize, stream, param);
        preorder(&(*p)->l, stream,param, action);
        preorder(&(*p)->r, stream,param, action);
    }
}
void postorder(dsBinaryTree* p, const void* stream,const void* param, Action action)
{
    if(!*p)
    {
        return;
    }
    else
    {
        postorder(&(*p)->l, stream,param, action);
        postorder(&(*p)->r, stream,param, action);
        action(&(*p)->info, &(*p)->infoSize, stream, param);
    }
}


void inorder_reverse(dsBinaryTree* p, const void* stream,const void* param, Action action)
{
    if(!*p)
    {
        return;
    }
    else
    {
        inorder_reverse(&(*p)->r, stream,param, action);
        action(&(*p)->info, &(*p)->infoSize, stream, param);
        inorder_reverse(&(*p)->l, stream,param, action);
    }
}
void preorder_reverse(dsBinaryTree* p, const void* stream,const void* param, Action action)
{
    if(!*p)
    {
        return;
    }
    else
    {
        action(&(*p)->info, &(*p)->infoSize, stream, param);
        preorder_reverse(&(*p)->r, stream,param, action);
        preorder_reverse(&(*p)->l, stream, param,action);
    }
}
void postorder_reverse(dsBinaryTree* p, const void* stream, const void* param,Action action)
{
    if(!*p)
    {
        return;
    }
    else
    {
        postorder_reverse(&(*p)->r, stream,param, action);
        postorder_reverse(&(*p)->l, stream,param, action);
        action(&(*p)->info, &(*p)->infoSize, stream, param);
    }
}


void traverse_only_leaves(dsBinaryTree* p, const void* stream, const void* param, Action action)
{
    if(!*p)
    {
        return;
    }

    if(!(*p)->l && !(*p)->r)
    {
        action(&(*p)->info, &(*p)->infoSize, stream, param);
    }
    else
    {
        traverse_only_leaves(&(*p)->l, stream, param, action);
        traverse_only_leaves(&(*p)->r, stream, param, action);
    }


}


/*=============================================Search=============================================*/
dsBinaryTree* search_key(const dsBinaryTree* p, const void* key, Cmp cmp)
{
    int c;
    if(!*p)
    {
        return NULL;
    }
    else
    {
        while(*p && (c = cmp(key, (*p)->info)))
        {
            if(c<0)
            {
                p = &(*p)->l;
            }
            else
            {
                p = &(*p)->r;
            }
        }

    }
    return (dsBinaryTree*)p;
}
dsBinaryTree* search_no_key(const dsBinaryTree* p, const void* item, Cmp cmp)
{
    dsBinaryTree* result = (dsBinaryTree*)p;
    if(!*p)
    {
        return NULL;
    }
    _search_no_key(p, item, cmp, &result);

    if(!result)
    {
        return NULL;
    }

    return result;
}

void _search_no_key(const dsBinaryTree* p, const void* item, Cmp cmp, dsBinaryTree** nokey)
{
    if(!*p)
    {
        return;
    }
    if((cmp((*p)->info, item))==0)
    {
        *nokey = (dsBinaryTree*)p;
    }
    _search_no_key(&(*p)->l, item, cmp, nokey);
    _search_no_key(&(*p)->r, item, cmp, nokey);
}
dsBinaryTree* search_max_key(const dsBinaryTree* p)
{
    while((*p)->r)
    {
        p = &(*p)->r;
    }
    return (dsBinaryTree*)p;
}
dsBinaryTree* search_min_key(const dsBinaryTree* p)
{
    while((*p)->l)
    {
        p = &(*p)->l;
    }
    return (dsBinaryTree*)p;
}
dsBinaryTree* search_max_no_key(const dsBinaryTree* p, Cmp cmp)
{
    dsBinaryTree* result = (dsBinaryTree*)p;
    _search_max_no_key(p, cmp, &result);
    if(!result)
    {
        return NULL;
    }

    return result;
}

void _search_max_no_key(const dsBinaryTree* p, Cmp cmp, dsBinaryTree** nokey)
{
    if(!*p)
    {
        return;
    }
    else if(cmp((**nokey)->info,(*p)->info) < 0)
    {
        *nokey = (dsBinaryTree*)p;
    }
    _search_max_no_key(&(*p)->l, cmp, nokey);
    _search_max_no_key(&(*p)->r, cmp, nokey);

}
dsBinaryTree* search_min_no_key(const dsBinaryTree* p, Cmp cmp)
{
    dsBinaryTree* result = (dsBinaryTree*)p;
    _search_min_no_key(p, cmp, &result);
    if(!result)
    {
        return NULL;
    }

    return result;
}
void _search_min_no_key(const dsBinaryTree* p, Cmp cmp, dsBinaryTree** nokey)
{
    if(!*p)
    {
        return;
    }
    else if(cmp((**nokey)->info,(*p)->info) > 0)
    {
        *nokey = (dsBinaryTree*)p;
    }
    _search_min_no_key(&(*p)->l, cmp, nokey);
    _search_min_no_key(&(*p)->r, cmp, nokey);
}

/*=============================================Map filter & reduce=============================================*/
void map_binary_tree_c(dsBinaryTree* p, const void* map_parameter, void(*map_function)(void** data, unsigned* data_size, const void* param))
{
    if(!*p)
    {
        return;
    }
    map_function(&(*p)->info, &(*p)->infoSize, map_parameter);
    map_binary_tree_c(&(*p)->l, map_parameter, map_function);
    map_binary_tree_c(&(*p)->r, map_parameter, map_function);
}
void filter_binary_tree_c(dsBinaryTree* p, const void* filter_parameter, int(*filter_function)(const void* data, const void* param))
{
    if(!*p)
    {
        return;
    }

    filter_binary_tree_c(&(*p)->l, filter_parameter, filter_function);
    filter_binary_tree_c(&(*p)->r, filter_parameter, filter_function);

    if(filter_function((*p)->info, filter_parameter)!=1)
    {
        _remove_root(p);
    }


}


void reduce_binary_tree_c(dsBinaryTree* p, void* result, void(*reduce_function)(const void* data, void* result));

/*=============================================Deletion=============================================*/
int remove_leaves(dsBinaryTree* p)
{
    if(!*p)
    {
        return 0;
    }
    if(!(*p)->l && !(*p)->r)
    {
       free((*p)->info);
       free(*p);
       *p = NULL;
       return 1;
    }

    return remove_leaves(&(*p)->r) + remove_leaves(&(*p)->l);
}
int remove_node(dsBinaryTree* p, const void* key,Cmp cmp)
{
    dsBinaryTree* node_to_delete= search_key(p, key, cmp);
    if(!node_to_delete)
    {
        return 0;
    }

    return _remove_root(node_to_delete);
}
int _remove_root(dsBinaryTree* p)
{
    dsBinaryTree* node_to_delete;
    dsNode* del;
    int lh, rh;
    if(!*p)
    {
        return 0;
    }
    free((*p)->info);
    if(!(*p)->l && !(*p)->r)
    {
        free(*p);
        *p = NULL;
        return 1;
    }
    else
    {
        lh = binary_tree_height(&(*p)->l);
        rh = binary_tree_height(&(*p)->r);
        if(lh>rh)
        {
            node_to_delete = search_max_key(&(*p)->l);
        }
        else
        {
            node_to_delete = search_min_key(&(*p)->r);
        }

        del = *node_to_delete;
        (*p)->info = del->info;
        (*p)->infoSize= del->infoSize;

        *node_to_delete = del->l ? del->l : del->r;

        free(del);

        return 1;

    }
}


/*=============================================Destruction=============================================*/
void destroy_binary_tree(dsBinaryTree* p)
{
    if(!*p)
    {
        return;
    }
    else
    {
        destroy_binary_tree(&(*p)->l);
        destroy_binary_tree(&(*p)->r);
        free((*p)->info);
        free(*p);
        *p = NULL;
    }
}
