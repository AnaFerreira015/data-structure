#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int item;
    struct NODE *next;
} NODE;

typedef struct QUEUE {
    int current_size;
    int head;
    int tail;
    NODE *items;
} QUEUE;

NODE *create_node(int e) {
    NODE *new_node = (NODE*)malloc(sizeof(NODE));
    new_node->item = e;
    new_node->next = NULL;

    return new_node;
}

QUEUE *create_queue() {
    QUEUE *new_queue = (QUEUE*) malloc(sizeof(QUEUE));
    new_queue->current_size = 0;
    new_queue->head = 0;
    new_queue->tail = 0;
    new_queue->items = NULL;
    
    return new_queue;
}

int isEmpty(QUEUE *queue) {
    return (queue->current_size == 0);
}

void enqueue(QUEUE *queue, int e) {
    NODE *node = create_node(e);

    if(queue->current_size == 0){
        queue->head = e;
        queue->tail = e;
    }
    queue->current_size++;
    // printf("current size: %d\n", queue->current_size);
    queue->tail = e;
    // printf("Tail: %d\n", queue->tail);
    queue->items = node;
    // printf("Items item: %d\n", queue->items->item);
}

void printing_queue(QUEUE *queue){
    
}

int main () {
   
    QUEUE *queue = create_queue();
    // printf("debug\n");
    enqueue(queue, 2);  
    // printf("\nEnqueue 2: \n");
    enqueue(queue, 4);
    return 0;
}