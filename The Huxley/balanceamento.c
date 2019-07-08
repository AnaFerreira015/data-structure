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

int main () {
    int qtd_strings, i, size_string, j;
    char sequency[MAX_SIZE];

    scanf("%d ", &qtd_strings);

    for(i = 0; i < qtd_strings; i++) {
        STACK *stack = creating_stack();
        getchar();
        gets(sequency);

        size_string = strlen(sequency);
        if(size_string < 2) {
            printf("No\n");
        }
        else {
            for(j = 0; j < size_string; j++) {
                if(sequency[i] == '(' || sequency[i] == '['){
                    push(stack, sequency[i]);
                }
                else{
                    if(sequency[i] == ')'){
                        if(peek(stack) == '('){
                            pop(stack);
                        } else {
                            
                        }
                    }
                }
            }
        }
    }
    return 0;
}