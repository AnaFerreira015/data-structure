#include <stdlib.h>
#include <stdio.h>

#define MAX_HEAP_SIZE 10

typedef struct HEAP {
    int size;
    int data[MAX_HEAP_SIZE];
} HEAP;

// TODO: Change to shift bit
int get_parent_index(int i) {
    return i/2;
}

int get_left_index(int i) {
    return 2*i;
}

int get_right_index(int i) {
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
    return (!heap->size);
}

void max_heapify(HEAP *heap, int i) {
    int largest;
    int left_index = get_left_index(i);
    int right_index = get_right_index(i);

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
        int parent_index = get_parent_index(heap->size);

        while(parent_index >= 1 && heap->data[key_index] > heap->data[parent_index]) {
            swap(&heap->data[key_index], &heap->data[parent_index]);

            key_index = parent_index;

            parent_index = get_parent_index(key_index);
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

void max_heap(HEAP *heap) {
    int aux = heap->size, i;
    for(i = aux/2; i >= 1; i--) {
        max_heapify(heap, i);
    }
}

void printing_heap(HEAP *heap) {
    int i;
    for(i = 1; i <= heap->size; i++){
        printf("heap[%d] = %d\n", i, heap->data[i]);
    }
}

void heapsort(HEAP *heap) {
    int i, k;
    for(i = heap->size; i >= 2; i--) {
        swap(&heap->data[1], &heap->data[i]);
        // printing_heap(heap);
        // scanf("%d", &k);
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

int main () {
    HEAP *heap = create_heap();

    int i, item;

    // printf("\nReceives values:\n");
    for(i = 1; i <= MAX_HEAP_SIZE; i++) {
        scanf("%d", &item);
        enqueue(heap, item);
        // heap->data[i] = item; // serve para quando não usa a enqueue
        // heap->size++; // serve para quando não usa a enqueue
    }
    printf("\nPrinting heap: \n");
    printing_heap(heap);

    // int d = dequeue(heap);
    // printf("\ndequeued %d\n", d);
    // printf("\nPrinting after dequeue:\n");
    // printing_heap(heap);

    heapsort(heap);
    heap->size = MAX_HEAP_SIZE;
    printf("\nPrinting after heapsort:\n");
    printing_heap(heap);

    return 0;
}