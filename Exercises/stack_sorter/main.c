#include "dynamic_stack.h"
int test_stack_sorter(const char*);
int sort_stack(tStack*, const char*);

int main()
{
    printf("Executing testing:\n");
    test_stack_sorter("case1.txt");
    return 0;
}

int test_stack_sorter(const char* fileName)
{
    tStack sortedStack;
    int top, lastTop;

    createStack(&sortedStack);
    sort_stack(&sortedStack, fileName);

    pop(&sortedStack, &lastTop, sizeof(int));

    for (int i = 0; i < 20; i++)
    {
        pop(&sortedStack, &top, sizeof(int));
        if(top > lastTop)
        {
            printf("\t\t Not sorted.\n");
            destroy(&sortedStack);
            return 1;
        }
        lastTop = top;
    }
    printf("TEST PASSED!\n");
    return 0;
}

int sort_stack(tStack* stack, const char* fileName)
{

    tStack auxStack;
    FILE *file = fopen(fileName, "rt");
    int current_number, top;

    if(!file)
    {
        printf("File name error.\n");
        return 0;
    }

    createStack(&auxStack);

    while (!feof(file))
    {
        fscanf(file,"%d\n", &current_number);
        peek(stack, &top, sizeof(top));
        if(current_number > top)
        {
            push(stack,&current_number, sizeof(int));
        }
        else
        {
            while (!isEmpty(stack)  && current_number < top)
            {
                pop(stack, &top, sizeof(top));
                push(&auxStack, &top, sizeof(top));
                peek(stack, &top, sizeof(top));
            }
            push(stack,&current_number, sizeof(int));
            while (!isEmpty(&auxStack))
            {
                pop(&auxStack, &top, sizeof(int));
                push(stack, &top, sizeof(int));
                peek(&auxStack, &top, sizeof(top));
            }
        }
    }
    destroy(&auxStack);
    fclose(file);
    return 1;
}
