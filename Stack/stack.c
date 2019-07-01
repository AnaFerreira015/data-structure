#include <stdlib.h>
#include <stdio.h>

typedef struct NODE {
    int num;
    struct NODE *next;
} NODE;

typedef struct STACK {
    struct NODE *top;
} STACK;

STACK *creating_stack(){
    STACK *new_stack = (STACK*)malloc(sizeof(STACK));
    new_stack->top = NULL;

    return new_stack;
}

void push(STACK *stack, int e){
    NODE *new_top = (NODE*)malloc(sizeof(NODE));
    new_top->num = e;
    new_top->next = stack->top;
    stack->top = new_top;
}

int isEmpty(STACK *stack){
    return (stack->top == NULL);
}

NODE *pop(STACK *stack){
    NODE *aux = (NODE *)malloc(sizeof(NODE));

    if(isEmpty(stack)){
        printf("Stack underflow\n");
    }
    else {
        aux = stack->top;
        stack->top = stack->top->next;
        return aux;
    }
}

NODE *peek (STACK *stack){
    if (isEmpty(stack))
    {
        printf("Stack underflow\n");
    }
    else {
        return stack->top;
    }
}

void printing(NODE *node)
{
    if (node != NULL)
    {
        printf("%d\n", node->num);
        return printing(node->next);
    }
}

int main () {
    int num;

    scanf("%d", &num);

    STACK *top = creating_stack();

    push(top, num);

    int count = 1;
    while (scanf("%d", &num) != EOF)
    {
        push(top, num);
        count++;
    }

    printing(top->top);

    NODE *node_peek = peek(top);
    printf("PEEK: %d\n", node_peek->num);

    NODE *node_pop = pop(top);
    printf("POP: %d\n", node_pop->num);

    node_pop = pop(top);
    printf("POP: %d\n", node_pop->num);

    printing(top->top);
    return 0;
}