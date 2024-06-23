#include "dynamic_stack.h"
int fibonacci_recursive_stack(int);
int main()
{
    int res = fibonacci_recursive_stack(10);
    printf("%d", res);
    return 0;
}

int fibonacci_recursive_stack(int n){
    tStack stack;
    int result =0, current,x;
    createStack(&stack);
    push(&stack, &n, sizeof(n));
    while(!isEmpty(&stack))
    {
        pop(&stack, &current, sizeof(current));
        if(current <=1){
            result+= current;
        }
        else{
            x = current-1;
            push(&stack, &x,sizeof(x));
            x = current-2;
            push(&stack, &x, sizeof(x));
        }
    }
    destroy(&stack);
    return result;
}
