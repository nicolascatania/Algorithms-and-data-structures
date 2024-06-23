#include "dynamic_stack.h"

#define BUFFER_SIZE 100
#define IN "math_expressions_raw.txt"
#define OUT "math_expressions_debugged.txt"

int math_expression_debugger(const char*, const char*);
int read_expression(char* , FILE**);
int debug_expression(char*, FILE**);
int same_type(char a, char b);

int main()
{
    math_expression_debugger(IN, OUT);
    return 0;
}
int math_expression_debugger(const char* FILE_IN, const char* FILE_OUT)
{
    FILE* in = fopen(FILE_IN, "rt");
    FILE* out = fopen(FILE_OUT,"wt");
    char buffer[BUFFER_SIZE];
    if(!in )
    {
        fclose(out);
        printf("ERROR; CANNOT OPEN %s.\n", FILE_IN);
        return 0;
    }
    if(!out)
    {
        fclose(in);
        printf("ERROR; CANNOT OPEN %s.\n", FILE_OUT);
        return 0;
    }
    while(!feof(in))
    {
        if(!read_expression(buffer, &in))
        {
            puts("There was a trouble reading the math expression.");
            return 0;
        }
        debug_expression(buffer, &out);
    }
    fclose(in);
    fclose(out);
    return 1;
}
int debug_expression(char* buffer, FILE** file_ptr)
{
    tStack stack;
    createStack(&stack);
    char top, missing_character, last_correct_char;
    char line[BUFFER_SIZE];
    char *pl = line, *pb = buffer;
    int error=0;
    while (*pb)
    {
        if (*pb == '(' || *pb == '[' || *pb == '{')
        {
            push(&stack, pb, sizeof(char));
            *pl= *pb;
            pl++;
        }
        else if (*pb == ')' || *pb == ']' || *pb == '}')
        {
            if (!isEmpty(&stack))
            {
                peek(&stack, &top, sizeof(top));
                if (same_type(top, *pb))
                {
                    pop(&stack, &top, sizeof(top));
                    *pl= *pb;
                    last_correct_char=*pl;
                    pl++;
                }
                else
                {
                    if (top == '(')
                        missing_character = ')';
                    else if (top == '[')
                        missing_character = ']';
                    else if (top == '{')
                        missing_character = '}';

                    error=1;
                    break;
                }
            }
            else
            {
                missing_character = *pb == ')' ? '(' : (*pb == ']' ? '[' : '{');
                error = 1;
                break;

            }
        }
        pb++;
    }
    if (!isEmpty(&stack))
    {
        peek(&stack,&top,sizeof(top));
        if (top == '(')
            missing_character = ')';
        else if (top == '[')
            missing_character = ']';
        else if (top == '{')
            missing_character = '}';
        error = 1;
    }
    *pl = '\0';
    if(error)
    {
        fprintf(*file_ptr, "%-30s ||| Expected %c after %c\n\n",line,missing_character, last_correct_char);
    }
    else
    {
        fprintf(*file_ptr, "%-30s ||| Nothing wrong\n\n", line);
    }
    destroy(&stack);
    return 1;
}
int same_type(char a, char b) {
    const char open[] = "([{";
    const char close[] = ")]}";
    char *pos_a = strchr(open, a);
    char *pos_b = strchr(close, b);
    if (pos_a && pos_b) {
        int idx_a = pos_a - open;
        int idx_b = pos_b - close;
        if (idx_a == idx_b) {
            return 1;
        }
    }
    return 0;
}
int read_expression(char* buffer, FILE** file_ptr)
{
    char c;
    char* pc = buffer;
    const char parenthesis[] = "()[]{}";
    int empty_spaces = 0;
    while ((c = fgetc(*file_ptr)) != EOF)
    {
        if (c == '|')
        {
            empty_spaces++;
            if(empty_spaces>1)
            {
                break;
            }
        }
        else if (strchr(parenthesis, c) != NULL)
        {
            *pc = c;
            pc++;
        }
    }
    *pc='\0';
    return 1;
}

