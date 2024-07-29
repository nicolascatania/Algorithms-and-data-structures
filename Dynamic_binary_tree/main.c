#include "btree.h"
#include "utils.h"


int main()
{
    dsBinaryTree t, *found;
    int arr[] = {10,16,123,54,213,4,23,55,6,7,23};
    int arr_size = sizeof(arr)/sizeof(arr[0]);
    int key = 55, map_param=2, filter_param = 50;

    puts("=============================CREATION LOAD AND TRAVERSE=============================");
    create_binary_tree(&t);

    load_binary_tree_with_data_source(&t, arr, sizeof(arr[0]),arr_size, append_recursive, cmpInt);
    preorder(&t,stdout,NULL, printInt);

    puts("=============================TREE STATUS=============================");
    printf("Number of nodes: %d\n", number_of_nodes(&t));
    printf("Tree height: %d\n", binary_tree_height(&t));
    printf("Number of nodes until level 1: %d\n", number_of_nodes_until_level_n(&t,1));
    printf("Number of nodes in level 1: %d\n", number_of_nodes_in_level_n(&t,10));
    printf("Number of leaves: %d\n", number_of_leaves(&t));
    puts("Showing only leaves:");
    traverse_only_leaves(&t,stdout,NULL, printInt);


    puts("=============================SEARCH FUNCTIONS TEST=============================");
    found = search_key(&t, &key, cmpInt);
    puts("Founded(key): ");
    printInt(&(*found)->info, &(*found)->infoSize, stdout, NULL);
    puts("Sub tree: ");
    preorder(found, stdout, NULL, printInt);

    found = search_no_key(&t, &key, cmpInt);
    puts("Founded(no key): ");
    printInt(&(*found)->info, &(*found)->infoSize, stdout, NULL);
    puts("Sub tree: ");
    preorder(found, stdout, NULL, printInt);


    found = search_max_key(&t);
    puts("Founded(MAX key): ");
    printInt(&(*found)->info, &(*found)->infoSize, stdout, NULL);

    found = search_min_key(&t);
    puts("Founded(MIN key): ");
    printInt(&(*found)->info, &(*found)->infoSize, stdout, NULL);

    found = search_max_no_key(&t, cmpInt);
    puts("Founded(MAX no key): ");
    printInt(&(*found)->info, &(*found)->infoSize, stdout, NULL);

    found = search_min_no_key(&t, cmpInt);
    puts("Founded(MIN no key): ");
    printInt(&(*found)->info, &(*found)->infoSize, stdout, NULL);

    puts("=============================MAP=============================");
    printf("Multiplying each element by %d\n", map_param);
    map_binary_tree_c(&t, &map_param, multiply_int_by_n);
    preorder(&t,stdout, NULL, printInt);


    puts("=============================REMOVE NODE=============================");
    key= 110;
    remove_node(&t, &key, cmpInt);
    preorder(&t, stdout, NULL, printInt);

    puts("=============================FILTERING=============================");
    filter_binary_tree_c(&t, &filter_param, filter_int_greater);
    printf("Tree with nodes greater than: %d\n",filter_param);
    preorder(&t, stdout, NULL, printInt);

    puts("=============================REMOVING LEAVES=============================");
    printf("Removed: %d\n",remove_leaves(&t));
    preorder(&t, stdout, NULL,printInt);


    destroy_binary_tree(&t);
    return 0;
}
