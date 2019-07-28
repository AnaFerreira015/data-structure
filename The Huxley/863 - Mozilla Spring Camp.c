#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct NODE
{
    char command[8];
    struct NODE *next;
} NODE;

typedef struct STACK
{
    int size;
    NODE *head;
} STACK;

STACK *create_stack()
{
    STACK *new_stack = (STACK *)malloc(sizeof(STACK));

    new_stack->head = NULL;
    new_stack->size = 0;

    return new_stack;
}

NODE *add_in_stack(NODE *head_stack, char *command)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));

    strcpy(new_node->command, command);
    new_node->next = head_stack;

    return new_node;
}

void push(STACK *stack, char *command)
{
    NODE *new_node = (NODE *)malloc(sizeof(NODE));

    new_node->next = stack->head;
    stack->head = new_node;
    stack->size = stack->size + 1;
}

void pop(STACK *stack)
{
    if (stack->size != 0)
    {
        NODE *new_node = stack->head;
        stack->head = stack->head->next;
        free(new_node);
        stack->size = stack->size - 1;
    }
    else
    {
        return;
    }
}

void restart(STACK *stack)
{
    if (stack->head != NULL)
    {
        NODE *new_node = stack->head;
        stack->head = stack->head->next;
        free(new_node);
        stack->size = stack->size - 1;
        restart(stack);
    }
}

int isEmpty(STACK *stack)
{
    return (stack->head == NULL);
}

int main()
{
    char command[8];

    STACK *back = create_stack();
    STACK *foward = create_stack();

    back->size = -1;
    // foward->size = 0;

    while (scanf("%s", command) != EOF)
    {
        // printf("BACK iter: %d\n", back->size);
        // printf("FORWARD iter: %d\n", foward->size);
        if (strcmp(command, "ENTER") == 0)
        {
            push(back, command);
            restart(foward);
        }
        if (strcmp(command, "BACK") == 0)
        {
            push(foward, command);
            pop(back);
        }
        if (strcmp(command, "FORWARD") == 0)
        {
            push(back, command);
            pop(foward);
        }
    }
    printf("BACK: %d\n", back->size);
    printf("FORWARD: %d\n", foward->size);

    return 0;
}