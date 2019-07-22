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
        return 0;
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

    for (j = 0; j < qtd_strings; j++)
    {
        STACK *parenteses = creating_stack();
        STACK *colchetes = creating_stack();

        // scanf("%s\n", sequency);
        getchar();
        // gets(sequency);
        scanf("%[] ()[]\n", sequency);
        // printf("%s\n", sequency);
        size_string = strlen(sequency);

        for (i = 0; i < size_string; i++)
        {
            if(size_string == 0) {
                printf("Yes\n");
            }
            if (sequency[i] == '(')
            {
                push(parenteses, sequency[i]);
            }
            if (sequency[i] == '[')
            {
                // printf("add %c\n", sequency[i]);
                push(colchetes, sequency[i]);
            }
            if (sequency[i] == ')')
            {
                if (!(pop(parenteses)))
                {
                    push(parenteses, sequency[i]);
                    break;
                }
            }
            if (sequency[i] == ']')
            {
                // printf("rm %c\n", sequency[i]);
                if (!(pop(colchetes)))
                {
                    push(colchetes, sequency[i]);
                    // printf("entrou %c\n", sequency[i]);
                    break;
                }
            }
        }
        if (isEmpty(parenteses) && isEmpty(colchetes))
        {
            printf("Yes\n");
        }
        else
        {
            printf("No\n");
        }
    }

    return 0;
}