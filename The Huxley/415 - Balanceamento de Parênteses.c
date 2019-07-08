#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256

typedef struct NODE
{
    char character;
    struct NODE *next;
} NODE;

typedef struct STACK
{
    struct NODE *top;
} STACK;

STACK *creating_stack()
{
    STACK *new_stack = (STACK *)malloc(sizeof(STACK));
    new_stack->top = NULL;

    return new_stack;
}

void push(STACK *stack, char character)
{
    NODE *new_top = (NODE *)malloc(sizeof(NODE));

    new_top->character = character;
    new_top->next = stack->top;
    stack->top = new_top;
}

int isEmpty(STACK *stack)
{
    return (stack->top == NULL);
}

NODE *pop(STACK *stack)
{
    NODE *aux = (NODE *)malloc(sizeof(NODE));

    if (isEmpty(stack))
    {
        printf("Stack underflow\n");
    }
    else
    {
        aux = stack->top;
        stack->top = stack->top->next;
        aux->next = NULL;

        return aux;
    }
}

char peek(STACK *stack)
{
    if (isEmpty(stack))
    {
        return 0;
    }
    else
    {
        return stack->top->character;
    }
}

void printing(NODE *node)
{
    if (node != NULL)
    {
        printf("%c\n", node->character);
        return printing(node->next);
    }
}

int main()
{
    int qtd_strings, i, size_string, j;

    char sequency[MAX_SIZE];
    int aux = 0;

    scanf("%d", &qtd_strings);



    for(j = 0; j < qtd_strings; j++) {
        STACK *top = creating_stack();
        // scanf("%s\n", sequency);
        getchar();
        gets(sequency);
        // printf("%s\n", sequency);
        size_string = strlen(sequency);
        if(size_string < 2) {
            printf("No\n");
        }
        else if (sequency[0] == '(' || sequency[0] == '[')
        {
            push(top, sequency[0]);
            for (i = 1; i < size_string; i++)
            {
                if (sequency[i] == '(' || sequency[i] == '[')
                {
                    push(top, sequency[i]);
                }
                else if (sequency[i] == ')' || sequency[i] == ']')
                {
                    if(peek(top) == '(' && sequency[i] == ')'){
                        pop(top);
                        continue;
                    }
                    else if(peek(top) == '[' && sequency[i] == ']'){
                        pop(top);
                        continue;
                    }
                    else {
                        // printf("DEBUG 1\n");
                        printf("No\n");
                    }

                    // if (isEmpty(top))
                    // {
                    //     // printf("DEBUG 1\n");
                    //     // ([] )
                    //     // printf("No\n");
                    //     push(top, sequency[i]);
                    // }
                    // else
                    // {
                    //     pop(top);
                    // }
                }
            }
            printing(top->top);
            if (isEmpty(top))
            {
                // printf("DEBUG 2\n");
                printf("Yes\n");
            }
            else
            {
                // printf("DEBUG 2\n");
                printf("No\n");
                
                while(!isEmpty(top)){
                    pop(top);
                }
            }
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}