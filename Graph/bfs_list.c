#include <stdio.h>
#include <stdlib.h>

typedef struct NODE {
    int item;
    struct NODE *next; 
} NODE;

typedef struct QUEUE {
    NODE *head;
    NODE *tail;
    int size;
} QUEUE;

NODE *creating_node(int item) {
    NODE *node = (NODE*)malloc(sizeof(NODE));
    
    node->item = item;
    node->next = NULL;

    return node;
}

void printing_queue(QUEUE *queue) {
    NODE *temp = queue->head;
    while(temp != NULL) {
        printf("%d -> ", temp->item);
        temp = temp->next;
    }
}

void enqueue(QUEUE *queue, int item) {
    NODE *node = creating_node(item);
    if (queue->size == 0) {
        queue->head = node;
        queue->tail = node;
        queue->size++;
        return;
    }
    queue->tail->next = node;
    queue->tail = node;
    queue->size++;
    return;
}

int dequeue(QUEUE *queue)
{
    if (!queue->size) {
        printf("0 elementos\n");
        return 0;
    }
    if (queue->size == 1) {
        queue->size--;
        NODE *aux = queue->head;
        queue->head = NULL;
        queue->tail = NULL;
        free(aux);
        return 1;
    }
    NODE *aux = queue->head;
    printf("\nRemove head: %d", aux->item);

    queue->head = aux->next;
    queue->size--;
    free(aux);
    return 1;
}

int main() {
    QUEUE *queue = (QUEUE*)malloc(sizeof(QUEUE));
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    int i;
    for (i = 0; i < 10; i++) {
        enqueue(queue, i);
    }
    printing_queue(queue);

    int k = dequeue(queue);
    printf("\nNew head: %d\n", k);
    printing_queue(queue);
    printf("\n");
    printf("Size: %d\n", queue->size);
    return 0;
}