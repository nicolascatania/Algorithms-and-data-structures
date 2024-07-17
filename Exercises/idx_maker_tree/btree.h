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

int append_iterative(dsBinaryTree* p, const void* data, unsigned data_size, Cmp cmp);

/*=============================================Load tree from data source=============================================*/


int load_from_sorted_bin_file(dsBinaryTree* p, const char* file_name, unsigned data_size, ReadFunction read_function);

int _load_from_sorted_data(dsBinaryTree* p, void* pf, unsigned data_size, ReadFunction read_function, int inf_limit, int sup_limit);
/*=============================================Traverse=============================================*/
void inorder(dsBinaryTree* p, const void* stream, const void* param, Action action);


/*=============================================Map filter & reduce=============================================*/
void map_binary_tree_c(dsBinaryTree* p, const void* map_parameter,void(*map_function)(void** data, unsigned* data_size, const void* param));
//wont let a really balanced tree, like if there are only 3 nodes left, maybe there will be only one leave, instead of two leaves, the perfect scenario.
void filter_binary_tree_c(dsBinaryTree* p, const void* filter_parameter, int(*filter_function)(const void* data, const void* param));
void reduce_binary_tree_c(dsBinaryTree* p, void* result, void(*reduce_function)(const void* data, void* result));


/*=============================================Destruction=============================================*/
void destroy_binary_tree(dsBinaryTree* p);


#endif // BTREE_H_INCLUDED
