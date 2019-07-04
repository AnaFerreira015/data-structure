#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_SIZE 256

typedef struct NODE {
    char character;
    struct NODE *next;
} NODE;

typedef struct STACK {
    struct NODE *top;
} STACK;

STACK *creating_stack() {
    STACK *new_stack = (STACK *) malloc(sizeof(STACK));
    new_stack->top = NULL;

    return new_stack;
}

void push(STACK *stack, char character){
    NODE *new_top = (NODE*)malloc(sizeof(NODE));

    new_top->character = character;
    new_top->next = stack->top;
    stack->top = new_top;
}

int isEmpty(STACK *stack){
    return (stack->top == NULL);
}

NODE *pop(STACK *stack) {
    NODE *aux = (NODE*)malloc(sizeof(NODE));

    if(isEmpty(stack)){
        printf("Stack underflow\n");
    }
    else  {
        aux = stack->top;
        stack->top = stack->top->next;
        aux->next = NULL;

        return aux;
    }
}

NODE *peek(STACK *stack){
    if(isEmpty(stack)){
        printf("Stack underflow\n");
    }
    else {
        return stack->top;
    }
}

void printing(NODE *node){
    if(node != NULL){
        printf("%c\n", node->character);
        return printing(node->next);
    }
}

int main () {
    int qtd_strings, i, size_string, j;

    char sequency[MAX_SIZE];

    // scanf("%d", &qtd_strings);

    STACK *top = creating_stack();

    // for(j = 0; j < qtd_strings; j++){         
        scanf("%[^\n]s", sequency);
        size_string = strlen(sequency);
        if(sequency[0] == '(' || sequency[0] == '['){
            push(top, sequency[0]);
            for(i = 1; i < size_string; i++) {
                if(sequency[i] == '(' || sequency[i] == '[') {
                    push(top, sequency[i]);
                }
                else if(sequency[i] == ')' || sequency[i] == ']')
                {
                    pop(top);
                }

            }
            if(isEmpty(top)){
                printf("Yes\n");
            }
            else {
                printf("No\n");
            }
        }
        else {
            printf("No\n");
        }
    // }

    // for (i = 0; i < qtd_strings; i++){
    //     scanf("%[^\n]s", sequency);
    //     size_string = strlen(sequency);

    //     // STACK *top = creating_stack();

    //     if(sequency[0] == '(' || sequency[0] == '['){
    //         push(top, sequency[0]);
    //         for(j = 1; j < size_string; j++){
    //             if(sequency[j] == '(' || sequency[j] == '[') {
    //                 push(top, sequency[j]);
    //             }
    //             else {
    //                 pop(top);
    //             }
    //         }
    //         if(isEmpty(top)){
    //             printf("Yes\n");
    //         }
    //         else {
    //             printf("No\n");
    //         }
    //     }
    //     else {
    //         printf("No\n");
    //     }
    // }
    return 0;
}