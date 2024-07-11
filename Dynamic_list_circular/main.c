#include "List.h"
/*=============================================Comparison Functions=============================================*/
int compareInt(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

/*=============================================Action Functions=============================================*/
void printInt(void** info, unsigned* infoSize, const void* stream) {
    printf("%d ", *(int*)(*info));
}


//really basic testing.
int main() {
    dsList myList, list;
    createList(&myList);
    createList(&list);

    int arr[] = {5, 3, 8, 1, 2, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    loadListFromSourceData(&list,arr,sizeof(arr[0]),n,insertAtEnd);
    printf("Loaded list (insert at end)\n");
    traverseList(&list,printInt,NULL);
    printf("\n");

    sortList(&list, compareInt);
    printf("Loaded list sorted:\n");
    traverseList(&list,printInt,NULL);
    printf("\n");



    printf("Insert at beginning:\n");
    for (int i = 0; i < n; i++) {
        insertAtBegining(&myList, &arr[i], sizeof(int));
    }
    traverseList(&myList, printInt, NULL);
    printf("\n");

    destroyList(&myList);
    createList(&myList);

    printf("Insert at end:\n");
    for (int i = 0; i < n; i++) {
        insertAtEnd(&myList, &arr[i], sizeof(int));
    }
    traverseList(&myList, printInt, NULL);
    printf("\n");

    destroyList(&myList);
    createList(&myList);

    printf("Insert sorted:\n");
    for (int i = 0; i < n; i++) {
        insertSorted(&myList, &arr[i], sizeof(int), compareInt, NULL);
    }
    traverseList(&myList, printInt, NULL);
    printf("\n");

    printf("List length: %d\n", listLen(&myList));

    int key = 3;
    dsList* foundNode = search_key(&myList, &key, compareInt);
    if (*foundNode) {
        printf("Key %d found.\n", *(int*)(*foundNode)->info);
    } else {
        printf("Key %d not found.\n", key);
    }

    destroyList(&myList);
    destroyList(&list);
    return 0;
}
