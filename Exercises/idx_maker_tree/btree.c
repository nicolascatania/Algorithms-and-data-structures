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

    return number_of_nodes_until_level_n(&(*p)->l, n-1) + number_of_nodes_until_level_n(&(*p)->r, n-1);
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
