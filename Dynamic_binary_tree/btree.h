#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "utils.h"

//Note:functions with prefix "_" are inner functions, should not be used by the user.
typedef struct sNode
{
    void* info;
    unsigned infoSize;
    struct sNode *l, *r;
}dsNode;

typedef dsNode* dsBinaryTree;

typedef int(*Cmp)(const void*, const void*);
typedef void(*Acc)(void**, unsigned*, const void*, unsigned);
typedef int(*InsertionType)(dsBinaryTree*, const void*, unsigned, Cmp cmp);
//Action used like show a integer (integer**, size*, stream*)
typedef void(*Action)(void**, unsigned*, const void* stream, const void* param);
typedef int(*ReadFunction)(void** data, unsigned data_size, void* pf, int position);


/*=============================================Creation=============================================*/
void create_binary_tree(dsBinaryTree* p);

/*=============================================Status=============================================*/
int is_empty_binary_tree(const dsBinaryTree* p);
int binary_tree_height(const dsBinaryTree* p);
int number_of_nodes(const dsBinaryTree* p);
int number_of_nodes_until_level_n(const dsBinaryTree* p, int n);
int number_of_nodes_in_level_n(const dsBinaryTree* p, int n);
int number_of_leaves(const dsBinaryTree* p);

int is_avl_binary_tree(const dsBinaryTree* p);
int is_balanced_binary_tree(const dsBinaryTree *p);
int is_complete_binary_tree(const dsBinaryTree *p);
/*=============================================Insertion=============================================*/
int append_recursive(dsBinaryTree* p, const void* data, unsigned data_size, Cmp cmp);
int append_iterative(dsBinaryTree* p, const void* data, unsigned data_size, Cmp cmp);

/*=============================================Load tree from data source=============================================*/

//REMAKE THE LAST ONE TO MAKE IT GENERIC, SO IT CAN ACCEPT TXT FILES OR ANY KIND OF FILE.

//load a tree with an array for example (the tree wont be balanced or something like it)
int load_binary_tree_with_data_source(dsBinaryTree* p, const void* input, unsigned input_size, int input_number_elements, InsertionType ins_type, Cmp cmp);

int load_from_sorted_bin_file(dsBinaryTree* p, const char* file_name, unsigned data_size, ReadFunction read_function);
int _load_from_sorted_data(dsBinaryTree* p, void* pf, unsigned data_size, ReadFunction read_function, int inf_limit, int sup_limit);
/*=============================================Traverse=============================================*/
void inorder(dsBinaryTree* p, const void* stream, const void* param, Action action);
void preorder(dsBinaryTree* p, const void* stream,const void* param, Action action);
void postorder(dsBinaryTree* p, const void* stream, const void* param,Action action);

void inorder_reverse(dsBinaryTree* p, const void* stream,const void* param,  Action action);
void preorder_reverse(dsBinaryTree* p, const void* stream, const void* param, Action action);
void postorder_reverse(dsBinaryTree* p, const void* stream, const void* param, Action action);

void traverse_only_leaves(dsBinaryTree* p, const void* stream, const void* param, Action action);


/*=============================================Search=============================================*/
dsBinaryTree* search_key(const dsBinaryTree* p, const void* key, Cmp cmp);
dsBinaryTree* search_no_key(const dsBinaryTree* p, const void* item, Cmp cmp);
void _search_no_key(const dsBinaryTree* p, const void* item, Cmp cmp, dsBinaryTree** nokey);
dsBinaryTree* search_max_key(const dsBinaryTree* p);
dsBinaryTree* search_min_key(const dsBinaryTree* p);
dsBinaryTree* search_max_no_key(const dsBinaryTree* p, Cmp cmp);
void _search_max_no_key(const dsBinaryTree* p, Cmp cmp, dsBinaryTree** nokey);
dsBinaryTree* search_min_no_key(const dsBinaryTree* p, Cmp cmp);
void _search_min_no_key(const dsBinaryTree* p, Cmp cmp, dsBinaryTree** nokey);

/*=============================================Map filter & reduce=============================================*/
void map_binary_tree_c(dsBinaryTree* p, const void* map_parameter,void(*map_function)(void** data, unsigned* data_size, const void* param));
//wont let a really balanced tree, like if there are only 3 nodes left, maybe there will be only one leave, instead of two leaves, the perfect scenario.
void filter_binary_tree_c(dsBinaryTree* p, const void* filter_parameter, int(*filter_function)(const void* data, const void* param));
void reduce_binary_tree_c(dsBinaryTree* p, void* result, void(*reduce_function)(const void* data, void* result));

/*=============================================Deletion=============================================*/
int remove_leaves(dsBinaryTree* p);
int remove_node(dsBinaryTree* p, const void* key, Cmp cmp);
int _remove_root(dsBinaryTree* p);


/*=============================================Destruction=============================================*/
void destroy_binary_tree(dsBinaryTree* p);


#endif // BTREE_H_INCLUDED
