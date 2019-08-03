#include <stdlib.h>
#include <stdio.h>

#define MAX_HEAP_SIZE 10

typedef struct HEAP {
    int size;
    int data[MAX_HEAP_SIZE];
} HEAP;

int get_parent_index(HEAP *heap, int i) {
    return i/2;
}

int get_left_index(HEAP *heap, int i) {
    return 2*i;
}

int get_right_index(HEAP *heap, int i) {
    return 2*i + 1;
}

int item_of(HEAP *heap, int i) {
    return heap->data[i];
}

void swap(int *a, int *b)
{
    int aux = *a;
    *a = *b;
    *b = aux;
}

int isEmpty(HEAP *heap) {
    return (heap->size == 0);
}

void max_heapify(HEAP *heap, int i) {
    int largest;
    int left_index = get_left_index(heap, i);
    int right_index = get_right_index(heap, i);

    if(left_index <= heap->size && heap->data[left_index] > heap->data[i]) {
        largest = left_index;
    } else {
        largest = i;
    }

    if(right_index <= heap->size && heap->data[right_index] > heap->data[largest]) {
        largest = right_index;
    }

    if(heap->data[i] != heap->data[largest]) {
        swap(&heap->data[i], &heap->data[largest]);
        max_heapify(heap, largest);
    }
}

void enqueue(HEAP *heap, int item) {
    if(heap->size >= MAX_HEAP_SIZE) {
        printf("Heap overflow\n");
    }
    else {
        heap->data[++heap->size] = item;

        int key_index = heap->size;
        int parent_index = get_parent_index(heap, heap->size);

        while(parent_index >= 1 && heap->data[key_index] > heap->data[parent_index]) {
            swap(&heap->data[key_index], &heap->data[parent_index]);

            key_index = parent_index;

            parent_index = get_parent_index(heap, key_index);
        }
    }
}

int dequeue(HEAP *heap) {
    if(isEmpty(heap)) {
        printf("Heap underflow\n");
        return -1;
    }
    else {
        int item = heap->data[1];
        heap->data[1] = heap->data[heap->size];
        heap->size--;
        max_heapify(heap, 1);

        return item;
    }
}

void heapsort(HEAP *heap) {
    int i;
    for(i = MAX_HEAP_SIZE; i >= 2; i--) {
        swap(&heap->data[1], &heap->data[i]);
        heap->size--;
        max_heapify(heap, 1);
    }
}

HEAP *create_heap() {
    HEAP *heap = (HEAP*)malloc(sizeof(HEAP));
    int i;

    for(i = 1; i <= MAX_HEAP_SIZE; i++) {
        heap->data[i] = 0;
    }
    heap->size = 0;

    return heap;
}

void printing_heap(HEAP *heap) {
    int i;
    for(i = 1; i <= MAX_HEAP_SIZE; i++){
        printf("heap[%d] = %d\n", i, heap->data[i]);
    }
}

int main () {
    HEAP *heap = create_heap();

    int i, item;

    // printf("Printing before enqueue:\n");
    // printing_heap(heap);

    // printf("\nReceives values:\n");
    for(i = 1; i <= MAX_HEAP_SIZE; i++) {
        printf("heap->size: %d\n", heap->size);
        scanf("%d", &item);
        // enqueue(heap, item);
        heap->data[i] = item;
        heap->size++;
    }
    
    printf("\nprinting_heap:\n");
    printing_heap(heap);

    int d = dequeue(heap);
    printf("\ndequeued %d\n", d);
    // printf("\nPrinting after dequeue:\n");
    // printing_heap(heap);

    heapsort(heap);
    printf("\nPrinting after heapsort:\n");
    printing_heap(heap);
    return 0;
}